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
#ifndef NYRA_SFML_WINDOW_SFML_H_
#define NYRA_SFML_WINDOW_SFML_H_

#include <nyra/WindowInterface.h>
#include <SFML/Window.hpp>

namespace nyra
{
namespace sfml
{
/*
 *  \class WindowSFML
 *  \brief Represents the
 */
class Window : public WindowInterface
{
public:
    /*
     *  \fn Constructor
     *  \brief Creates an opens a SFML window.
     *
     *  \param title The title of the window.
     *  \param size The desired size of the window. This should represent
     *         the client size and not the actual size.
     *  \param position The desired postition of the window.
     *  \param fullscreen Should the window be fullscreen? If it is then
     *         size and position will ignored.
     */
    Window(const std::string& title,
           const Vector2U& size,
           const Vector2I& position,
           bool fullscreen);

    /*
     *  \fn Destructor
     *  \brief Closes the window when it goes out of scope.
     */
    ~Window();

    /*
     *  \fn update
     *  \brief Polls the operator system messages.
     */
    void update() override;

    /*
     *  \fn getTitle
     *  \brief Returns the title of the window.
     *
     *  \return The current title.
     */
    std::string getTitle() const override;

    /*
     *  \fn setTitle
     *  \brief Sets the window title.
     *
     *  \param title The desired title.
     */
    void setTitle(const std::string& title) override;

    /*
     *  \fn getSize
     *  \brief Returns the window size. Note that this should reflect the
     *         client area and not the actual window size.
     *
     *  \return The current window size.
     */
    Vector2U getSize() const override;

    /*
     *  \fn setSize
     *  \brief Gets the window size. Note that this should reflect the
     *         client area and not the actual window size.
     *
     *  \iparam The desired window size.
     */
    void setSize(const Vector2U& size) override;

    /*
     *  \fn getPosition
     *  \brief Gets the position of the window based on the default top left
     *         corner of the primary monitor.
     *
     *  \return The current window position.
     */
    Vector2I getPosition() const override;

    /*
     *  \fn setPosition
     *  \brief Sets the window position based on the top left corner of the
     *         primary monitor.
     *
     *  \param The desired window position.
     */
    void setPosition(const Vector2I& position) override;

    /*
     *  \fn isOpen
     *  \brief Used to determine if the window is opened. A closed window
     *         should be treated as invalid.
     *
     *  \return True if the window is still open.
     */
    bool isOpen() const override;

    /*
     *  \fn getFullscreen
     *  \brief Used to determine if a window is in fullscreen mode.
     *
     *  \return True if the window is in fullscreen mode.
     */
    bool getFullscreen() const override;

    /*
     *  \fn setFullscreen
     *  \brief Sets the fullscreen state of the window.
     *
     *  \param fullscreen The desired fullscreen setting.
     */
    void setFullscreen(bool fullscreen) override;

    /*
     *  \fn getHandle
     *  \brief This can be used to obtain a platform specific handle to the
     *         window object. This handle should be able to cast
     *         directly into the platform specific object.
     *
     *  \return The platform specific handle or NULL if the window is closed.
     */
    WindowsHandle getHandle() const override;

private:
    sf::Window mWindow;
    std::string mTitle;
    bool mFullscreen;
};
}
}

#endif

