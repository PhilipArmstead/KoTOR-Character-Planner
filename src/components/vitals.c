#include <raylib.h>
#include <stdio.h>

#include "ui-constants.h"
#include "../character.h"
#include "../types.h"


void drawVitals(const RectangleU16 position, const Attributes *attributes) {
#define X position.x
#define Y position.y

	uint16_t y = 0;
	char buf[5];
	// TODO: add levels
	// TODO: add classes
	snprintf(buf, 5, "%d", getVitality(2, 10, attributes->constitution));
	DrawText("Vitality:", X, Y + y, FONT_SIZE, BLACK);
	DrawText(buf, X + 75, Y + 1 + y, FONT_SIZE, BLACK);
	y += LABEL_ROW_HEIGHT;

	snprintf(buf, 5, "%d", getDefence(attributes->dexterity));
	DrawText("Defence:", X, Y + y, FONT_SIZE, BLACK);
	DrawText(buf, X + 75, Y + 1 + y, FONT_SIZE, BLACK);
	y += LABEL_ROW_HEIGHT;

	// TODO: force points, main/off hand attacks, saves, resistances
}
