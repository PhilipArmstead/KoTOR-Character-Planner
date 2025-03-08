#pragma once

#include <stdint.h>


typedef struct {
	float attackModifierPerLevel;
	uint8_t vitalityPerLevel;
} ClassModifier;

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
	ClassModifier modifier;
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
	*/
	uint8_t growthSpeed;
	/**
	 * Bits 1-2 must contain a SaveGrowthSpeed value representing Fortitude
	 * Bits 3-5 must contain a SaveGrowthSpeed value representing Reflex
	 * Bits 3-5 must contain a SaveGrowthSpeed value representing Will
	*/
	uint8_t saveGrowthSpeed;
} Class;

// 	JEDI_GUARDIAN: {
// 		name: 'Jedi Guardian',
// 		modifier: {
// 			vitalityPerLevel: 10,
// 			forcePointsPerLevel: 4,
// 			attackModifierPerLevel: 1,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: saveGrowthSpeed.FAST,
// 			[saveEnum.REFLEX]: saveGrowthSpeed.FAST,
// 			[saveEnum.WILL]: saveGrowthSpeed.AVERAGE,
// 		},
// 		skillGrowth: skillGrowthEnum.SLOW,
// 		featAllowance: featGrowthMap.MEDIUM_SLOWER,
// 		isForceSensitive: true,
// 		hasInnateDefence: true, // Up to 6 defence
// 	},
// 	JEDI_SENTINEL: {
// 		name: 'Jedi Sentinel',
// 		modifier: {
// 			vitalityPerLevel: 8,
// 			forcePointsPerLevel: 6,
// 			attackModifierPerLevel: 0.75,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: saveGrowthSpeed.FAST,
// 			[saveEnum.REFLEX]: saveGrowthSpeed.FAST,
// 			[saveEnum.WILL]: saveGrowthSpeed.AVERAGE,
// 		},
// 		skillGrowth: skillGrowthEnum.MEDIUM,
// 		featAllowance: featGrowthMap.SLOWER,
// 		isForceSensitive: true,
// 		hasInnateDefence: true, // Up to 6 defence
// 	},
// 	JEDI_CONSULAR: {
// 		name: 'Jedi Consular',
// 		modifier: {
// 			vitalityPerLevel: 6,
// 			forcePointsPerLevel: 8,
// 			attackModifierPerLevel: 0.75,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: saveGrowthSpeed.FAST,
// 			[saveEnum.REFLEX]: saveGrowthSpeed.AVERAGE,
// 			[saveEnum.WILL]: saveGrowthSpeed.FAST,
// 		},
// 		skillGrowth: skillGrowthEnum.SLOW,
// 		featAllowance: featGrowthMap.SLOWER,
// 		isForceSensitive: true,
// 		hasInnateDefence: true, // Up to 6 defence
// 	},
// 	COMBAT_DROID: {
// 		name: 'Combat Droid',
// 		modifier: {
// 			vitalityPerLevel: 12,
// 			attackModifierPerLevel: 1,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: saveGrowthSpeed.FAST,
// 			[saveEnum.REFLEX]: saveGrowthSpeed.SLOW,
// 			[saveEnum.WILL]: saveGrowthSpeed.SLOW,
// 		},
// 		skillGrowth: skillGrowthEnum.SLOW,
// 		featAllowance: featGrowthMap.SLOWER,
// 		hasInnateDefence: true, // Up to 6 defence
// 	},
// 	EXPERT_DROID: {
// 		name: 'Expert Droid',
// 		modifier: {
// 			vitalityPerLevel: 8,
// 			attackModifierPerLevel: 0.75,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: saveGrowthSpeed.SLOW,
// 			[saveEnum.REFLEX]: saveGrowthSpeed.FAST,
// 			[saveEnum.WILL]: saveGrowthSpeed.SLOW,
// 		},
// 		skillGrowth: skillGrowthEnum.MEDIUM,
// 		featAllowance: featGrowthMap.MEDIUM_SLOW,
// 		hasInnateDefence: true, // Up to 6 defence
// 	},
// 	MINION: {
// 		// TODO: merge with Soldier
// 		name: 'Minion',
// 		modifier: {
// 			vitalityPerLevel: 10,
// 			attackModifierPerLevel: 1,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: saveGrowthSpeed.FAST,
// 			[saveEnum.REFLEX]: saveGrowthSpeed.SLOW,
// 			[saveEnum.WILL]: saveGrowthSpeed.SLOW,
// 		},
// 	},
// 	SITH_SOLDIER_NEWBIE: {
// 		name: 'Sith Soldier',
// 		modifier: {
// 			vitalityPerLevel: 15,
// 			attackModifierPerLevel: 1,
// 		},
// 		saveGrowth: {
// 			[saveEnum.FORTITUDE]: saveGrowthSpeed.FAST,
// 			[saveEnum.REFLEX]: saveGrowthSpeed.SLOW,
// 			[saveEnum.WILL]: saveGrowthSpeed.SLOW,
// 		},
// 	},
// })
