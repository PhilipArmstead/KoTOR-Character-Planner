#pragma once

#include <stdint.h>


#define INDEX_JEDI_START 5

enum VitalityPerLevel {
	VITALITY_PER_LEVEL_6,
	VITALITY_PER_LEVEL_8,
	VITALITY_PER_LEVEL_10,
	VITALITY_PER_LEVEL_12,
};

enum SaveGrowthSpeed {
	SAVE_GROWTH_SLOW,
	SAVE_GROWTH_AVERAGE,
	SAVE_GROWTH_FAST,
};

enum FeatGrowthSpeed {
	FEAT_GROWTH_SLOWER,
	FEAT_GROWTH_SLOW,
	FEAT_GROWTH_AVERAGE,
	FEAT_GROWTH_QUICK,
	FEAT_GROWTH_FAST,
	FEAT_GROWTH_FASTER,
};

typedef struct {
	char name[16];
	/**
	 * Skills
	 * --
	 * Bits 1-2 must contain a number 0-3, representing x in the following formulae:
	 * ((x + 1) + INT) * 4 on character creation
	 * (x + 1) + INT / 2   on level up
	 *
	 * Feats
	 * --
	 * Bits 3-5 must contain a FeatGrowthSpeed value
	 *
	 * Vitality per level
	 * --
	 * Bits 6-7 must contain a number 0-3, representing 6, 8, 10 and 12
	 * vitality points per level respectively.
	 *
	 * Attack modifier per level
	 * --
	 * Bit 8 must contain 1 if the modifier is linear or 0 if it is level * 0.75
	 *
	 * Saves
	 * --
	 * Bits 9-10 must contain a SaveGrowthSpeed value representing Fortitude
	 * Bits 11-12 must contain a SaveGrowthSpeed value representing Reflex
	 * Bits 13-14 must contain a SaveGrowthSpeed value representing Will
	 *
	*/
	uint16_t data;
} Class;

// 	JEDI_GUARDIAN: {
// 		forcePointsPerLevel: 4,
// 	},
// 	JEDI_SENTINEL: {
// 		forcePointsPerLevel: 6,
// 	},
// 	JEDI_CONSULAR: {
// 		forcePointsPerLevel: 8,
// 	},
