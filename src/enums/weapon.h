#pragma once

#include <stdint.h>


enum LightsaberType {
  LIGHTSABER_SINGLE,
  LIGHTSABER_DOUBLE,
  LIGHTSABER_SHORT,
  LIGHTSABER_SITH,
};

enum LightsaberColourCrystal {
  COLOUR_BLUE,
  COLOUR_YELLOW,
  COLOUR_GREEN,
  COLOUR_VIOLET,
  COLOUR_RED,
  COLOUR_HEART_OF_THE_GUARDIAN,
  COLOUR_MANTLE_OF_THE_FORCE
};

enum LightsaberCrystal {
  CRYSTAL_RUBAT,
  CRYSTAL_DAMIND,
  CRYSTAL_ERALAM,
  CRYSTAL_SAPITH,
  CRYSTAL_NEXTOR,
  CRYSTAL_OPILA,
  CRYSTAL_JENRUAX,
  CRYSTAL_PHOND,
  CRYSTAL_LUXUM,
  CRYSTAL_FIRKRANN,
  CRYSTAL_BONDAR,
  CRYSTAL_SIGIL,
  CRYSTAL_UPARI,
  CRYSTAL_SOLARI,
  CRYSTAL_KRAYT_DRAGON_PEARL,
};

enum WeaponModifier {
  MODIFIER_BALANCED    = 1 << 0,
  MODIFIER_UPGRADEABLE = 1 << 1,
};

typedef struct {
  uint8_t min;
  uint8_t max;
} Damage;

typedef struct {
  uint8_t minimumRoll; // 20 means 20-20, 19 means 19-20 etc.
  uint8_t damageModifier;
} CriticalThreat;

// https://strategywiki.org/wiki/Star_Wars:_Knights_of_the_Old_Republic/Upgrade_items#Crystal,_Rubat
// All of these properties are optional
typedef struct {
  uint8_t attackModifier;
  uint8_t damage;
  uint8_t forceRegeneration;
} Crystal;

typedef struct {
  // Array of data representing attributes for normal colours, Heart of the Guardian and Mantle of the Force
  Crystal crystals[3];
  enum LightsaberCrystal type;
} Crystals;

typedef struct {
  Damage damage;
  CriticalThreat critical;
  enum LightsaberType type;
  enum WeaponModifier modifiers;
  enum LightsaberColourCrystal colour;
  enum LightsaberCrystal crystals[2];
} Lightsaber;

#define LIGHTSABER_COUNT 4

Lightsaber lightsabers[LIGHTSABER_COUNT] = {
  {
    .type = LIGHTSABER_SINGLE,
    .damage = {2, 20},
    .critical = {.minimumRoll = 20, .damageModifier = 2},
    .modifiers = MODIFIER_BALANCED | MODIFIER_UPGRADEABLE
  },
  {
    .type = LIGHTSABER_DOUBLE,
    .damage = {2, 16},
    .critical = {.minimumRoll = 19, .damageModifier = 2},
    .modifiers = MODIFIER_UPGRADEABLE
  },
  {
    .type = LIGHTSABER_SHORT,
    .damage = {2, 12},
    .critical = {.minimumRoll = 19, .damageModifier = 2},
    .modifiers = MODIFIER_BALANCED | MODIFIER_UPGRADEABLE
  },
  {.type = LIGHTSABER_SITH, .damage = {2, 16}, .critical = {.minimumRoll = 19, .damageModifier = 2}},
};

#define CRYSTAL_COUNT 15

Crystals crystals[CRYSTAL_COUNT] = {
  {
    .type = CRYSTAL_RUBAT,
    .crystals = {
      {.attackModifier = 1, .damage = 1},
      {.attackModifier = 2, .damage = 2},
      {.forceRegeneration = 3}
    },
  },
  {
    .type = CRYSTAL_DAMIND,
    .crystals = {
      {.attackModifier = 3},
      {.attackModifier = 3, .damage = 2},
      {.attackModifier = 1, .damage = 1, .forceRegeneration = 2},
    },
  },
  {
    .type = CRYSTAL_ERALAM,
    .crystals = {
      {.attackModifier = 2, .damage = 2},
      {.attackModifier = 3, .damage = 3},
      {.attackModifier = 3, .damage = 3},
    },
  },
  {
    .type = CRYSTAL_SAPITH,
    .crystals = {
      {.attackModifier = 2, .damage = 3},
      {.attackModifier = 3, .damage = 4},
      {.attackModifier = 3, .damage = 4},
    },
  },
  {
    .type = CRYSTAL_NEXTOR,
    .crystals = {
      {.attackModifier = 1},
      // TODO: Keen
      {.attackModifier = 1, .damage = 1},
      {.attackModifier = 1, .damage = 1},
    },
  },
  {
    .type = CRYSTAL_OPILA,
    .crystals = {
      // TODO: Massive Criticals: +2-12
      {.damage = 3},
      // TODO: Massive Criticals: +2-12
      {.attackModifier = 2, .damage = 3},
      // TODO: Massive Criticals: +2-12
      {.attackModifier = 2, .damage = 3},
    },
  },
  {
    .type = CRYSTAL_JENRUAX,
    .crystals = {
      // TODO: Blaster Bolt Deflection: +5
      {.damage = 2},
      // TODO: Blaster Bolt Deflection: +7
      {.damage = 2},
      // TODO: Blaster Bolt Deflection: +5
      // TODO: Dexterity: +1
      {.attackModifier = 2, .damage = 3},
    },
  },
};
