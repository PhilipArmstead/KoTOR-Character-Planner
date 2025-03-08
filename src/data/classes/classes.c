#include "classes.h"
#include "../../types.h"


const Class classes[CLASS_COUNT] = {
    (Class){
        .name = "Soldier",
        .data = 1 << 7 | VITALITY_PER_LEVEL_10 << 5 | FEAT_GROWTH_FASTER << 2 | 0,
        .saveGrowthSpeed = SAVE_GROWTH_SLOW << 4 | (SAVE_GROWTH_SLOW << 2 | SAVE_GROWTH_FAST),
    },
    (Class){
        .name = "Scout",
        .data = VITALITY_PER_LEVEL_8 << 5 | FEAT_GROWTH_FAST << 2 | 2,
        .saveGrowthSpeed = SAVE_GROWTH_FAST << 4 | (SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_FAST),
    },
    (Class){
        // TODO: has Innate Defence
        .name = "Scoundrel",
        .data = VITALITY_PER_LEVEL_6 << 5 | FEAT_GROWTH_SLOW << 2 | 3,
        .saveGrowthSpeed = SAVE_GROWTH_SLOW << 4 | (SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_SLOW),
    },
};
