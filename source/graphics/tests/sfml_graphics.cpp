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
#include <iostream>
#include <stdexcept>
#include <window/WindowSFML.h>
#include <graphics/GraphicsSFML.h>

int main(int argc, char** argv)
{
    try
    {
        window::WindowSFML win("Test window",
                               core::Vector2U(1280, 720),
                               core::Vector2I(0, 0),
                               false);

        graphics::GraphicsSFML graph;

        while (win.isOpen())
        {
            win.update();
            graph.render(win.getHandle());
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Caught standard exception from " <<
            ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Caught unnamed Unwanted exception" << std::endl;
    }
}