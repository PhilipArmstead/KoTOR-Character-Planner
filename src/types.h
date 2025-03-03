#pragma once

#include <stdint.h>


#define false 0
#define true 1

typedef struct {
	uint8_t value;
	int8_t modifier;
} Attribute;

typedef struct {
	Attribute strength;
	Attribute dexterity;
	Attribute constitution;
	Attribute intelligence;
	Attribute wisdom;
	Attribute charisma;
} Attributes;
