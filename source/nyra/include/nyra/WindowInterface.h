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
#ifndef NYRA_WINDOW_INTERFACE_H_
#define NYRA_WINDOW_INTERFACE_H_

#include <string>
#include <nyra/Types.h>
#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \class WindowInterface
 *  \brief Represents the expected class for a Window object. All Window
 *         objects should inherit from this class.
 */
class WindowInterface
{
public:
    /*
     *  \fn Destructor
     *  \brief Included for proper inheritance.
     */
    virtual ~WindowInterface();

    /*
     *  \fn update
     *  \brief Handles all operator system level messages. In general this
     *         should not be concerned with input. A seperate input module
     *         should handle this.
     *
     *  \return False if the Window has been closed and is no longer valid.
     */
    virtual bool update() = 0;

    /*
     *  \fn getTitle
     *  \brief Returns the title of the window.
     *
     *  \return The current title.
     */
    virtual std::string getTitle() const = 0;

    /*
     *  \fn setTitle
     *  \brief Sets the window title.
     *
     *  \param title The desired title.
     */
    virtual void setTitle(const std::string& title) = 0;

    /*
     *  \fn getSize
     *  \brief Returns the window size. Note that this should reflect the
     *         client area and not the actual window size.
     *
     *  \return The current window size.
     */
    virtual Vector2U getSize() const = 0;

    /*
     *  \fn setSize
     *  \brief Gets the window size. Note that this should reflect the
     *         client area and not the actual window size.
     *
     *  \iparam The desired window size.
     */
    virtual void setSize(const Vector2U& size) = 0;

    /*
     *  \fn getPosition
     *  \brief Gets the position of the window based on the default top left
     *         corner of the primary monitor.
     *
     *  \return The current window position.
     */
    virtual Vector2I getPosition() const = 0;

    /*
     *  \fn setPosition
     *  \brief Sets the window position based on the top left corner of the
     *         primary monitor.
     *
     *  \param The desired window position.
     */
    virtual void setPosition(const Vector2I& position) = 0;

    /*
     *  \fn isOpen
     *  \brief Used to determine if the window is opened. A closed window
     *         should be treated as invalid.
     *
     *  \return True if the window is still open.
     */
    virtual bool isOpen() const = 0;

    /*
     *  \fn getFullscreen
     *  \brief Used to determine if a window is in fullscreen mode.
     *
     *  \return True if the window is in fullscreen mode.
     */
    virtual bool getFullscreen() const = 0;

    /*
     *  \fn setFullscreen
     *  \brief Sets the fullscreen state of the window.
     *
     *  \param fullscreen The desired fullscreen setting.
     */
    virtual void setFullscreen(bool fullscreen) = 0;

    /*
     *  \fn getHandle
     *  \brief This can be used to obtain a platform specific handle to the
     *         window object. This handle should be able to cast
     *         directly into the platform specific object.
     *
     *  \return The platform specific handle or NULL if the window is closed.
     */
    virtual WindowsHandle getHandle() const = 0;
};
}

#endif

