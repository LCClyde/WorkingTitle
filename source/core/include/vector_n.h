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
#ifndef CORE_VECTOR_N_H_
#define CORE_VECTOR_N_H_

#include <algorithm.h>

namespace core {

/*
 *  \class VectorN
 *  \brief A generic mathematical vector of any size and any type. Specialized
 *         versions of this class exist for sized 2, 3, and 4 vectors. These
 *         can be used for 2D locations, 3D locations, and quaternion. In
 *         general direct use of this class is discoraged.
 *
 *  \tparam TypeT The type for individual elements in the vector.
 *  \tparam SizeT The size of the vector.
 */
template <typename TypeT, size_t SizeT>
class VectorN {
public:
    ~VectorN() {
    }

    /*
     *  \fn Assignment Operator
     *  \brief Assigns one vector to another.
     *
     *  \param other The value to assign. Note, the parameter is sent in
     *         by value. This is so it can swap without destroying the
     *         original value.
     *  \return The new assigned vector.
     */
    VectorN<TypeT, SizeT>& operator=(VectorN<TypeT, SizeT> other) {
        std::swap(data_, other.data_);
        return *this;
    }

    /*
     *  \fn Equality Operator
     *  \brief Checks if each element of each vector are equal.
     *
     *  \param other The vector to check against.
     *  \return True if the vectors are equal.
     */
    bool operator==(const VectorN<TypeT, SizeT>& other) const {
        return std::equal(data_.begin(), data_.end(), other.data_.begin());
    }

    /*
     *  \fn Inequality Operator
     *  \brief Checks if any value in either vector are not equal.
     *
     *  \param other The vector to check against.
     *  \return True if the vectors are not equal.
     */
    bool operator!=(const VectorN<TypeT, SizeT>& other) const {
        return !(*this == other);
    }

    /*
     *  \fn Subscript Operator
     *  \brief Returns the value of the vector at an index.
     *
     *  \param index The index of the desired element.
     *  \return A reference to the element.
     *  \throw If the index is out range
     */
    TypeT& operator[](size_t index) {
        return data_[index];
    }

    /*
     *  \fn Subscript Operator
     *  \brief Returns the value of the vector at an index.
     *
     *  \param index The index of the desired element.
     *  \return A const reference to the element.
     *  \throw If the index is out range
     */
    const TypeT& operator[](size_t index) const {
        return data_[index];
    }

    /*
     *  \fn Addition Assignment Operator
     *  \brief Adds each element of the vectors together.
     *
     *  \param other The vector to add.
     *  \return The original vector with the other vector added to it.
     */
    VectorN<TypeT, SizeT>& operator+=(const VectorN<TypeT, SizeT>& other) {
        for (size_t ii = 0; ii < SizeT; ++ii) {
            data_[ii] += other.[ii];
        }
        return *this;
    }

    /*
     *  \fn Subtraction Assignment Operator
     *  \brief Subtracts each element of the vectors.
     *
     *  \param other The vector to subtract.
     *  \return The original vector with the other vector subtracted from it.
     */
    VectorN<TypeT, SizeT>& operator-=(const VectorN<TypeT, SizeT>& other) {
        for (size_t ii = 0; ii < SizeT; ++ii) {
            data_[ii] -= other[ii];
        }
        return *this;
    }

    /*
     *  \fn Addition Assignment Operator
     *  \brief Adds a passed in value to each element in the vector.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to add.
     *  \return The original vector with the value added to it.
     */
    template <typename ScalarT>
    VectorN<TypeT, SizeT>& operator+=(const ScalarT& value) {
        for (size_t ii = 0; ii < SizeT; ++ii) {
            data_[ii] += value;
        }
    }

    /*
     *  \fn Subtraction Assignment Operator
     *  \brief Subtracts a passed in value from each element in the vector.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to subtract.
     *  \return The original vector with the value subtracted from it.
     */

    template <typename ScalarT>
    VectorN<TypeT, SizeT>& operator-=(const ScalarT& value) {
        (*this) += (-value);
        return *this;
    }

    /*
     *  \fn Multiplication Assignment Operator
     *  \brief Multiplies each element in the vector by a passed in value.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to multiply by.
     *  \return The original vector with the value multiplied by it.
     */
    template <typename ScalarT>
    VectorN<TypeT, SizeT>& operator*=(const ScalarT& value) {
        for (size_t ii = 0; ii < SizeT; ++ii) {
            data_[ii] *= value;
        }
        return *this;
    }

