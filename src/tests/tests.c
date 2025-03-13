#include <stdio.h>

#include "tests.h"
#include "../character.h"
#include "../types.h"
#include "../data/classes/classes.h"


bool assertUint8(const uint8_t expected, const uint8_t actual) {
	printf("should be %d ", expected);
	if (expected == actual) {
		printf("✓\n");
		return false;
	}

	printf("but received %d x\n", actual);
	return true;
}

bool assertInt8(const int8_t expected, const int8_t actual) {
	printf("should be %d ", expected);
	if (expected == actual) {
		printf("✓\n");
		return false;
	}

	printf("but received %d x\n", actual);
	return true;
}

uint16_t runAttributesTests() {
	uint8_t failures = 0;
	printf("\nAttributes tests\n===\n");

	typedef struct {
		uint8_t attribute;
		int8_t expectedModifier;
	} TestCase;

	const TestCase testCases[] = {
		{8, -1},
		{9, -1},
		{10, 0},
		{11, 0},
		{12, 1},
		{13, 1},
		{14, 2},
		{15, 2},
		{16, 3},
		{17, 3},
		{18, 4},
		{19, 4},
		{20, 5},
		{21, 5},
		{22, 6},
		{23, 6},
	};

	for (uint8_t i = 0; i < 16; ++i) {
		printf("- When we have an attribute value of %d\n", testCases[i].attribute);
		const Character character = {.attributes = {testCases[i].attribute}};

		failures += assertInt8(testCases[i].expectedModifier, getModifier(character.attributes.strength));
	}

	return failures;
}

uint16_t runClassTests() {
	uint8_t failures = 0;
	printf("\nClass tests\n===\n");

	typedef struct {
		uint8_t data;
		bool canBecomeJedi;
	} TestCase;

	const TestCase testCases[] = {
		{0,true},
		{32,false},
		{64,false},
		{96,false},
	};

	for (uint8_t i = 0; i < 4; ++i) {
		printf("- When we have character data of %d\n", testCases[i].data);
		const Character character = {.data = testCases[i].data};

		failures += assertUint8(testCases[i].canBecomeJedi, getCanClassBecomeJedi(&character));
	}

	return failures;
}

uint16_t runSpeciesTests() {
	uint8_t failures = 0;
	printf("\nSpecies tests\n===\n");

	typedef struct {
		uint8_t data;
		uint8_t expected;
	} TestCase;

	const TestCase testCases[] = {
		{0, 0},
		{32, 1},
		{64, 2},
		{96, 3},
	};

	for (uint8_t i = 0; i < 4; ++i) {
		printf("- When we have a data value of %d\n", testCases[i].data);
		Character character = {.data = testCases[i].data};

		failures += assertUint8(testCases[i].expected, getSpecies(&character));
	}

	return failures;
}

