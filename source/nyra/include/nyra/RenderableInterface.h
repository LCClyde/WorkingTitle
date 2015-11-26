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
#ifndef NYRA_RENDERABLE_INTERFACE_H_
#define NYRA_RENDERABLE_INTERFACE_H_

#include <nyra/Matrix.h>
#include <nyra/Vector2.h>
#include <nyra/GraphicsInterface.h>

namespace nyra
{
/*
 *  \class RenderableInterface
 *  \brief Represents a single renderable object. This is an abstract object
 *         that could be as simple as a pixel to as complex as an entire gui.
 */
class RenderableInterface
{
public:
    /*
     *  \fn Destructor
     *  \brief Here for proper inheritance.
     */
    virtual ~RenderableInterface();

    /*
     *  \fn render
     *  \brief Renders the object to a graphics interface.
     *
     *  \param matrix The positional information about the object.
     *  \param graphics The graphics interface to render to.
     */
    virtual void render(const Matrix& matrix,
                        GraphicsInterface& graphics) = 0;

    /*
     *  \fn getSize
     *  \brief Gets the overall size of the object when it is at its
     *         default starting dimensions and rotation.
     *
     *  \return The size of the object.
     */
    virtual Vector2U getSize() const = 0;
};
}
#endif
