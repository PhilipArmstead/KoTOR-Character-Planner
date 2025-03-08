#pragma once

#include "types.h"


inline uint8_t getSkillGrowth(const uint8_t growthSpeed) {
	return (growthSpeed & 3) + 1;
}

uint8_t getSkillAllowance(uint8_t growthSpeed, uint8_t level, int8_t intelligenceModifier);
