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
#include <window/WindowSFML.h>

namespace window
{
//===========================================================================//
WindowSFML::WindowSFML(const std::string& title,
                       const core::Vector2U& size,
                       const core::Vector2I& position,
                       bool fullscreen) :
    mWindow(sf::VideoMode(size.x, size.y), title,
            fullscreen ? (sf::Style::Fullscreen) :
                         (sf::Style::Close | sf::Style::Titlebar)),
    mTitle(title),
    mFullscreen(fullscreen)
{
    // Set vsync by default
    mWindow.setVerticalSyncEnabled(true);
    if (!mFullscreen)
    {
        setPosition(position);
    }
}

//===========================================================================//
WindowSFML::~WindowSFML()
{
    if (mWindow.isOpen())
    {
        mWindow.close();
    }
}

//===========================================================================//
void WindowSFML::update()
{
    // Make sure the window is open
    if (!mWindow.isOpen())
    {
        return;
    }

    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
}

//===========================================================================//
std::string WindowSFML::getTitle() const
{
    return mTitle;
}

//===========================================================================//
void WindowSFML::setTitle(const std::string& title)
{
    mTitle = title;
    mWindow.setTitle(title);
}

//===========================================================================//
core::Vector2U WindowSFML::getSize() const
{
    return core::Vector2U(mWindow.getSize());
}

//===========================================================================//
void WindowSFML::setSize(const core::Vector2U& size)
{
    mWindow.setSize(size.toThirdParty<sf::Vector2u>());
}

//===========================================================================//
core::Vector2I WindowSFML::getPosition() const
{
    return core::Vector2I(mWindow.getPosition());
}

//===========================================================================//
void WindowSFML::setPosition(const core::Vector2I& position)
{
    mWindow.setPosition(position.toThirdParty<sf::Vector2i>());
}

//===========================================================================//
bool WindowSFML::isOpen() const
{
    return mWindow.isOpen();
}

//===========================================================================//
bool WindowSFML::getFullscreen() const
{
    // We need to handle the fullscreen flag ourselves
    return mFullscreen;
}

//===========================================================================//
void WindowSFML::setFullscreen(bool fullscreen)
{
    // If we already have the correct settings, just return
    if (fullscreen == mFullscreen)
    {
        return;
    }

    // We need to destroy and recreate our window
    // Store off the current information
    // You lose your positional information going from fullscreen to windowed
    const sf::Vector2u size = mWindow.getSize();
    mWindow.close();
    mWindow.create(sf::VideoMode(size.x, size.y), mTitle,
                   fullscreen ? (sf::Style::Fullscreen) :
                           (sf::Style::Close | sf::Style::Titlebar));
    mWindow.setVerticalSyncEnabled(true);
    mFullscreen = fullscreen;
}

//===========================================================================//
core::WindowsHandle WindowSFML::getHandle() const
{
    return reinterpret_cast<core::WindowsHandle>(mWindow.getSystemHandle());
}
}

