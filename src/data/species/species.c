#include "species.h"


const Species species[SPECIES_COUNT] = {
    (Species){
        .name = "Droid",
        .classes = {3, 4, -1},
    },
    (Species){
        .name = "Humanoid",
        .classes = {0, 1, 2},
    },
    (Species){
        .name = "Wookie",
        .classes = {1, -1},
    },
    (Species){
        .name = "Jedi",
        .classes = {5, 6, 7},
    },
};
