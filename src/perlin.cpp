#include "include/perlin.h"

PerlinNoise::
PerlinNoise(float seed) {
    this->seed = seed;
}

//weight shoud be from 0 to 1
inline float PerlinNoise::
interpolate(float a0, float a1, float weight) {
	return (a1 - a0) * weight + a0;
}

fvec2 PerlinNoise::
randomGradient(int x, int y) {
	float rand = 2920.f * sin(x * 21942.f + y * 171324.f + 8912.f) * cos(x * 23157.f * y * 217832.f + 9758.f);
	return fvec2({(float)cos(rand), (float)sin(rand)});
}

float PerlinNoise::
dotGridGradient(int ix, int iy, float fx, float fy) {
	fvec2 grad = randomGradient(ix, iy);
	float dx = fx - ix;
	float dy = fy - iy;
	return (dx * grad[_x] + dy * grad[_y]);
}


float PerlinNoise::
operator()(float fx, float fy) {
	int ix0 = (int)fx;
	int ix1 = ix0 + 1;
	int iy0 = (int)fy;
	int iy1 = iy0 + 1;

	//Interpolation weights
	float fwx = fx - ix0;
	//float fwy = fy - iy0;

	//Interpolate between grid points gradients
	float fn0, fn1, ix3, ix4;

	fn0 = dotGridGradient(ix0, iy0, fx, fy);
	fn1 = dotGridGradient(ix1, iy0, fx, fy);
	ix3 = interpolate(fn0, fn1, fwx);

	fn0 = dotGridGradient(ix0, iy1, fx, fy);
	fn1 = dotGridGradient(ix1, iy1, fx, fy);
	ix4 = interpolate(fn0, fn1, fwx);

	float z = 10.f * seed;
	float retVal = interpolate(ix3, ix4, z);
	return retVal;
}
