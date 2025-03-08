#include <stdio.h>

#include "tests.h"
#include "../character.h"
#include "../types.h"
#include "../data/classes/classes.h"


extern const Class classes[CLASS_COUNT];

bool assertUint8(const uint8_t expected, const uint8_t actual) {
	printf("should be %d ", expected);
	if (expected == actual) {
		printf("✓\n");
		return false;
	}

	printf("but received %d x\n", actual);
	return true;
}

uint16_t runFeatTests() {
	uint8_t failures = 0;
	printf("\nFeat point allowance tests\n===\n");

	typedef struct {
		char name[16];
		uint8_t index;
		uint8_t allowed[20];
	} TestCase;

	const TestCase testCases[3] = {
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
	};

	for (uint8_t i = 0; i < 3; ++i) {
		const Class testClass = classes[testCases[i].index];
		const TestCase testCase = testCases[i];

		printf("When we have a %s\n", testCase.name);

		for (uint8_t level = 1; level <= 20; ++level) {
			printf("	and they are level %d\n", level);
			failures += assertUint8(testCase.allowed[level - 1], getFeatAllowance(testClass.growthSpeed, level));
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

	const TestCase testCases[3] = {
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
	};

	for (uint8_t i = 0; i < 3; ++i) {
		const Class testClass = classes[testCases[i].index];

		const TestSuite *suite = testCases[i].tests;
		TestSuite testCase = suite[0];

		// Character creation
		printf("%s\n", testCase.description);

		for (uint8_t j = 0; j < 6; ++j) {
			const int8_t modifier = testCase.outcomes[j].modifier;
			printf("	and Intelligence Modifier is %d\n", modifier);
			failures += assertUint8(testCase.outcomes[j].expected, getSkillAllowance(testClass.growthSpeed, 1, modifier));
		}

		// Levelling
		printf("- %s\n", testCase.description);

		testCase = suite[1];
		for (uint8_t j = 0; j < 6; ++j) {
			const int8_t modifier = testCase.outcomes[j].modifier;
			printf("	and Intelligence Modifier is %d\n", modifier);
			failures += assertUint8(testCase.outcomes[j].expected, getSkillAllowance(testClass.growthSpeed, 2, modifier));
		}
	}

	return failures;
}
