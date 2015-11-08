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
#ifndef NYRA_GRAPHICS_INTERFACE_H_
#define NYRA_GRAPHICS_INTERFACE_H_

#include <string>
#include <nyra/Types.h>

namespace nyra
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
     *  \fn clear
     *  \brief Clears a window.
     *
     *  \param handle The operating system specific window handle. This
     *         should be castable to the correct type.
     */
    virtual void clear(WindowsHandle handle) = 0;

    /*
     *  \fn clear
     *  \brief Renders a single frame to any window. It is assumed that the
     *         same window was cleared as presented.
     */
    virtual void present() = 0;

    /*
     *  \fn screenshot
     *  \brief Saves a screenshot of the current render.
     *
     *  \param pathname The pathname of the location to save to. The
     *         extension in the pathname should provide the filetype.
     *         Note: Only PNG is expected at this time.
     */
    virtual void screenshot(const std::string& pathname) const = 0;

private:

};
}

#endif