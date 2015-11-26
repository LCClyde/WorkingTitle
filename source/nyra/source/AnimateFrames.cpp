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
#include <nyra/AnimateFrames.h>
#include <stdexcept>

namespace nyra
{
//===========================================================================//
AnimateFrames::AnimateFrames(size_t startFrame,
                             size_t endFrame,
                             double duration,
                             AnimateMode mode) :
    mStartFrame(startFrame),
    mEndFrame(endFrame),
    mTimePerFrame(duration / (endFrame - startFrame + 1)),
    mCurrentFrame(startFrame),
    mMode(mode),
    mElapsedTime(0.0),
    mAnimationDirection(1),
    mSpriteInjection(nullptr)
{
    if (mEndFrame < mStartFrame)
    {
        std::runtime_error(
                "End frame of animation is smaller than the start frame");
    }

    // We need at least 3 frames for PING PONG
    if ((mMode == AnimateMode::PING_PONG_ONCE ||
        mMode == AnimateMode::PING_PONG_LOOP) &&
        mEndFrame - mStartFrame < 2)
    {
        std::runtime_error(
                "At least 3 frames are required for a PING_PONG animation");
    }
}

//===========================================================================//
bool AnimateFrames::update(double deltaTime)
{
    // Update the time
    mElapsedTime += deltaTime;

    // Check for a frame tick
    if (mElapsedTime >= mTimePerFrame)
    {
        mCurrentFrame += mAnimationDirection;
        mElapsedTime -= mTimePerFrame;

        // Check for the end of the animation
        if (mCurrentFrame > mEndFrame)
        {
            switch (mMode)
            {
            case AnimateMode::PLAY_ONCE:
                return false;
            case AnimateMode::LOOP:
                mCurrentFrame = mStartFrame;
                break;
            case AnimateMode::PING_PONG_ONCE:
            case AnimateMode::PING_PONG_LOOP:
                mCurrentFrame -= 2;
                mAnimationDirection = -1;
                break;
            }
        }
        // Check for the end of ping pong
        else if (mCurrentFrame < mStartFrame)
        {
            if (mMode == AnimateMode::PING_PONG_LOOP)
            {
                mCurrentFrame += 2;
                mAnimationDirection = 1;
            }
            else if (mMode == AnimateMode::PING_PONG_ONCE)
            {
                return false;
            }
        }

        if (mSpriteInjection)
        {
            mSpriteInjection->setFrame(mCurrentFrame);
        }
    }

    return true;
}
}
