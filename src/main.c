#include <stdio.h>
#include <sys/time.h>

#include "types.h"
#include "window.h"
#include "components/attributes.h"
#include "components/ui-constants.h"
#include "components/vitals.h"
#include "data/classes/classes.h"
// #include "enums/weapon.h"


#define IS_BENCHMARKING 0
#define IS_TESTING 0

#if IS_TESTING
#include "tests/tests.h"
#endif

#define TAB_CONTENT_POSITION (PointU16){20, 20}

extern const Class classes[CLASS_COUNT];

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

	const Font font = LoadFontEx("../assets/fonts/ubuntu-mono/Ubuntu-R.ttf", FONT_SIZE, 0, 0);

	AttributesContext attributesContext = {.contentPosition = TAB_CONTENT_POSITION};
	Image imageArrowRight = LoadImage("../assets/icons/arrow-right.png");
	ImageResize(&imageArrowRight, ARROW_WIDTH, LABEL_ROW_HEIGHT);
	attributesContext.arrowRight = LoadTextureFromImage(imageArrowRight);
	ImageFlipHorizontal(&imageArrowRight);
	attributesContext.arrowLeft = LoadTextureFromImage(imageArrowRight);
	UnloadImage(imageArrowRight);

	Character character = {
		.classIndices = 0,
		//.classIndices = 0 << 3 | 0,
		.level1 = 1,
		.level2 = 0,
		.attributes = {10, 10, 10, 10, 10, 10}
	};
	while (true) {
		if (WindowShouldClose()) {
			break;
		}

		window_beforeDraw();

		const MouseContext mouseContext = {
			.isPressed = IsMouseButtonPressed(0),
			.position = GetMousePosition()
		};

		// TODO: cache all buttons + labels in local structs and pre-compute positions ahead of time?
		drawAttributeInputs(font, attributesContext, mouseContext, &character.attributes);
		drawVitals(font, (PointU16){465, 20}, mouseContext, &character);
		// DrawFPS(20, 440);
		window_afterDraw();

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

	UnloadTexture(attributesContext.arrowRight);
	UnloadFont(font);
	window_destroy();

	return 0;
}

// TODO: render defence, main/off hand attacks, saves, resistances
// TODO: choose feats
// TODO: choose force powers
// TODO: show forms in tabs
// TODO: add keyboard support
