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

namespace nyra
{
namespace sfml
{
/*
 *  \class Sprite
 *  \brief Represents a single drawable sprite.
 */
class Sprite : public RenderableInterface
{
public:
    /*
     *  \fn Constructor
     *  \brief Creates a sprite object.
     *
     *  \param pathname The pathname to the texture on disk.
     */
    Sprite(const std::string& pathname);

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
    Vector2F getSize() const override;

private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
};
}
}

#endif