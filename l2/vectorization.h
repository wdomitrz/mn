// ---------------------------------------------------------------------
//
// Copyright (C) 2011 - 2019 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------


#ifndef dealii_vectorization_h
#define dealii_vectorization_h

#include <cmath>
#include <type_traits>
#include <array>

// Note:
// The flag DEAL_II_COMPILER_VECTORIZATION_LEVEL is essentially constructed
// according to the following scheme (on x86-based architectures)
// #ifdef __AVX512F__
// #define DEAL_II_COMPILER_VECTORIZATION_LEVEL 3
// #elif defined (__AVX__)
// #define DEAL_II_COMPILER_VECTORIZATION_LEVEL 2
// #elif defined (__SSE2__)
// #define DEAL_II_COMPILER_VECTORIZATION_LEVEL 1
// #else
// #define DEAL_II_COMPILER_VECTORIZATION_LEVEL 0
// #endif
// In addition to checking the flags __AVX__ and __SSE2__, a CMake test,
// 'check_01_cpu_features.cmake', ensures that these feature are not only
// present in the compilation unit but also working properly.

#define DEAL_II_NAMESPACE_CLOSE
#define DEAL_II_NAMESPACE_OPEN

#define DEAL_II_ALWAYS_INLINE inline

#define DEAL_II_COMPILER_VECTORIZATION_LEVEL 4


#    include <x86intrin.h>




DEAL_II_NAMESPACE_OPEN




template <typename Number, int width>
class VectorizedArray
{
public:
  /**
   * This gives the type of the array elements.
   */
  typedef Number value_type ;



  /**
   * This gives the number of elements collected in this class. In the general
   * case, there is only one element. Specializations use SIMD intrinsics and
   * can work on multiple elements at the same time.
   */
  static const unsigned int n_array_elements = width;


  // POD means that there should be no user-defined constructors, destructors
  // and copy functions (the standard is somewhat relaxed in C++2011, though).

  /**
   * Default empty constructor, leaving the data in an uninitialized state
   * similar to float/double.
   */
  VectorizedArray() = default;

  /**
   * Construct an array with the given scalar broadcast to all lanes.
   */
  VectorizedArray(const Number scalar)
  {
    this->operator=(scalar);
  }

  /**
   * This function assigns a scalar to this class.
   */
  DEAL_II_ALWAYS_INLINE
  VectorizedArray &
  operator=(const Number scalar)
  {
	  for(unsigned int i=0; i<width; ++i )
		  data[i] = scalar;
    return *this;
  }

  /**
   * Return the number of elements in the array stored in the variable
   * n_array_elements.
   */
  static constexpr unsigned int
  size()
  {
    return n_array_elements;
  }

  /**
   * Access operator (only valid with component 0 in the base class without
   * specialization).
   */
  DEAL_II_ALWAYS_INLINE
  Number &operator[](const unsigned int comp)
  {

//    AssertIndexRange(comp, width);
    return data[comp];
  }

  /**
   * Constant access operator (only valid with component 0 in the base class
   * without specialization).
   */
  DEAL_II_ALWAYS_INLINE
  const Number &operator[](const unsigned int comp) const
  {

//    AssertIndexRange(comp, width);
    return data[comp];
  }

  /**
   * Addition
   */
  DEAL_II_ALWAYS_INLINE
  VectorizedArray &
  operator+=(const VectorizedArray &vec)
  {
	  for(unsigned int i=0; i<width; ++i )
		  this->data[i] += vec.data[i];
    return *this;
  }

  /**
   * Subtraction
   */
  DEAL_II_ALWAYS_INLINE
  VectorizedArray &
  operator-=(const VectorizedArray &vec)
  {
	  for(unsigned int i=0; i<width; ++i )
		  this->data[i] -= vec.data[i];
    return *this;
  }

  /**
   * Multiplication
   */
  DEAL_II_ALWAYS_INLINE
  VectorizedArray &
  operator*=(const VectorizedArray &vec)
  {
	  for(unsigned int i=0; i<width; ++i )
		  this->data[i] *= vec.data[i];
    return *this;
  }

  /**
   * Division
   */
  DEAL_II_ALWAYS_INLINE
  VectorizedArray &
  operator/=(const VectorizedArray &vec)
  {
	  for(unsigned int i=0; i<width; ++i )
		  this->data[i] /= vec.data[i];
    return *this;
  }

  /**
   * Load @p n_array_elements from memory into the calling class, starting at
   * the given address. The pointer `ptr` needs not be aligned by the amount
   * of bytes in the vectorized array, as opposed to casting a double address
   * to VectorizedArray<double>*.
   */
  DEAL_II_ALWAYS_INLINE
  void
  load(const Number *ptr)
  {
	  for(unsigned int i=0; i<width; ++i )
		  this->data[i] = *(ptr+i);
  }

  /**
   * Write the content of the calling class into memory in form of @p
   * n_array_elements to the given address. The pointer `ptr` needs not be
   * aligned by the amount of bytes in the vectorized array, as opposed to
   * casting a double address to VectorizedArray<double>*.
   */
  DEAL_II_ALWAYS_INLINE
  void
  store(Number *ptr) const
  {
	  for(unsigned int i=0; i<width; ++i )
		  *(ptr + i)= data[i];
  }

  DEAL_II_ALWAYS_INLINE
  void
  streaming_store(Number *ptr) const
  {
	  for(unsigned int i=0; i<width; ++i )
		  *(ptr+i) = data[i];
  }

  /**
   * Load @p n_array_elements from memory into the calling class, starting at
   * the given address and with given offsets, each entry from the offset
   * providing one element of the vectorized array.
   *
   * This operation corresponds to the following code (but uses a more
   * efficient implementation in case the hardware allows for that):
   * @code
   * for (unsigned int v=0; v<VectorizedArray<Number>::n_array_elements; ++v)
   *   this->operator[](v) = base_ptr[offsets[v]];
   * @endcode
   */
//  DEAL_II_ALWAYS_INLINE
//  void
//  gather(const Number *base_ptr, const unsigned int *offsets)
//  {
//    data = base_ptr[offsets[0]];
//  }

  /**
   * Write the content of the calling class into memory in form of @p
   * n_array_elements to the given address and the given offsets, filling the
   * elements of the vectorized array into each offset.
   *
   * This operation corresponds to the following code (but uses a more
   * efficient implementation in case the hardware allows for that):
   * @code
   * for (unsigned int v=0; v<VectorizedArray<Number>::n_array_elements; ++v)
   *   base_ptr[offsets[v]] = this->operator[](v);
   * @endcode
   */
//  DEAL_II_ALWAYS_INLINE
//  void
//  scatter(const unsigned int *offsets, Number *base_ptr) const
//  {
//    base_ptr[offsets[0]] = data;
//  }

  /**
   * Actual data field. Since this class represents a POD data type, it is
   * declared public.
   */
//  Number data;
  std::array<Number, width> data;

};

#endif
