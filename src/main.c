#include <stdio.h>
#include <sys/time.h>

#include "types.h"
#include "window.h"
#include "components/attributes.h"
#include "components/vitals.h"
// #include "enums/weapon.h"


#define IS_BENCHMARKING 0
#define IS_TESTING 0

#if IS_TESTING
#include "tests/tests.h"
#endif

#define TAB_CONTENT_POSITION (RectangleU16){20, 20}


int main() {
#if IS_TESTING
	uint16_t failures = 0;

	failures += runFeatTests();
	failures += runSkillTests();

	if (failures) {
		printf("\n Error: encountered %d test failures\n", failures);
		return 1;
	}

	return 0;
#endif

	// Lightsaber l = {
	// 	.damage = {2, 10},
	// 	.type = LIGHTSABER_SINGLE,
	// 	.modifiers = MODIFIER_BALANCED,
	// };
	// printf("%d\n", l.damage.max);

	const uint16_t SCREEN_WIDTH = 640;
	const uint16_t SCREEN_HEIGHT = 480;
#if IS_BENCHMARKING
	const int8_t FPS = -1;
	int32_t minFps = INT32_MAX;
	int32_t maxFps = INT32_MIN;
	struct timeval startTime;
	gettimeofday(&startTime, NULL);
#else
	const uint8_t FPS = 60;
#endif
	window_create(SCREEN_WIDTH, SCREEN_HEIGHT, FPS, "SWKoTOR Character creator");

	Character character = {
		.attributes = {10, 10, 10, 10, 10, 10}
	};
	while (true) {
		if (WindowShouldClose()) {
			break;
		}

		window_beforeDraw();
		drawAttributeInputs(TAB_CONTENT_POSITION, &character.attributes);
		drawVitals((RectangleU16){500, 20}, character.attributes);
		// DrawFPS(20, 440);
		window_afterDraw();

		// TODO: begin this after five seconds, and print that we have begun
#if IS_BENCHMARKING
		struct timeval now;
		gettimeofday(&now, NULL);
		const unsigned long duration = now.tv_sec * (int)1e6 + now.tv_usec - (startTime.tv_sec * (int)1e6 + startTime.
			tv_usec);
		if (duration >= 10000000) {
			printf("Fps: %d, %d\n", minFps, maxFps);
			// Fps: 8186, 63834
			// Fps: 1680, 54969
			break;
		} else if (duration > 5000000) {
			const uint16_t fps = GetFPS();
			minFps = fps < minFps ? fps : minFps;
			maxFps = fps > maxFps ? fps : maxFps;
		}
#endif
	}

	window_destroy();

	return 0;
}

// TODO: render defence, main/off hand attacks, saves, resistances
// TODO: choose non-Jedi class + level
// TODO: choose Jedi class + level
// TODO: choose feats
// TODO: choose force powers
// TODO: show forms in tabs
// TODO: add keyboard support
