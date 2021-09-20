#ifndef INCLUDE_PERLIN_H
#define INCLUDE_PERLIN_H

#include "def.h"
#include "vec.h"
#include <cmath>

/** PerlinNoise generates perlin noise */
class PerlinNoise{
    float seed;
    inline float interpolate(float a0, float a1, float weight);
    fvec2 randomGradient(int x, int y);
    float dotGridGradient(int ix, int iy, float fx, float fy);
public:
    /**Generate Perlin noise using seed*/
    PerlinNoise(float seed);
    /**Return perlin noise value at coords {fx, fy}*/
    float operator()(float fx, float fy);
};

#endif
