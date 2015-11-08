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
#include <nyra/sfml/Graphics.h>
#include <nyra/Constants.h>
#include <nyra/sfml/Sprite.h>
#include <nyra/Transform.h>
#include <nyra/Image.h>

namespace
{
class RunTest
{
public:
    RunTest() :
        mWindow("Test window",
                nyra::Vector2U(400, 400),
                nyra::Vector2I(0, 0),
                false),
        mSprite(nyra::Constants::APP_PATH +
                "../data/unittests/sfml-logo-small.png")
    {
    }

    nyra::Vector2F getSize()
    {
        return mSprite.getSize();
    }

    void operator()(nyra::Transform& transform,
                    const std::string& subname)
    {
        mWindow.update();
        mGraphics.clear(mWindow.getHandle());
        mSprite.render(transform.getMatrix(), mGraphics);
        mGraphics.present();
        const std::string imageName(nyra::Constants::APP_PATH +
                "../data/unittests/sfml_sprite_" + subname);
        mGraphics.screenshot(imageName + ".png");
        const nyra::Image image(imageName + ".png");
        const nyra::Image truth(imageName + "_truth.png");
        EXPECT_EQ(image, truth);
    }

private:
    nyra::sfml::Window mWindow;
    nyra::sfml::Graphics mGraphics;
    nyra::sfml::Sprite mSprite;
};
}

TEST(SpriteSFMLTest, Transforms)
{
    // Default no transforms
    RunTest test;
    nyra::Transform transform;
    transform.setSize(test.getSize());
    test(transform, "default");

    // Centered image
    transform.setPosition(nyra::Vector2F(200.0f, 200.0f));
    test(transform, "centered");

    transform.setRotation(33.33f);
    test(transform, "rotated");
    transform.setRotation(0.0f);

    transform.setScale(nyra::Vector2F(1.33f, 1.25f));
    test(transform, "scaled");

    transform.setScale(nyra::Vector2F(-1.0f, -1.0f));
    test(transform, "flipped");
    transform.setScale(nyra::Vector2F(1.0f, 1.0f));

    transform.setPivot(nyra::Vector2F(0.34f, 0.75f));
    test(transform, "pivot");

    transform.setPosition(nyra::Vector2F(187.89f, 213.56f));
    transform.setPivot(nyra::Vector2F(0.52f, 0.41f));
    transform.setScale(nyra::Vector2F(-1.1f, 0.89f));
    transform.setRotation(-24.654f);
    test(transform, "complex");

}