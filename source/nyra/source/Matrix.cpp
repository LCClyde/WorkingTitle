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
#include <nyra/Matrix.h>
#include <string.h>
#include <nyra/Constants.h>

namespace nyra
{
//===========================================================================//
Matrix::Matrix()
{
    // Zero out all data
    memset(mData, 0.0f, 9 * sizeof(float));

    // Set identity matrix
    mData[0][0] = 1.0f;
    mData[1][1] = 1.0f;
    mData[2][2] = 1.0f;
}

//===========================================================================//
Matrix::Matrix(float aa, float ab, float ac,
               float ba, float bb, float bc,
               float ca, float cb, float cc)
{
    mData[0][0] = aa;
    mData[0][1] = ab;
    mData[0][2] = ac;
    mData[1][0] = ba;
    mData[1][1] = bb;
    mData[1][2] = bc;
    mData[2][0] = ca;
    mData[2][1] = cb;
    mData[2][2] = cc;
}

//===========================================================================//
Matrix::Matrix(const Vector2F& position,
               const Vector2F& offset,
               const Vector2F& scale,
               float rotation)
{
    const float rad  = -rotation * Constants::DEGREES_TO_RADIANS;
    const float cos = static_cast<float>(std::cos(rad));
    const float sin = static_cast<float>(std::sin(rad));
    mData[0][0] = scale.x * cos;
    mData[1][1] = scale.y * cos;
    mData[1][0] = -(scale.x * sin);
    mData[0][1] = scale.y * sin;

    // Note that offset comes in as a negative since that makes more
    // sense when applying directly as a transform. We need to keep that
    // in mind here.
    mData[0][2] = (offset.x * mData[0][0]) +
            (offset.y * mData[0][1]) + position.x;
    mData[1][2] = (offset.x * mData[1][0]) +
            (offset.y * mData[1][1]) + position.y;

    mData[2][0] = 0.0f;
    mData[2][1] = 0.0f;
    mData[2][2] = 1.0f;
}

//===========================================================================//
Matrix& Matrix::operator*=(const Matrix& other)
{
    (*this) = (*this) * other;
    return *this;
}

//===========================================================================//
Matrix Matrix::operator*(const Matrix& other) const
{
    Matrix temp(0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f);

    for (size_t ii = 0; ii < 3; ++ii)
    {
        for (size_t jj = 0; jj < 3; ++jj)
        {
            for (size_t kk = 0; kk < 3; ++kk)
            {
                temp.mData[ii][jj] += mData[ii][kk] * other.mData[kk][jj];
            }
        }
    }
    return temp;
}

//===========================================================================//
void Matrix::translate(const Vector2F& vector)
{
    (*this) *= Matrix(1.0f, 0.0f, vector.x,
                      0.0f, 1.0f, vector.y,
                      0.0f, 0.0f, 1.0f);
}

//===========================================================================//
void Matrix::scale(const Vector2F& vector)
{
    (*this) *= Matrix(vector.x, 0.0f, 0.0f,
                      0.0f, vector.y, 0.0f,
                      0.0f, 0.0f, 1.0f);
}

//===========================================================================//
void Matrix::rotate(float rotation)
{
    const float rad = rotation * Constants::DEGREES_TO_RADIANS;
    const float cos = std::cos(rad);
    const float sin = std::sin(rad);

    (*this) *= Matrix(cos, -sin, 0.0f,
                      sin, cos, 0.0f,
                      0.0f, 0.0f, 1.0f);
}
}