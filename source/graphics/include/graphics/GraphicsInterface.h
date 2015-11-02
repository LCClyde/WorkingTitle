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
#ifndef GRAPHICS_GRAPHICS_INTERFACE_H_
#define GRAPHICS_GRAPHICS_INTERFACE_H_

#include <core/Types.h>

namespace graphics
{
/*
 *  \class GraphicsInterface
 *  \brief Base class for rendering objects to the screen. This meant to be a
 *         manager for graphics libraries that require some global
 *         functionality as well as handle registering sprites.
 */
class GraphicsInterface
{
public:
    /*
     *  \fn Destructor
     *  \brief Here for proper inheritance.
     */
    ~GraphicsInterface();

    /*
     *  \fn render
     *  \brief Renders a single frame to any window.
     *
     *  \param handle The operating system specific window handle. This
     *         should be castable to the correct type.
     */
    virtual void render(core::WindowsHandle handle) = 0;
};
}

#endif