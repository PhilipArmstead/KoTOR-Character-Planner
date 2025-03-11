#pragma once

#include "character.h"
#include "types.h"
#include "data/classes/classes.h"
#include "data/species/species.h"


extern const Class classes[CLASS_COUNT];

inline uint8_t getSpecies(const Character *character) {
	return character->data >> 5 & 3;
}

inline uint8_t getPrimaryClassIndex(const Character *character) {
	return character->data & 7;
}

inline uint8_t getSecondaryClassIndex(const Character *character) {
	return character->data >> 3 & 3;
}

inline bool getCanClassBecomeJedi(const Character *character) {
	return getSpecies(character) == SPECIES_HUMANOID;
}

inline int8_t getModifier(int16_t attribute) {
	attribute -= 10;
	return attribute / 2 - (attribute % 2 != 0 && (attribute ^ 2) < 0);
}

inline float getAttackPerLevel(const Class class) {
	return class.data1 & 128 ? 1 : 0.75;
}

inline uint8_t getVitalityPerLevel(const Class class) {
	const uint8_t value = class.data1 >> 5 & 3;
	if (value == 0) {
		return 6;
	}

	if (value == 1) {
		return 8;
	}

	if (value == 2) {
		return 10;
	}

	return 12;
}

inline uint8_t getDefence(const uint8_t dexterity) {
#define BASE 10

	int8_t modifier = getModifier(dexterity);
	// Dexterity bonus
	{
		// TODO: implement armour
		// const int8_t maxDexterityBonus = this.equipment.get(EquipmentSlot.BODY).maxDexterityBonus;
		const int8_t maxDexterityBonus = -1;
		if (maxDexterityBonus > -1 && maxDexterityBonus < modifier) {
			modifier = maxDexterityBonus;
		}
	}

	// TODO: dexterity bonuses from feats, equipment, status
	// TODO: defence bonuses from feats, equipment, status

	return BASE + modifier;

	// // Defence modifiers
	// Object.entries(this.getBonus(Bonus.DEFENCE).log).forEach(([key, value]) => log[key] += value)
	//
	// return {
	// 	total: Math.floor(Object.entries(log).reduce((total, [, value]) => total + value, 0)),
	// 	log,
	// }
}

// inline void getAttack() {
// 	// TODO: bonuses from feats, class, equipment, status
// 	// const attackBonus = this.getBonus(Bonus.ATTACK)
// 	// TODO: bonuses from feats, class, equipment, status
// 	// const attackBonusPerLevel = this.getBonus(Bonus.ATTACK_BONUS_PER_LEVEL, true)
//
// 	// return Math.floor(attackBonus.total + attackBonusPerLevel.total),
// }

inline uint16_t getVitality(const Character *character) {
	const Class class1 = classes[getPrimaryClassIndex(character)];
	const Class class2 = classes[getSecondaryClassIndex(character)];
	const uint8_t level1 = character->level1;
	const uint8_t level2 = character->level2 * getCanClassBecomeJedi(character);
	float vitality = getModifier(character->attributes.constitution) * (level1 + level2);

	vitality += getVitalityPerLevel(class1) * level1;
	vitality += getVitalityPerLevel(class2) * level2;


	// TODO: bonuses from feats, equipment, status
	// Feat/power/equipment etc. bonuses
	// maxVitality += this.getBonus(Bonus.VITALITY_BONUS_PER_LEVEL).total * level

	return vitality;
}

// inline uint16_t getForcePoints() {
// uint16_t maxForcePoints = 0;
//
// if (this.isForceSensitive) {
// 	const level
// 	=
// 	this.level
//
// 	// From (charisma + wisdom modifiers) * levels
// 	const charismaModifier
// 	=
// 	Character.getModifierFromAttributeValue(this.getAttributeTotal(Attribute.CHARISMA))
// 	const wisdomModifier
// 	=
// 	Character.getModifierFromAttributeValue(this.getAttributeTotal(Attribute.WISDOM))
// 	maxForcePoints += (charismaModifier + wisdomModifier) * level
//
// 	// Feat/power/equipment etc. bonuses
// 	maxForcePoints += this.getBonus(Bonus.FORCE_POINTS_BONUS_PER_LEVEL, true).total
// 	maxForcePoints += this.getBonus(Bonus.FORCE_POINTS).total
// }
// 	return Math.max(Math.floor(maxForcePoints), 0);
// }

// inline void calculateAttackWithWeapon () {
// // Get weapon attack modifier from Strength/Dexterity stat
// // Is the weapon a lightsaber? Pick the highest stat from dexterity or strength if so.
// // Otherwise pick the appropriate stat for the weapon type (ranged: dexterity, melee: strength)
// let weaponAttackModifier = weapon.class.attributesForAttackModifier.reduce((total, attribute) => {
// 	return Math.max(total, Character.getModifierFromAttributeValue(this.getAttributeTotal(attribute)))
// }, 0)

// // If we're dual-wielding, add negative modifiers to main/off-hand attack
// if (offHandItem || mainHandItem.attributes.includes(WeaponAttribute.DUAL_BLADED)) {
// 	if (!isOffHand) {
// 		// Subtract penalty
// 		weaponAttackModifier -= 6
//
// 		// Add dual-wield attack bonuses
// 		weaponAttackModifier += this.getBonus(Bonus.DUAL_WIELD_ATTACK_BONUS_MAIN_HAND).total
//
// 		// If our off-hand weapon is balanced, add +2 right back to our main-hand attack
// 		if (offHandItem?.attributes.includes(WeaponAttribute.BALANCED)) {
// 			weaponAttackModifier += 2
// 		}
// 	} else {
// 		// Subtract penalty
// 		weaponAttackModifier -= 10
//
// 		// Add dual-wield attack bonuses
// 		weaponAttackModifier += this.getBonus(Bonus.DUAL_WIELD_ATTACK_BONUS_OFF_HAND).total
// 	}
// }
//
// const attackBonus = weapon.bonuses?.get(Bonus.ATTACK) || 0
//
// return weaponAttackModifier + attackBonus + this.attack.total
// }

inline enum FeatGrowthSpeed getFeatGrowth(const uint8_t characterData) {
	return characterData >> 2 & 7;
}

inline uint8_t getSkillGrowth(const uint8_t characterData) {
	return (characterData & 3) + 1;
}

uint8_t getFeatAllowance(uint8_t characterData, uint8_t level);
uint8_t getSkillAllowance(uint8_t characterData, uint8_t level, int8_t intelligenceModifier);
