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
#include <nyra/Vector2.h>
#include <nyra/Transform.h>

TEST(Transform, AccessorsMutators)
{
    nyra::Transform transform;
    EXPECT_EQ(transform.getPosition(), nyra::Vector2F(0.0f, 0.0f));
    EXPECT_EQ(transform.getScale(), nyra::Vector2F(1.0f, 1.0f));
    EXPECT_EQ(transform.getRotation(), 0.0f);
    EXPECT_EQ(transform.getPivot(), nyra::Vector2F(0.5f, 0.5f));
    EXPECT_TRUE(transform.getAndResetDirty());
    EXPECT_FALSE(transform.getAndResetDirty());

    const nyra::Vector2F testVec(567.909f, -345.234f);
    transform.setPosition(testVec);
    EXPECT_EQ(transform.getPosition(), testVec);
    EXPECT_TRUE(transform.getAndResetDirty());

    transform.setScale(testVec);
    EXPECT_EQ(transform.getScale(), testVec);
    EXPECT_TRUE(transform.getAndResetDirty());

    transform.setRotation(testVec.x);
    EXPECT_EQ(transform.getRotation(), testVec.x);
    EXPECT_TRUE(transform.getAndResetDirty());

    transform.setPivot(testVec);
    EXPECT_EQ(transform.getPivot(), testVec);
    EXPECT_TRUE(transform.getAndResetDirty());
}
