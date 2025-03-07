#include <raylib.h>
#include <stdio.h>

#include "attributes.h"
#include "ui-constants.h"
#include "../types.h"


static inline uint8_t getDefence(uint8_t dexterity) {
#define BASE 10

	// // Class bonus
	// log.class = this.classes.reduce((best, { class: { defenceBonus }, level }) => {
	// 	return Math.min(best + defenceBonus(level), 10)
	// }, 0)

	// Dexterity bonus
	// TODO: implement armour
	const uint8_t modifier = getModifier(dexterity);
	// const int8_t maxDexterityBonus = this.equipment.get(EquipmentSlot.BODY).maxDexterityBonus;
	const int8_t maxDexterityBonus = 127;
	dexterity = BASE + 2 * (modifier < maxDexterityBonus ? modifier : maxDexterityBonus);

	// TODO: bonuses from feats, class, equipment, status
	// dexterity += this.getBonus(Attribute.DEXTERITY.bonus).total

	// TODO: bonuses from feats, class, equipment, status
	// // Defence modifiers
	// Object.entries(this.getBonus(Bonus.DEFENCE).log).forEach(([key, value]) =  > log[key] += value)

	return BASE + getModifier(dexterity);
}

// static inline void getAttack() {
// 	// TODO: bonuses from feats, class, equipment, status
// 	// const attackBonus = this.getBonus(Bonus.ATTACK)
// 	// TODO: bonuses from feats, class, equipment, status
// 	// const attackBonusPerLevel = this.getBonus(Bonus.ATTACK_BONUS_PER_LEVEL, true)
//
// 	// return Math.floor(attackBonus.total + attackBonusPerLevel.total),
// }

static inline uint16_t getVitality(const uint8_t constitution) {
	const uint8_t level = 1; // TODO

	// From constitution modifier * levels
	float maxVitality = getModifier(constitution) * level;

	// TODO: bonuses from feats, class, equipment, status
	// Feat/power/equipment etc. bonuses
	// maxVitality += this.getBonus(Bonus.VITALITY_BONUS_PER_LEVEL).total * level

	return maxVitality;
}

// static inline uint16_t getForcePoints() {
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

// static inline void calculateAttackWithWeapon () {
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


void drawVitals(const RectangleU16 position, const Attributes *attributes) {
#define X position.x
#define Y position.y

	uint16_t y = 0;
	char buf[5];
	snprintf(buf, 5, "%d", getVitality(attributes->constitution));
	DrawText("Vitality:", X, Y + y, FONT_SIZE, BLACK);
	DrawText(buf, X + 75, Y + 1 + y, FONT_SIZE, BLACK);
	y += LABEL_ROW_HEIGHT;

	snprintf(buf, 5, "%d", getDefence(attributes->dexterity));
	DrawText("Defence:", X, Y + y, FONT_SIZE, BLACK);
	DrawText(buf, X + 75, Y + 1 + y, FONT_SIZE, BLACK);
	y += LABEL_ROW_HEIGHT;

	// TODO: force points, main/off hand attacks, saves, resistances
}
