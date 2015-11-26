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
#ifndef NYRA_TRANSFORM_H_
#define NYRA_TRANSFORM_H_

#include <nyra/Vector2.h>
#include <nyra/Matrix.h>

namespace nyra
{
/*
 *  \class Transform
 *  \brief Used to keep track of positional information of an entity.
 */
class Transform
{
public:
    /*
     *  \fn Constructor
     *  \brief Sets up the internal structure of a transform. The members
     *         are in the following units.
     *         Position - Pixels from top left corner.
     *         Scale - Normalized from default size.
     *         Rotation - Clockwise degrees.
     *         Pivot - Normalized where center of object is 0.5f.
     */
    Transform();

    /*
     *  \fn setPosition
     *  \brief Sets the positional information of the transform.
     *         This sets the dirty flag.
     *
     *  \param position The new desired position.
     */
    inline void setPosition(const Vector2F& position)
    {
        mPosition = position;
        mNeedMatrixUpdate = true;
    }

    /*
     *  \fn setPosition
     *  \brief Sets the positional information of the transform.
     *         This sets the dirty flag.
     *
     *  \param x The new desired x position.
     *  \param y The new desired y position.
     */
    inline void setPosition(float x, float y)
    {
        setPosition(Vector2F(x, y));
    }

    /*
     *  \fn getPosition
     *  \brief Returns the transforms position.
     *
     *  \return The positional information.
     */
    inline const Vector2F& getPosition() const
    {
        return mPosition;
    }

    /*
     *  \fn setScale
     *  \brief Sets the scale information of the transform.
     *         This sets the dirty flag.
     *
     *  \param scale The new desired scale.
     */
    inline void setScale(const Vector2F& scale)
    {
        mScale = scale;
        mNeedMatrixUpdate = true;
    }

    /*
     *  \fn setScale
     *  \brief Sets the scale information of the transform.
     *         This sets the dirty flag.
     *
     *  \param x The new desired x scale.
     *  \param y The new desired y scale.
     */
    inline void setScale(float x, float y)
    {
        setScale(Vector2F(x, y));
    }

    /*
     *  \fn getScale
     *  \brief Returns the transforms scale.
     *
     *  \return The scale information.
     */
    inline const Vector2F& getScale() const
    {
        return mScale;
    }

    /*
     *  \fn setRotation
     *  \brief Sets the rotational information of the transform.
     *         This sets the dirty flag.
     *
     *  \param rotation The new desired rotation.
     */
    inline void setRotation(float rotation)
    {
        mRotation = rotation;
        mNeedMatrixUpdate = true;
    }

    /*
     *  \fn getRotation
     *  \brief Returns the transform rotation.
     *
     *  \return The rotational information.
     */
    inline float getRotation() const
    {
        return mRotation;
    }

    /*
     *  \fn setPivot
     *  \brief Sets the pivot information of the transform.
     *         This sets the dirty flag.
     *
     *  \param pivot The new desired pivot.
     */
    inline void setPivot(const Vector2F& pivot)
    {
        mPivot = pivot;
        mNeedMatrixUpdate = true;
    }

    /*
     *  \fn setPivot
     *  \brief Sets the pivot information of the transform.
     *         This sets the dirty flag. This will only work correctly if
     *         the size parameter has been set.
     *
     *  \param x The new desired x pivot.
     *  \param y The new desired y pivot.
     */
    inline void setPivot(float x, float y)
    {
        setPivot(Vector2F(x, y));
    }

    /*
     *  \fn getPivot
     *  \brief Returns the transforms pivot.
     *
     *  \return The rotational information.
     */
    const Vector2F& getPivot() const
    {
        return mPivot;
    }

     /*
      *  \fn getMatrix
      *  \brief Updates and returns the transforms matrix. If the matrix is
      *         out of date it will recalculate everything.
      *
      *  \return The matrix object.
      */
     const Matrix& getMatrix();
     /*
      *  \fn setSize
      *  \brief Sets the size of the underlying object. This allows the pivot
      *         to work correctly. This should only be called from a manager
      *         graphics object.
      *
      *  \param size The object size.
      */
     void setSize(const Vector2U& size)
     {
        mSize = size * -1.0f;
        mNeedMatrixUpdate = true;
     }

private:
    Vector2F mPosition;
    Vector2F mScale;
    float mRotation;
    Vector2F mPivot;
    Matrix mMatrix;
    Vector2I mSize;
    bool mNeedMatrixUpdate;
};
}
#endif
