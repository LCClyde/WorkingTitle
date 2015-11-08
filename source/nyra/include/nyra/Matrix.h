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
#ifndef NYRA_MATRIX_H_
#define NYRA_MATRIX_H_

#include <ostream>
#include <nyra/Vector2.h>

namespace nyra
{
/*
 *  \class Matrix
 *  \brief Represents a 3X3 matrix used for transforming entities in
 *         two dimensional space.
 */
class Matrix
{
public:
    /*
     *  \fn Constructor
     *  \brief Creates an indentity matrix.
     */
    Matrix();

    /*
     *  \fn Constructor
     *  \brief Creates a matrix with known values.
     *
     *  \param aa row 0 column 0
     *  \param ab row 0 column 1
     *  \param ac row 0 column 2
     *  \param ba row 1 column 0
     *  \param bb row 1 column 1
     *  \param bc row 1 column 2
     *  \param ca row 2 column 0
     *  \param cb row 2 column 1
     *  \param cc row 2 column 2
     */
    Matrix(float aa, float ab, float ac,
           float ba, float bb, float bc,
           float ca, float cb, float cc);

    /*
     *  \fn Constructor
     *  \brief Applies all transformations in one shot.
     *
     *  \param position The position to apply
     *  \param offset The offset to represent the origin.
     *  \param scale The scale to apply
     *  \param rotation The rotation to apply in degrees.
     */
    Matrix(const Vector2F& position,
           const Vector2F& offset,
           const Vector2F& scale,
           float rotation);

    /*
     *  \fn Multiplication Operator
     *  \brief Multiplies two matrices together.
     *
     *  \param other The matrix to multiply by.
     *  \return The multiplied matrices.
     */
    Matrix operator*(const Matrix& other) const;

    /*
     *  \fn Multiplication Assignment Operator
     *  \brief Multiplies this matrix against another.
     *
     *  \param other The matrix to multiply by
     *  \return The multiplied matrices.
     */
    Matrix& operator*=(const Matrix& other);

    /*
     *  \fn Functor Operator
     *  \brief Returns a single value of the matrix. Note that this purposely
     *         does not do bounds checks to try to increase speed (this needs
     *         to be tested). It is undefined behaviour to send in values out
     *         of bounds.
     *
     *  \param row The row index.
     *  \param col The column index.
     *  \return The value at the given index.
     */
    inline float operator()(size_t row, size_t col) const
    {
        return mData[row][col];
    }

    /*
     *  \fn translate
     *  \brief Translates a matrix by a vector.
     *
     *  \param vector The amount to translate by.
     */
    void translate(const Vector2F& vector);

    /*
     *  \fn scale
     *  \brief Scales a matrix by a vector
     *
     *  \param vector The amount to scale by.
     */
    void scale(const Vector2F& vector);

    /*
     *  \fn rotate
     *  \brief Rotates a vector by an angle in degrees.
     *
     *  \param rotation The angle in degrees.
     */
    void rotate(float rotation);

private:
    float mData[3][3];
};

}

#endif