    /*
     *  \fn Division Assignment Operator
     *  \brief Divides each element in a vector by a passed in value.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to divide by.
     *  \return The original vector divided by the value.
     */
    template <typename ScalarT>
    VectorN<TypeT, SizeT>& operator/=(const ScalarT& value) {
        (*this) /= (1.0 / value);
        return *this;
    }

    /*
     *  \fn Addition Operator
     *  \brief Adds two vectors together, element by element.
     *
     *  \param other The other vector to add. Note this is passed in by
     *         value since the operator will need to return by value
     *         anyways.
     *  \return A new vector which is both vectors added together.
     */
    VectorN<TypeT, SizeT> operator+(VectorN<TypeT, SizeT> other) const {
        other += (*this);
        return other;
    }

    /*
     *  \fn Subtraction Operator
     *  \brief Subtracts two vectors, element by element.
     *
     *  \param other The other vector to subtract. Note this is passed in by
     *         value since the operator will need to return by value
     *         anyways.
     *  \return A new vector which is the difference between the vectors.
     */
    VectorN<TypeT, SizeT> operator-(VectorN<TypeT, SizeT> other) const {
        other -= (*this);
        return other;
    }

    /*
     *  \fn Addition Operator
     *  \brief Adds a scalar to each element of a vector.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to add to each element.
     *  \return A new vector which has the value added to each element.
     */
    template <typename ScalarT>
    VectorN<TypeT, SizeT> operator+(const ScalarT& value) const {
        VectorN<TypeT, SizeT> ret(*this);
        ret += value;
        return ret;
    }

    /*
     *  \fn Subtraction Operator
     *  \brief Subtracts a scalar from each element of a vector.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to subtract from each element.
     *  \return A new vector which has the value subtracted from each element.
     */
    template <typename ScalarT>
    VectorN<TypeT, SizeT> operator-(const ScalarT& value) const {
        VectorN<TypeT, SizeT> ret(*this);
        ret -= value;
        return ret;
    }

    /*
     *  \fn Multiplication Operator
     *  \brief Multiplies each element by a scalar.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to multiply each element by.
     *  \return A new vector which is multiplied by the scalar.
     */
    template <typename ScalarT>
    VectorN<TypeT, SizeT> operator*(const ScalarT& value) const {
        VectorN<TypeT, SizeT> ret(*this);
        ret *= value;
        return ret;
    }

    /*
     *  \fn Division Operator
     *  \brief Divides each element by a scalar.
     *
     *  \tparam ScalarT The scalar type. This will usually be a plain
     *          data type.
     *  \param value The value to divide each element by.
     *  \return A new vector which is divided by the scalar.
     */
    template <typename ScalarT>
    VectorN<TypeT, SizeT> operator/(const ScalarT& value) const {
        VectorN<TypeT, SizeT> ret(*this);
        ret /= value;
        return ret;
    }

    /*
     *  \fn Sum
     *  \brief Adds all elements in a vector together into one value.
     *
     *  \return The sum of all the elements.
     */
    TypeT Sum() const {
        return std::accumulate(data_.begin(), data_.end(), 0);
    }

    /*
     *  \fn Product
     *  \brief Multiples all the elements in a vector together.
     *
     *  \return The product of all the elements.
     */
    TypeT Product() const {
        return std::accumulate(
                v.begin(), v.end(), 1, std::multiplies<TypeT>());
    }

    /*
     *  \fn SumSquares
     *  \brief Adds the squares of all the elements together.
     *
     *  \return The sum of all the squares of the elements.
     */
    TypeT SumSquares() const {
        return std::inner_product(
                data_.begin(), data_.end(), data_.begin(), 0);
    }

    /*
     *  \fn Length
     *  \brief Calculates the magnitude of a vector. If you just need a
     *         comparison between two lengths then LengthSquared is slightly
     *         more efficient.
     *
     *  \return The length of the vector.
     */
    double Length() const {
        return std::sqrt(SumSquares());
    }

    /*
     *  \fn LengthSquared
     *  \brief Calculates the magnitude of the vector without the final square
     *         root. Use this instead of Length if you just need to compare
     *         two lengths.
     *
     *  \return The length of the vector squared.
     */
    double LengthSquared() const {
        return SumSquares();
    }

    /*
     *  \fn Normalize
     *  \brief Normalizes a vector so it has a length of 1.
     */
    void Normalize() {
        (*this) /= Length();
    }

protected:
    std::array<TypeT, SizeT> data_;
};
}

#endif

