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
#ifndef CORE_VECTOR_2_H_
#define CORE_VECTOR_2_H_

#include <core/VectorN.h>
#include <stdint.h>

namespace core
{
/*
 *  \class Vector2
 *  \brief A two dimensional vector. This can be used for 2D position or scale.
 *         Common types are typenamed for easier use.
 *
 *  \tparam TypeT The data type for elements.
 */
template <typename TypeT>
class Vector2 : public VectorN<TypeT, 2>
{
public:
    /*
     *  \fn Constructor
     *  \brief Default constructor
     */
    Vector2() :
        x(this->mData[0]),
        y(this->mData[1])
    {
    }

    /*
     *  \fn Constructor
     *  \brief Constructs a vector from X and Y values.
     *
     *  \param x The starting x value.
     *  \param y The starting y value.
     */
    Vector2(const TypeT& x, const TypeT& y) :
        x(this->mData[0]),
        y(this->mData[1])
    {
        this->x = x;
        this->y = y;
    }

    /*
     *  \fn Constructor
     *  \brief Constructs a vector from another vector. This can be used
     *         to copy from 3rd party vectors.
     *
     *  \tparam VectorT The vector type to copy from. This must have public
     *          x and y members.
     *  \param vector The vector to copy.
     */
    template <typename VectorT>
    Vector2(const VectorT& vector) :
        x(this->mData[0]),
        y(this->mData[1])
    {
        x = static_cast<TypeT>(vector.x);
        y = static_cast<TypeT>(vector.y);
    }

    /*
     *  \fn ToThirdParty
     *  \brief Converts a Vector2 into another 3rd party vector type.
     *
     *  \tparam ThirdPartyT The vector type to copy. This must have public
     *          x and y members.
     *  \return An instance of the 3rd party vector that acts a copy of this.
     */
    template <typename ThirdPartyT>
    ThirdPartyT ToThirdParty() const
    {
        ThirdPartyT ret;
        ret.x = x;
        ret.y = y;
        return ret;
    }

    /*
     *  \var x
     *  \brief Represents the first element of the vector.
     */
    TypeT& x;

    /*
     *  \var y
     *  \brief Represents the second element of the vector.
     */
    TypeT& y;
};

typedef Vector2<float> Vector2F;
typedef Vector2<int32_t> Vector2I;
typedef Vector2<uint32_t> Vector2U;

}

#endif

