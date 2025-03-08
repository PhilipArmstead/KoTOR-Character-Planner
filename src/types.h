#pragma once

#include <stdbool.h>
#include <stdint.h>


#define CLASS_COUNT 8

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
