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
#ifndef NYRA_SFML_GRAPHICS_H_
#define NYRA_SFML_GRAPHICS_H_

#include <nyra/GraphicsInterface.h>
#include <SFML/Graphics.hpp>

namespace nyra
{
namespace sfml
{
/*
 *  \class GraphicsSFML
 *  \brief A SFML specific graphics renderer.
 */
class Graphics : public GraphicsInterface
{
public:
    /*
     *  \fn clear
     *  \brief Clears a window.
     *
     *  \param handle The operating system specific window handle. This
     *         should be castable to the correct type.
     */
    void clear(WindowsHandle handle) override;

    /*
     *  \fn clear
     *  \brief Renders a single frame to any window. It is assumed that the
     *         same window was cleared as presented.
     */
    void present() override;

    /*
     *  \fn screenshot
     *  \brief Saves a screenshot of the current render.
     *
     *  \param pathname The pathname of the location to save to. The
     *         extension in the pathname should provide the filetype.
     *         SFML does support a lot of filetypes, but to be as
     *         portable as possible you should limit screenshots to png.
     */
    void screenshot(const std::string& pathname) const override;

    /*
     *  \fn getRenderTarget
     *  \brief SFML has the draw command attached to the render window.
     *         This gets that window so things can draw to it.
     *
     *  \return The render window.
     */
    inline sf::RenderWindow& getRenderTarget()
    {
        return mWindow;
    }

private:
    sf::RenderWindow mWindow;
};
}
}

#endif
