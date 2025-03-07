#pragma once

#include <stdint.h>


#define false 0
#define true 1

typedef struct {
	uint8_t strength;
	uint8_t dexterity;
	uint8_t constitution;
	uint8_t intelligence;
	uint8_t wisdom;
	uint8_t charisma;
} Attributes;

typedef struct {
	uint16_t x;
	uint16_t y;
} RectangleU16;
