#pragma once

#include "data/classes/classes.h"


inline int8_t getModifier(uint8_t attribute) {
	attribute -= 10;
	return attribute / 2 - (attribute % 2 != 0 && (attribute ^ 2) < 0);
}

inline uint8_t getDefence(uint8_t dexterity) {
#define BASE 10

	// Dexterity bonus
	// TODO: implement armour
	const uint8_t modifier = getModifier(dexterity);
	// const int8_t maxDexterityBonus = this.equipment.get(EquipmentSlot.BODY).maxDexterityBonus;
	const int8_t maxDexterityBonus = 127;
	dexterity = BASE + 2 * (modifier < maxDexterityBonus ? modifier : maxDexterityBonus);

	// TODO: bonuses from feats, equipment, status
	// dexterity += this.getBonus(Attribute.DEXTERITY.bonus).total

	// TODO: bonuses from feats, equipment, status
	// // Defence modifiers
	// Object.entries(this.getBonus(Bonus.DEFENCE).log).forEach(([key, value]) =  > log[key] += value)

	return BASE + getModifier(dexterity);
}

// inline void getAttack() {
// 	// TODO: bonuses from feats, class, equipment, status
// 	// const attackBonus = this.getBonus(Bonus.ATTACK)
// 	// TODO: bonuses from feats, class, equipment, status
// 	// const attackBonusPerLevel = this.getBonus(Bonus.ATTACK_BONUS_PER_LEVEL, true)
//
// 	// return Math.floor(attackBonus.total + attackBonusPerLevel.total),
// }

inline uint16_t getVitality(const uint8_t level, const uint8_t vitalityPerLevel, const uint8_t constitution) {
	float vitality = getModifier(constitution) * level;

	vitality += vitalityPerLevel * level;


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

inline enum FeatGrowthSpeed getFeatGrowth(const uint8_t growthSpeed) {
	return growthSpeed >> 2 & 7;
}

inline uint8_t getSkillGrowth(const uint8_t growthSpeed) {
	return (growthSpeed & 3) + 1;
}

uint8_t getFeatAllowance(uint8_t growthSpeed, uint8_t level);
uint8_t getSkillAllowance(uint8_t growthSpeed, uint8_t level, int8_t intelligenceModifier);
