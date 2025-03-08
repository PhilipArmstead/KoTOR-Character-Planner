#include "character.h"
#include "data/classes/classes.h"


uint8_t getSkillAllowance(const uint8_t growthSpeed, const uint8_t level, const int8_t intelligenceModifier) {
  const uint8_t skillGrowth = getSkillGrowth(growthSpeed);

	if (level == 1) {
		int8_t value = (skillGrowth + intelligenceModifier) * 4;

		return value > 4 ? value : 4;
	}

	int8_t value = skillGrowth + (intelligenceModifier >> 1);
	return value > 1 ? value : 1;
}