uint16_t runFeatTests() {
	uint8_t failures = 0;
	printf("\nFeat point allowance tests\n===\n");

	typedef struct {
		char name[16];
		uint8_t index;
		uint8_t allowed[20];
	} TestCase;

	const TestCase testCases[] = {
		{
			"Soldier",
			0,
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
		},
		{
			"Scout",
			1,
			{1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
		},
		{
			"Scoundrel",
			2,
			{1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
		},
		{
			"Combat Droid",
			3,
			{1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
		},
		{
			"Expert Droid",
			4,
			{1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0},
		},
		{
			"Jedi Guardian",
			5,
			{1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0},
		},
		{
			"Jedi Sentinel",
			6,
			{1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
		},
		{
			"Jedi Consular",
			7,
			{1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
		},
	};

	for (uint8_t i = 0; i < 8; ++i) {
		const Class testClass = classes[testCases[i].index];
		const TestCase testCase = testCases[i];

		printf("When we have a %s\n", testCase.name);

		for (uint8_t level = 1; level <= 20; ++level) {
			printf("	and they are level %d\n", level);
			failures += assertUint8(testCase.allowed[level - 1], getFeatAllowance(testClass.data, level));
		}
	}

	return failures;
}

uint16_t runSkillTests() {
	uint8_t failures = 0;
	printf("\nSkill point allowance tests\n===\n");

	typedef struct {
		int8_t modifier;
		uint8_t expected;
	} TestInitialSkill;
	typedef struct {
		char description[32];
		TestInitialSkill outcomes[6];
	} TestSuite;
	typedef struct {
		uint8_t index;
		TestSuite tests[2];
	} TestCase;

	const TestCase testCases[] = {
		{
			0,
			{
				{"When creating Soldier", {{-1, 4}, {0, 4}, {1, 8}, {2, 12}, {3, 16}, {4, 20}}},
				{"When levelling Soldier", {{-1, 1}, {0, 1}, {1, 1}, {2, 2}, {3, 2}, {4, 3}}}
			},
		},
		{
			1,
			{
				{"When creating Scout", {{-1, 8}, {0, 12}, {1, 16}, {2, 20}, {3, 24}, {4, 28}}},
				{"When levelling Scout", {{-1, 2}, {0, 3}, {1, 3}, {2, 4}, {3, 4}, {4, 5}}}
			},
		},
		{
			2,
			{
				{"When creating Scoundrel", {{-1, 12}, {0, 16}, {1, 20}, {2, 24}, {3, 28}, {4, 32}}},
				{"When levelling Scoundrel", {{-1, 3}, {0, 4}, {1, 4}, {2, 5}, {3, 5}, {4, 6}}}
			},
		},
		{
			3,
			{
				{"When creating Combat Droid", {{-1, 4}, {0, 4}, {1, 8}, {2, 12}, {3, 16}, {4, 20}}},
				{"When levelling Combat Droid", {{-1, 1}, {0, 1}, {1, 1}, {2, 2}, {3, 2}, {4, 3}}}
			},
		},
		{
			4,
			{
				{"When creating Expert Droid", {{-1, 4}, {0, 8}, {1, 12}, {2, 16}, {3, 20}, {4, 24}}},
				{"When levelling Expert Droid", {{-1, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 3}, {4, 4}}}
			},
		},
		{
			5,
			{
				{"When creating Jedi Guardian", {{-1, 4}, {0, 4}, {1, 8}, {2, 12}, {3, 16}, {4, 20}}},
				{"When levelling Jedi Guardian", {{-1, 1}, {0, 1}, {1, 1}, {2, 2}, {3, 2}, {4, 3}}}
			},
		},
		{
			6,
			{
				{"When creating Jedi Sentinel", {{-1, 4}, {0, 8}, {1, 12}, {2, 16}, {3, 20}, {4, 24}}},
				{"When levelling Jedi Sentinel", {{-1, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 3}, {4, 4}}}
			},
		},
		{
			7,
			{
				{"When creating Jedi Consular", {{-1, 4}, {0, 4}, {1, 8}, {2, 12}, {3, 16}, {4, 20}}},
				{"When levelling Jedi Consular", {{-1, 1}, {0, 1}, {1, 1}, {2, 2}, {3, 2}, {4, 3}}}
			},
		},
	};

	for (uint8_t i = 0; i < 8; ++i) {
		const Class testClass = classes[testCases[i].index];

		const TestSuite *suite = testCases[i].tests;
		TestSuite testCase = suite[0];

		// Character creation
		printf("%s\n", testCase.description);

		for (uint8_t j = 0; j < 6; ++j) {
			const int8_t modifier = testCase.outcomes[j].modifier;
			printf("	and Intelligence Modifier is %d\n", modifier);
			failures += assertUint8(testCase.outcomes[j].expected, getSkillAllowance(testClass.data, 1, modifier));
		}

		// Levelling
		printf("- %s\n", testCase.description);

		testCase = suite[1];
		for (uint8_t j = 0; j < 6; ++j) {
			const int8_t modifier = testCase.outcomes[j].modifier;
			printf("	and Intelligence Modifier is %d\n", modifier);
			failures += assertUint8(testCase.outcomes[j].expected, getSkillAllowance(testClass.data, 2, modifier));
		}
	}

	return failures;
}
