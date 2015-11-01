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
#ifndef WINDOW_WINDOW_SFML_H_
#define WINDOW_WINDOW_SFML_H_

#include <string>
#include <core/vector_2.h>

namespace window {
class WindowSFML {
public:
    WindowSFML(const std::string& title,
               const core::Vector2U& size,
               const core::Vector2I& position,
               bool fullscreen);

    void update();

    std::string getTitle() const;

    void setTitle(const std::string& title);

    core::Vector2U getSize() const;

    void setSize(const core::Vector2U& size);

    core::Vector2I getPosition() const;

    void setPosition(const core::Vector2I& position);

    bool isClosed() const;

    void close();

    bool getFullscreen() const;

    void setFullscreen(bool fullscreen);

    void* getHandle() const;
};
}

#endif

