#include "types.h"
#include "window.h"
#include "components/attributes.h"
// #include "enums/weapon.h"


int main() {
	// Lightsaber l = {
	// 	.damage = {2, 10},
	// 	.type = LIGHTSABER_SINGLE,
	// 	.modifiers = MODIFIER_BALANCED,
	// };
	// printf("%d\n", l.damage.max);

	const uint16_t SCREEN_WIDTH = 640;
	const uint16_t SCREEN_HEIGHT = 480;
	const uint8_t FPS = 30;
	window_create(SCREEN_WIDTH, SCREEN_HEIGHT, FPS, "SWKoTOR Character creator");

	Attributes attributes = {{10, 0}, {10, 0}, {10, 0}, {10, 0}, {10, 0}, {10, 0}};
	while (true) {
		if (WindowShouldClose()) {
			break;
		}

		window_beforeDraw();
		drawAttributeInputs(&attributes);
		window_afterDraw();
	}

	window_destroy();

	return 0;
}
