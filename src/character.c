#include "character.h"


uint8_t getFeatAllowance(uint8_t data, uint8_t level) {
  const enum FeatGrowthSpeed featGrowth = getFeatGrowth(data);

  switch (featGrowth) {
    case FEAT_GROWTH_SLOWER:
      return level == 1 || (level % 3) == 0;
    case FEAT_GROWTH_SLOW:
      return level == 1 || ((level + 1) % 3) == 0;
    case FEAT_GROWTH_AVERAGE:
      return level == 1 || level == 7 || level == 13 || (level % 3) == 0;
    case FEAT_GROWTH_QUICK:
      return level == 1 || level == 5 || level == 11 || level == 17 || (level % 3) == 0;
    case FEAT_GROWTH_FAST:
      return level & 1 || level == 2;
    case FEAT_GROWTH_FASTER:
      return level != 17 && level != 19;
    }
}

uint8_t getSkillAllowance(const uint8_t characterData, const uint8_t level, const int8_t intelligenceModifier) {
  const uint8_t skillGrowth = getSkillGrowth(characterData);

	if (level == 1) {
		int8_t value = (skillGrowth + intelligenceModifier) * 4;

		return value > 4 ? value : 4;
	}

	int8_t value = skillGrowth + (intelligenceModifier >> 1);
	return value > 1 ? value : 1;
}
