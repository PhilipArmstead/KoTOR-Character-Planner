#include "classes.h"
#include "../../types.h"


const Class classes[CLASS_COUNT] = {
    (Class){
        .name = "Soldier",
        .data = SAVE_GROWTH_SLOW << 12 | SAVE_GROWTH_SLOW << 10 | SAVE_GROWTH_FAST << 8 | 1 << 7 |
        VITALITY_PER_LEVEL_10 << 5 | FEAT_GROWTH_FASTER << 2 | 0,
    },
    (Class){
        .name = "Scout",
        .data = SAVE_GROWTH_FAST << 12 | SAVE_GROWTH_FAST << 10 | SAVE_GROWTH_FAST << 8 | VITALITY_PER_LEVEL_8 << 5 |
        FEAT_GROWTH_FAST << 2 | 2,
    },
    (Class){
        .name = "Scoundrel",
        .data = SAVE_GROWTH_SLOW << 12 | SAVE_GROWTH_FAST << 10 | SAVE_GROWTH_SLOW << 8 | VITALITY_PER_LEVEL_6 << 5 |
        FEAT_GROWTH_SLOW << 2 | 3,
    },
    (Class){
        .name = "Combat Droid",
        .data = SAVE_GROWTH_SLOW << 12 | (SAVE_GROWTH_SLOW << 10 | SAVE_GROWTH_FAST << 8) | 1 << 7 |
        VITALITY_PER_LEVEL_12 << 5 | FEAT_GROWTH_SLOWER << 2 | 0,
    },
    (Class){
        .name = "Expert Droid",
        .data = SAVE_GROWTH_SLOW << 12 | SAVE_GROWTH_FAST << 10 | SAVE_GROWTH_SLOW << 8 | VITALITY_PER_LEVEL_8 << 5 |
        FEAT_GROWTH_QUICK << 2 | 1,
    },
    (Class){
        .name = "Jedi Guardian",
        .data = SAVE_GROWTH_AVERAGE << 12 | SAVE_GROWTH_FAST << 10 | SAVE_GROWTH_FAST << 8 | 1 << 7 |
        VITALITY_PER_LEVEL_10 << 5 | FEAT_GROWTH_AVERAGE << 2 | 0,
    },
    (Class){
        .name = "Jedi Sentinel",
        .data = SAVE_GROWTH_AVERAGE << 12 | SAVE_GROWTH_FAST << 10 | SAVE_GROWTH_FAST << 8 | VITALITY_PER_LEVEL_8 << 5
        | FEAT_GROWTH_SLOWER << 2 | 1,
    },
    (Class){
        .name = "Jedi Consular",
        .data = SAVE_GROWTH_FAST << 12 | SAVE_GROWTH_AVERAGE << 10 | SAVE_GROWTH_FAST << 8 | VITALITY_PER_LEVEL_6 << 5
        | FEAT_GROWTH_SLOWER << 2 | 0,
    },
};
