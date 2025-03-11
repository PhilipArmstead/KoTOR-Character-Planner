#pragma once

#include <stdint.h>


enum Species {
	SPECIES_HUMANOID,
	SPECIES_WOOKIE,
	SPECIES_DROID,
	SPECIES_JEDI,
	SPECIES_COUNT,
};

typedef struct {
	char name[8];
	/**
	 * This is fragile as hell, but it's an array
	 * of indices pointing to the classes in classes.c.
	 */
	int8_t classes[3];
} Species;
