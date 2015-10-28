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
#ifndef CORE_VECTOR_H_
#define CORE_VECTOR_H_

namespace core
{
template <typename TypeT, size_t SizeT>
struct VectorN
{
public:
    operator 
protected:
    std::array<TypeT, SizeT> data_;
};

template <typename T>
struct Vector2 : public VectorN<T, 2>
{
public:
    Vector2() :
        x(data_[0]),
        y(data_[1])
    {
    }
    
    Vector2(const T& x, const T& y) :
        x(data_[0]),
        y(data_[1])
    {
        this->x = x;
        this->y = y;
    }
    
    template <typename ThirdPartyT>
    Vector2(const ThirdPartyT& vector)
        x(data_[0]),
        y(data_[1])
    {
        x = vector.x;
        y = vector.y;
    }
    
    T& x;
    T& y;
};
}

#endif

