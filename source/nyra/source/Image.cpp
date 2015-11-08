/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <nyra/Image.h>
#include <exception>
#include <png.h>

namespace nyra
{
//===========================================================================//
Image::Image(const std::string& pathname) :
    mPixelSize(0)
{
    FILE* filePtr = fopen(pathname.c_str(), "rb");
    if (filePtr == NULL)
    {
        throw std::runtime_error("File not found by PNG reader");
    }

    png_structp pngPtr;
    png_infop infoPtr;
    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (pngPtr == NULL)
    {
        fclose(filePtr);
        throw std::runtime_error("Create read struct failed");
    }

    infoPtr = png_create_info_struct(pngPtr);
    if (infoPtr == NULL)
    {
        fclose(filePtr);
        png_destroy_read_struct(&pngPtr, NULL, NULL);

        throw std::runtime_error("Create create info struct failed");
    }

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
        fclose(filePtr);
        throw std::runtime_error("Read failed in image read.");
    }

    png_init_io(pngPtr, filePtr);
    png_read_info(pngPtr, infoPtr);

    int32_t depth;
    int32_t color;
    int32_t filter;
    int32_t compr;
    int32_t interlace;

    png_get_IHDR(pngPtr,
                 infoPtr,
                 reinterpret_cast<png_uint_32*>(&mSize.x),
                 reinterpret_cast<png_uint_32*>(&mSize.y),
                 &depth,
                 &color,
                 &interlace,
                 &compr,
                 &filter);

    if (color == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(pngPtr);
    }

    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(pngPtr);
    }

    if (depth < 8)
    {
        throw std::runtime_error("Grayscale PNGs are not supported");
    }

    // I dont know when this happens
    png_set_interlace_handling(pngPtr);

    // We probably need to do a png_set_packswap as well
    png_read_update_info(pngPtr, infoPtr);

    mPixelSize = depth / 8;

    // I dont need to bother with channels, since Im forcing my modes here.
    switch (color)
    {
    case PNG_COLOR_TYPE_PALETTE:
        mPixelSize *= 3;
        break;
    case PNG_COLOR_TYPE_GRAY:
        throw std::runtime_error("Grayscale PNGs are not supported");
        break;
    case PNG_COLOR_TYPE_RGB:
        mPixelSize *= 3;
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        mPixelSize *= 4;
        break;
    default:
        throw std::runtime_error("Unknown PNG type");
        break;
    }

    const size_t rowbytes = png_get_rowbytes(pngPtr, infoPtr);
    png_bytep* rowPtrs = static_cast<png_bytep*>(
            png_malloc(pngPtr, mSize.y * sizeof(png_bytep)));

    mBuffer.reset(new uint8_t[mSize.product() * mPixelSize]);

    for (size_t ii = 0; ii < mSize.y; ++ii)
    {
        rowPtrs[ii] = static_cast<png_bytep>(&mBuffer[ii * rowbytes]);
    }

    png_read_image(pngPtr, rowPtrs);
    write("/home/clyde/lena.png");
}

//===========================================================================//
void Image::write(const std::string& file) const
{
    FILE* filePtr = fopen(file.c_str(), "wb");
    if (filePtr == NULL)
    {
        throw std::runtime_error("File not usable by PNG writer");
    }

    png_infop infoPtr;
    png_structp  pngPtr = png_create_write_struct(
            PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (pngPtr == NULL)
    {
        fclose(filePtr);
        throw std::runtime_error("Create read struct failed");
    }

    infoPtr = png_create_info_struct(pngPtr);
    if (infoPtr == NULL)
    {
        fclose(filePtr);
        png_destroy_read_struct(&pngPtr, NULL, NULL);
        throw std::runtime_error("Create create info struct failed");
    }

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
        fclose(filePtr);
        throw std::runtime_error("Read failed in image write.");
    }

    png_init_io(pngPtr, filePtr);
    int colorType;
    const size_t sampleDepth = (mPixelSize * 8) / mPixelSize;
    switch (mPixelSize)
    {
    case 3:
        colorType = PNG_COLOR_TYPE_RGB;
        break;
    case 4:
        colorType = PNG_COLOR_TYPE_RGBA;
        break;
    default:
        throw std::runtime_error("Only RGB and RGBA pngs are supported.");
        break;
    }

    const int interlaceType = PNG_INTERLACE_NONE; //TODO default to None?

    //set a bunch of parameters at once
    png_set_IHDR(pngPtr,
                 infoPtr,
                 mSize.x,
                 mSize.y,
                 sampleDepth,
                 colorType,
                 interlaceType,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    // write it
    png_write_info(pngPtr, infoPtr);

    // let libpng take care of, e.g., bit-depth conversions
    png_set_packing(pngPtr);

    //get the data from the image
    const size_t lineSize = mSize.x * mPixelSize;
    for (size_t i = 0; i < mSize.y; i++)
    {
        // Read one row
        png_write_row(pngPtr, (png_byte*) (mBuffer.get() + (i * lineSize)));
    }

    png_write_end(pngPtr, infoPtr);
    png_destroy_write_struct(&pngPtr, &infoPtr);

    //clean up
    fclose(filePtr);
}

//===========================================================================//
bool Image::operator==(const Image& other) const
{
    if (mSize != other.mSize)
    {
        return false;
    }

    if (mPixelSize != other.mPixelSize)
    {
        return false;
    }

    const size_t imageSize = mSize.product() * mPixelSize;
    for (size_t ii = 0; ii < imageSize; ++ii)
    {
        if (mBuffer[ii] != other.mBuffer[ii])
        {
            return false;
        }
    }

    return true;
}
}
