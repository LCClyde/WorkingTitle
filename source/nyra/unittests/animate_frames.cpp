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
#include <nyra/AnimateFrames.h>
#include <nyra/SpriteInterface.h>

namespace
{
//===========================================================================//
struct FrameAccessor : public nyra::SpriteInterface
{
public:
    FrameAccessor() :
        frame(0)
    {
    }

    void setFrame(size_t index) override
    {
        frame = index;
    }

    size_t frame;
};
}

//===========================================================================//
TEST(AnimateFrames, PlayOnce)
{
    FrameAccessor accesor;
    nyra::AnimateFrames frames(2, 5, 2.0, nyra::AnimateMode::PLAY_ONCE);
    frames.inject(accesor);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 2);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 3);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 3);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 4);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 4);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 5);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 5);
    EXPECT_FALSE(frames.update(0.25));
}

//===========================================================================//
TEST(AnimateFrames, Loop)
{
    FrameAccessor accesor;
    nyra::AnimateFrames frames(2, 5, 2.0, nyra::AnimateMode::LOOP);
    frames.inject(accesor);
    for (size_t ii = 0; ii < 7; ++ii)
    {
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 2);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 3);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 3);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 4);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 4);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 5);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 5);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 2);
    }
}

//===========================================================================//
TEST(AnimateFrames, PING_PONG_ONCE)
{
    FrameAccessor accesor;
    nyra::AnimateFrames frames(2, 5, 2.0, nyra::AnimateMode::PING_PONG_ONCE);
    frames.inject(accesor);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 2);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 3);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 3);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 4);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 4);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 5);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 5);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 4);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 4);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 3);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 3);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 2);
    EXPECT_TRUE(frames.update(0.25));
    EXPECT_EQ(accesor.frame, 2);
    EXPECT_FALSE(frames.update(0.25));
}

//===========================================================================//
TEST(AnimateFrames, PING_PONG_LOOP)
{
    FrameAccessor accesor;
    nyra::AnimateFrames frames(2, 5, 2.0, nyra::AnimateMode::PING_PONG_LOOP);
    frames.inject(accesor);
    for (size_t ii = 0; ii < 7; ++ii)
    {
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 2);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 3);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 3);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 4);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 4);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 5);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 5);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 4);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 4);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 3);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 3);
        EXPECT_TRUE(frames.update(0.25));
        EXPECT_EQ(accesor.frame, 2);
    }
}

