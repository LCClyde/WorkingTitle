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
#include <gtest/gtest.h>
#include <nyra/sfml/Window.h>

namespace
{
// TODO: We need to wait make sure everything has initialized properly.
//       Is there something more relable than sleep? Ideally we would have
//       waitForWindow() function.
void wait(size_t seconds = 1)
{
    sleep(seconds);
}
}

TEST(WindowSFMLTest, Construction)
{
    {
        nyra::sfml::Window win("Test window",
                               nyra::Vector2U(1280, 720),
                               nyra::Vector2I(500, 300),
                               false);

        wait();
        EXPECT_TRUE(win.isOpen());
        EXPECT_EQ(win.getTitle(), "Test window");
        EXPECT_FALSE(win.getFullscreen());
        EXPECT_EQ(win.getSize(), nyra::Vector2U(1280, 720));
        // TODO: Depending on platform this might be incorrect. By making
        // the position larger and towards the center it may fix the issue
        EXPECT_EQ(win.getPosition(), nyra::Vector2I(500, 300));
    }

    {
        nyra::sfml::Window win("Test window",
                               nyra::Vector2U(1280, 720),
                               nyra::Vector2I(500, 300),
                               true);

        wait();
        EXPECT_TRUE(win.isOpen());
        EXPECT_EQ(win.getTitle(), "Test window");
        EXPECT_TRUE(win.getFullscreen());
        // Size is dependant on the desktop resolution so there is nothing
        // to test.
        // Position should go to 0.
        EXPECT_EQ(win.getPosition(), nyra::Vector2I(0, 0));
    }
}

TEST(WindowSFMLTest, Fullscreen)
{
    nyra::sfml::Window win("Test window",
                           nyra::Vector2U(1280, 720),
                           nyra::Vector2I(500, 300),
                           false);

    wait();
    EXPECT_FALSE(win.getFullscreen());
    win.setFullscreen(true);
    wait();
    EXPECT_TRUE(win.getFullscreen());
    win.setFullscreen(false);
    wait();
    EXPECT_FALSE(win.getFullscreen());
}

TEST(WindowSFMLTest, Mutators)
{

    nyra::sfml::Window win("Test window",
                           nyra::Vector2U(1280, 720),
                           nyra::Vector2I(500, 300),
                           false);

    wait();
    win.setPosition(nyra::Vector2I(600, 400));
    win.setSize(nyra::Vector2U(1000, 600));
    win.setTitle("A new title");
    wait();
    EXPECT_EQ(win.getTitle(), "A new title");
    EXPECT_EQ(win.getSize(), nyra::Vector2U(1000, 600));
    EXPECT_EQ(win.getPosition(), nyra::Vector2I(600, 400));
}
