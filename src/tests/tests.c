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

uint16_t runSkillTests() {
	uint8_t failures = 0;
	printf("Skill point allowance tests\n===\n");

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
		(TestCase){
			0,
			{
				{"When creating Soldier", {{-1, 4}, {0, 4}, {1, 8}, {2, 12}, {3, 16}, {4, 20}}},
				{"When levelling Soldier", {{-1, 1}, {0, 1}, {1, 1}, {2, 2}, {3, 2}, {4, 3}}}
			},
		},
		(TestCase){
			1,
			{
				{"When creating Scout", {{-1, 8}, {0, 12}, {1, 16}, {2, 20}, {3, 24}, {4, 28}}},
				{"When levelling Scout", {{-1, 2}, {0, 3}, {1, 3}, {2, 4}, {3, 4}, {4, 5}}}
			},
		},
		(TestCase){
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
