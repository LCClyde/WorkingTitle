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
#ifndef NYRA_ANIMATE_FRAMES_H_
#define NYRA_ANIMATE_FRAMES_H_

#include <nyra/AnimateInterface.h>
#include <nyra/SpriteInterface.h>

namespace nyra
{
/*
 *  \class AnimateFrames
 *  \brief Used to perform frame by frame animations. This is guaranteed to
 *         play each frame once. In other words if something would cause this
 *         to skip frames (lagging) it will instead slow down the animation
 *         to ensure each frame plays.
 */
class AnimateFrames : public AnimateInterface
{
public:
    /*
     *  \fn Constructor
     *  \brief Sets up the internal structure of the frame animation.
     *
     *  \param startFrame The first frame in the animation (inclusive)
     *  \param endFrame The last frame in the animation (inclusive)
     *  \param duration The total time to play all frames
     *  \param mode The way the animation should be played
     */
    AnimateFrames(size_t startFrame,
                  size_t endFrame,
                  double duration,
                  AnimateMode mode = AnimateMode::PLAY_ONCE);

    /*
     *  \fn inject
     *  \brief Sets the sprite that will play the animations.
     *
     *  \param The sprite to animate.
     */
    inline void inject(SpriteInterface& sprite)
    {
        // Only inject if there is not something already injected.
        // this allows the caller to supply a sprite instead.
        if (!mSpriteInjection)
        {
            mSpriteInjection = &sprite;
            mSpriteInjection->setFrame(mCurrentFrame);
        }
    }

    /*
     *  \fn update
     *  \brief Updates the animation object.
     *
     *  \param deltaTime The time since the last update.
     *  \return false if the animation is finished and should be removed.
     */
    bool update(double deltaTime) override;

private:
    const size_t mStartFrame;
    const size_t mEndFrame;
    const double mTimePerFrame;
    int64_t mCurrentFrame;
    const AnimateMode mMode;
    double mElapsedTime;
    int8_t mAnimationDirection;
    SpriteInterface* mSpriteInjection;
};
}

#endif
