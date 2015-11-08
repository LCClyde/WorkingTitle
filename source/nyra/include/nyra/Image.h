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
#ifndef NYRA_IMAGE_H_
#define NYRA_IMAGE_H_

#include <string>
#include <memory>
#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \class image
 *  \brief Provides an interface independant way to read and compare images.
 *         This makes it possible to easily do graphics based unittests
 *         without needing CPU side image information in every graphics
 *         implementation.
 *
 *  \note This class currently only supports png.
 *  TODO: Add more image support as it is needed.
 */
class Image
{
public:
    /*
     *  \fn Constructor
     *  \brief Creates an image from disk.
     *
     *  \param pathname The image on disk.
     */
    Image(const std::string& pathname);

    /*
     *  \fn write
     *  \brief Writes an image to disk.
     *
     *  \param pathname The location on disk to write the image to.
     */
    void write(const std::string& pathname) const;

    /*
     *  \fn Equality Operator
     *  \brief Compares to images. Note this is an expensive deep compare
     *         meant for unittesting.
     *
     *  \param other The Image to compare against.
     *  \return true if the Images match
     */
    bool operator==(const Image& other) const;

    /*
     *  \fn Equality Operator
     *  \brief Compares to images. Note this is an expensive deep compare
     *         meant for unittesting.
     *
     *  \param other The Image to compare against.
     *  \return true if the Images match
     */
    inline bool operator!=(const Image& other) const
    {
        return !((*this) == other);
    }

private:
    size_t mPixelSize;
    std::unique_ptr<uint8_t[]> mBuffer;
    Vector2U mSize;
};
}

#endif