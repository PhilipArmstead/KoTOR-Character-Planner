#include "classes.h"
#include "../../types.h"


const Class classes[CLASS_COUNT] = {
    (Class){
        .name = "Soldier",
        .modifier = (ClassModifier){
            .attackModifierPerLevel = 1,
            .vitalityPerLevel = 10,
        },
        .growthSpeed = FEAT_GROWTH_FASTER << 2 | 0,
        .saveGrowthSpeed = SAVE_GROWTH_SLOW << 4 | (SAVE_GROWTH_SLOW << 2 | SAVE_GROWTH_FAST),
    },
    (Class){
        .name = "Scout",
        .modifier = (ClassModifier){
            .attackModifierPerLevel = 0.75,
            .vitalityPerLevel = 8,
        },
        .growthSpeed = FEAT_GROWTH_AVERAGE << 2 | 2,
        .saveGrowthSpeed = SAVE_GROWTH_FAST << 4 | (SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_FAST),
    },
    (Class){
        // TODO: has Innate Defence
        .name = "Scoundrel",
        .modifier = (ClassModifier){
            .attackModifierPerLevel = 0.75,
            .vitalityPerLevel = 6,
        },
        .growthSpeed = FEAT_GROWTH_SLOW << 2 | 3,
        .saveGrowthSpeed = SAVE_GROWTH_SLOW << 4 | (SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_SLOW),
    },
};
