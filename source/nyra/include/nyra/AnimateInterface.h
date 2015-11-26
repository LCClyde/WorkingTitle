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
#ifndef NYRA_ANIMATE_INTERFACE_H_
#define NYRA_ANIMATE_INTERFACE_H_

namespace nyra
{
/*
 *  \enum AnimateMode
 *  \brief Used to describe how an animation should be played:
 *         DEFAULT - Play once
 *         LOOP - Repeat forever
 *         PING_PONG - Repeat and then go backwards. Repeat this forever.
 */
enum class AnimateMode
{
    PLAY_ONCE,
    LOOP,
    PING_PONG_ONCE,
    PING_PONG_LOOP
};

/*
 *  \class AnimateInterface
 *  \brief A base class for all animations.
 */
class AnimateInterface
{
public:
    /*
     *  \fn Constructor
     *  \brief Here for proper inheritance.
     */
    ~AnimateInterface();

    /*
     *  \fn update
     *  \brief Updates the animation object.
     *
     *  \param deltaTime The time since the last update.
     *  \return false if the animation is finished and should be removed.
     */
    virtual bool update(double deltaTime) = 0;
};
}

#endif