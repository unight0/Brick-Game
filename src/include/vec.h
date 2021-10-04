#ifndef INCLUDE_VEC_H
#define INCLUDE_VEC_H

#include "def.h"
#include <iostream> //std::initializer_list<T>


enum VectorDimensions {
    _x = 0,
    _y = 1,
    _z = 2,
    _j = 3,
    _k = 4,
    _l = 5
};

/** This is a vector class definition 
 T - type(int, float, etc.), D - dimensions(1, 2, 3, 4...)*/
template <typename T, uint8_t D>
struct vec {
public:
    T coords[D];

    /** Get reference to dimens dimension
      * @param VectorDimensions dimens -- dimension to get 
      * @return T& -- reference to dimension */
    T &operator[](VectorDimensions dimens);

    /** Get reference to dimens dimension
      * @param uint8_t dimens -- dimension to get 
      * @return T& -- reference to dimension */
    T &operator[](uint8_t dimens);
    
    /** Sets value of this vector to v vector
      * @param vec<T,D> v -- vector to set this vector to 
      * @return vec<T,D> -- value for chain equality like this:
      * v1 = v2 = v3 = v4... = vN*/
    vec<T, D> operator=(vec<T, D> v);
    
    /** Sums two vectors: this and v
      * @param vec<T,D> v -- vector to sum with this vector 
      * @return vec<T,D> -- sum of this and v */
    vec<T, D> operator+(vec<T, D> v);
    
    /** Substracts two vectors: this and v
      * @param vec<T,D> v -- vector to be substracted from this vector
      * @return vec<T,D> -- sub of this vector and v*/
    vec<T, D> operator-(vec<T, D> v);
    
    /** Sums two vectors: this and v and writes result to this
      * @param vec<T,D> v -- vector to sum with this vector
      * @return reference to this because of what you would
      * expect from this expression: `(v1 += v2) = v3`*/
    vec<T, D> &operator+=(vec<T, D> v);

    /** Substracts two vectors: this and v and writes result to this
      * @param vec<T,D> v -- vector to substract with this vector
      * @return reference to this because of what you would
      * expect from this expression: `(v1 -= v2) = v3`*/
    vec<T, D> &operator-=(vec<T, D> v);
    
    /** Tests equality of two vectors: this and v
      * @param vec<T,D> b -- vector to test equality to
      * @return bool result */
    bool operator==(vec<T, D> v);

    /** Tests unequality of two vectors: this and v
      * @param vec<T,D> b -- vector to test equality to
      * @return bool result */
    bool operator!=(vec<T, D> v);

    /** Constructors */
    template <typename T1, uint8_t D1>
    vec(const vec<T1, D1> &v);

    vec(const vec<T, D> &v);
    vec(T arr[D]);
    vec(std::initializer_list<T> lst);
    vec();
};


typedef vec<float, 2> fvec2;
typedef vec<int64_t, 2> ivec2;
typedef vec<uint64_t, 2> uvec2;
typedef vec<float, 3> fvec3;
typedef vec<int64_t, 3> ivec3;
typedef vec<uint64_t, 3> uvec3;
typedef vec<float, 4> fvec4;
typedef vec<int64_t, 4> ivec4;
typedef vec<uint64_t, 4> uvec4;


/* Definition goes down below */


#include <cassert>  //assert()
#include <typeinfo>

template <typename T, uint8_t D>
T & vec<T, D>::
operator[](VectorDimensions dimens) {
    return coords[dimens];
}

template <typename T, uint8_t D>
T & vec<T, D>::
operator[](uint8_t dimens) {
    return coords[dimens];
}

template <typename T, uint8_t D>
vec<T, D> vec<T, D>::
operator=(vec<T, D> v) {
    for(uint8_t ptr = 0; ptr < D; ptr++) {
        coords[ptr] = v[ptr];
    }
    return v;
}

template <typename T, uint8_t D>
vec<T, D> vec<T, D>::
operator+(vec<T, D> v) {
    vec<T, D> result = *this;
    for(uint8_t ptr = 0; ptr < D; ptr++) {
        result[ptr] += v[ptr];
    }
    return result;
}

template <typename T, uint8_t D>
vec<T, D> vec<T, D>::
operator-(vec<T, D> v) {
    vec<T, D> result = *this;
    for(uint8_t ptr = 0; ptr < D; ptr++) {
        result[ptr] -= v[ptr];
    }
    return result;
}

template <typename T, uint8_t D>
vec<T, D> & vec<T, D>::
operator+=(vec<T, D> v) {
    for(uint8_t ptr = 0; ptr < D; ptr++) {
        coords[ptr] += v[ptr];
    }
    return this;
}

template <typename T, uint8_t D>
vec<T, D> & vec<T, D>::
operator-=(vec<T, D> v) {
    for(uint8_t ptr = 0; ptr < D; ptr++) {
       coords[ptr] -= v[ptr];
    }
    return this;
}

template <typename T, uint8_t D>
bool vec<T, D>::
operator==(vec<T, D> v) {
    bool equal = false;
    for(uint8_t ptr = 0; ptr < D; ptr++) {
        equal = (coords[ptr] == v[ptr]);
    }
    return equal;
}

template <typename T, uint8_t D>
bool vec<T, D>::
operator!=(vec<T, D> v) {
    return !(*this == v);
}


template <typename T, uint8_t D>
vec<T, D>::
vec() {
    for(uint8_t ptr = 0; ptr < D; ptr++) {
        coords[ptr] = 0;
    }
}

template <typename T, uint8_t D>
template <typename T1, uint8_t D1>
vec<T, D>::
vec(const vec<T1, D1> &v) {
    if(D == D1 || D < D1) {
        for(uint8_t ptr = 0; ptr < D; ptr++) {
            coords[ptr] = (T)v.coords[ptr];
        }
    }
    else if(D > D1) {
        for(uint8_t ptr = 0; ptr < D1; ptr++) {
            coords[ptr] = (T)v.coords[ptr];
        }
        for(uint8_t ptr = D1; ptr < D; ptr++) {
            coords[ptr] = 0;
        }
    }
}


template <typename T, uint8_t D>
vec<T, D>::
vec(const vec<T, D> &v) {
    for(uint8_t ptr = 0; ptr < D; ptr++) {
        coords[ptr] = v.coords[ptr];
    }
}


template <typename T, uint8_t D>
vec<T, D>::
vec(T arr[D]) {
    uint8_t ptr;
    for(ptr = 0; ptr < D; ptr++) {
        coords[ptr] = arr[ptr];
    }
}

template <typename T, uint8_t D>
vec<T, D>::
vec(std::initializer_list<T> lst) {
    assert(lst.size() <= D); // if not, abort
    std::copy(lst.begin(), lst.end(), coords);
}

#endif
