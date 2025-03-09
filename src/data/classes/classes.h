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
	*/
	uint8_t data1;
	/**
	 * Saves
	 * --
	 * Bits 1-2 must contain a SaveGrowthSpeed value representing Fortitude
	 * Bits 3-4 must contain a SaveGrowthSpeed value representing Reflex
	 * Bits 5-6 must contain a SaveGrowthSpeed value representing Will
	 *
	 * Secondary class
	 * --
	 * Bit 7 must contain 1 if the class can become a Jedi
	*/
	uint8_t data2;
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
// 	MINION: {
// 		// TODO: merge with Soldier
// 		name: 'Minion',
// 		modifier: {
// 			vitalityPerLevel: 10,
// 			attackModifierPerLevel: 1,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: data2.FAST,
// 			[saveEnum.REFLEX]: data2.SLOW,
// 			[saveEnum.WILL]: data2.SLOW,
// 		},
// 	},
// 	SITH_SOLDIER_NEWBIE: {
// 		name: 'Sith Soldier',
// 		modifier: {
// 			vitalityPerLevel: 15,
// 			attackModifierPerLevel: 1,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: data2.FAST,
// 			[saveEnum.REFLEX]: data2.SLOW,
// 			[saveEnum.WILL]: data2.SLOW,
// 		},
// 	},
// })
