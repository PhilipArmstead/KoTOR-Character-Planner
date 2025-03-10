#pragma once

#include <raylib.h>
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
	Attributes attributes;
	/**
	 * Bits 1-3 must contain a number 0-5, representing a non-Jedi class index
	 * Bits 4-5 must contain a number 1-3, representing a Jedi class index
	 */
	uint8_t classIndices;
	uint8_t level1;
	uint8_t level2;
} Character;


typedef struct {
	Vector2 position;
	bool isPressed;
} MouseContext;


typedef struct {
	int16_t x;
	int16_t y;
	int16_t width;
	int16_t height;
} RectangleI16;

typedef struct {
	uint16_t x;
	uint16_t y;
} PointU16;


typedef struct {
	Texture arrowLeft;
	Texture arrowRight;
	PointU16 contentPosition;
} AttributesContext;
