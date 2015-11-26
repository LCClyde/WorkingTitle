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
#include <nyra/sfml/Sprite.h>
#include <exception>
#include <nyra/sfml/Graphics.h>

namespace nyra
{
namespace sfml
{
//===========================================================================//
Sprite::Sprite(const std::string& pathname,
               const Vector2U& numFrames) :
    mNumFrames(numFrames)
{
    // Ensure there is at least one frame in each direction
    if (mNumFrames.product() < 1)
    {
        throw std::runtime_error("You must have at least one sprite frame");
    }

    if (!mTexture.loadFromFile(pathname))
    {
        throw std::runtime_error("Unable to load texture: " + pathname);
    }
    mSprite.setTexture(mTexture);
    mFrameSize = Vector2U(mTexture.getSize()) / mNumFrames;
    setFrame(0);
}

//===========================================================================//
void Sprite::render(const Matrix& matrix,
                    GraphicsInterface& graphics)
{
    const sf::Transform sfmlMatrix(matrix(0, 0), matrix(0, 1), matrix(0, 2),
                                   matrix(1, 0), matrix(1, 1), matrix(1, 2),
                                   matrix(2, 0), matrix(2, 1), matrix(2, 2));
    Graphics& sfmlGraphics(dynamic_cast<Graphics&>(graphics));
    sfmlGraphics.getRenderTarget().draw(mSprite, sfmlMatrix);
}

//===========================================================================//
Vector2U Sprite::getSize() const
{
    return mFrameSize;
}

//===========================================================================//
void Sprite::setFrame(size_t index)
{
    if (index >= mNumFrames.product())
    {
        throw std::runtime_error("Frame index out of bounds");
    }

    const size_t xStart = (index % mNumFrames.x) * mFrameSize.x;
    const size_t yStart = (index / mNumFrames.x) * mFrameSize.y;
    mSprite.setTextureRect(sf::IntRect(xStart,
                                       yStart,
                                       mFrameSize.x,
                                       mFrameSize.y));
}
}
}