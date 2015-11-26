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
#ifndef NYRA_SPRITE_INTERFACE_H_
#define NYRA_SPRITE_INTERFACE_H_

#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \class SpriteInterface
 *  \brief Represents a sprite. In general something that inherits this
 *         will also inherit RenderableInterface.
 */
class SpriteInterface
{
public:
    /*
     *  \fn Destructor
     *  \brief Here for proper inheritance.
     */
    ~SpriteInterface();

    /*
     *  \fn setFrame
     *  \brief Sets a portion of the sprite as the current frame.
     *
     *  \param index The frame number to use for rendering.
     */
    virtual void setFrame(size_t index) = 0;
};
}

#endif