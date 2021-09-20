#ifndef INCLUDE_DEF_H
#define INCLUDE_DEF_H

#include <cstddef>
#include <cstdint>


typedef uint64_t coord_t;
struct color {
	uint8_t r, g, b, a;
};


const color clr_black = {0, 0, 0, 255};
const color clr_white = {255, 255, 255, 255};
const color clr_red = {255, 0, 0, 255};
const color clr_green = {0, 255, 0, 255};
const color clr_blue = {0, 0, 255, 255};


#endif
