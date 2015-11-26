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
#ifndef NYRA_SFML_SPRITE_H_
#define NYRA_SFML_SPRITE_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <nyra/RenderableInterface.h>
#include <nyra/SpriteInterface.h>

namespace nyra
{
namespace sfml
{
/*
 *  \class Sprite
 *  \brief Represents a single drawable sprite.
 */
class Sprite : public RenderableInterface, public SpriteInterface
{
public:
    /*
     *  \fn Constructor
     *  \brief Creates a sprite object.
     *
     *  \param pathname The pathname to the texture on disk.
     *  \param numFrames The number of frames in the x and y direction.
     */
    Sprite(const std::string& pathname,
           const Vector2U& numFrames = Vector2U(1, 1));

    /*
     *  \fn render
     *  \brief Renders the object to a graphics interface.
     *
     *  \param matrix The positional information about the object.
     *  \param graphics The graphics interface to render to.
     */
    void render(const Matrix& matrix,
                GraphicsInterface& graphics) override;

    /*
     *  \fn getSize
     *  \brief Gets the overall size of the object when it is at its
     *         default starting dimensions and rotation.
     *
     *  \return The size of the object.
     */
    Vector2U getSize() const override;

    /*
     *  \fn setFrame
     *  \brief Sets a portion of the sprite as the current frame.
     *
     *  \param index The frame number to use for rendering.
     */
    void setFrame(size_t index) override;

private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    const Vector2U mNumFrames;
    Vector2U mFrameSize;
};
}
}

#endif