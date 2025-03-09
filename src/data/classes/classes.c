#include "classes.h"
#include "../../types.h"


const Class classes[CLASS_COUNT] = {
    (Class){
        .name = "Soldier",
        .data1 = 1 << 7 | VITALITY_PER_LEVEL_10 << 5 | FEAT_GROWTH_FASTER << 2 | 0,
        .data2 = 1 << 6 | SAVE_GROWTH_SLOW << 4 | SAVE_GROWTH_SLOW << 2 | SAVE_GROWTH_FAST,
    },
    (Class){
        .name = "Scout",
        .data1 = VITALITY_PER_LEVEL_8 << 5 | FEAT_GROWTH_FAST << 2 | 2,
        .data2 = 1 << 6 | SAVE_GROWTH_FAST << 4 | SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_FAST,
    },
    (Class){
        .name = "Scoundrel",
        .data1 = VITALITY_PER_LEVEL_6 << 5 | FEAT_GROWTH_SLOW << 2 | 3,
        .data2 = 1 << 6 | SAVE_GROWTH_SLOW << 4 | SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_SLOW,
    },
    (Class){
        .name = "Combat Droid",
        .data1 = 1 << 7 | VITALITY_PER_LEVEL_12 << 5 | FEAT_GROWTH_SLOWER << 2 | 0,
        .data2 = SAVE_GROWTH_SLOW << 4 | (SAVE_GROWTH_SLOW << 2 | SAVE_GROWTH_FAST),
    },
    (Class){
        .name = "Expert Droid",
        .data1 = VITALITY_PER_LEVEL_8 << 5 | FEAT_GROWTH_QUICK << 2 | 1,
        .data2 = SAVE_GROWTH_SLOW << 4 | (SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_SLOW),
    },
    (Class){
        .name = "Jedi Guardian",
        .data1 = 1 << 7 | VITALITY_PER_LEVEL_10 << 5 | FEAT_GROWTH_AVERAGE << 2 | 0,
        .data2 = SAVE_GROWTH_AVERAGE << 4 | SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_FAST,
    },
    (Class){
        .name = "Jedi Sentinel",
        .data1 = VITALITY_PER_LEVEL_8 << 5 | FEAT_GROWTH_SLOWER << 2 | 1,
        .data2 = SAVE_GROWTH_AVERAGE << 4 | SAVE_GROWTH_FAST << 2 | SAVE_GROWTH_FAST,
    },
};
