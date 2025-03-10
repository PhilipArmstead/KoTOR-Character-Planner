#include <raylib.h>
#include <stdio.h>

#include "ui-constants.h"
#include "../character.h"
#include "../types.h"
#include "../utility.h"


void drawClassInput(
	const Font font,
	const Vector2 position,
	Character *character,
	const bool isPrimaryClass,
	const MouseContext mouse
) {
	const char *label = "Level ";
	DrawTextEx(font, label, position, FONT_SIZE, 0, BLACK);

	char buf[16];
	const PointU16 mousePoint = {mouse.position.x, mouse.position.y};
	const uint8_t labelWidth = (uint8_t)MeasureTextEx(font, label, FONT_SIZE, 0).x;

	uint8_t classIndex1 = getPrimaryClassIndex(*character);
	uint8_t classIndex2 = getSecondaryClassIndex(*character);
	Class class = classes[isPrimaryClass ? classIndex1 : classIndex2 + INDEX_JEDI_START];

	// Level number
	{
		uint8_t level1 = character->level1;
		uint8_t level2 = character->level2;
		snprintf(buf, 4, "%d ", isPrimaryClass ? level1 : level2);
		const Vector2 levelPosition = {position.x + (float)labelWidth, position.y};
		const Vector2 levelSize = MeasureTextEx(font, buf, FONT_SIZE, 0);
		const RectangleI16 levelRectangle = {
			(int16_t)levelPosition.x,
			(int16_t)levelPosition.y,
			(int16_t)levelSize.x,
			(int16_t)levelSize.y
		};
		if (mouse.isPressed && isPointIntersecting(mousePoint, levelRectangle)) {
			if (isPrimaryClass) {
				level1 = level1 < 20 ? level1 + 1 : 1;
			} else {
				level2 = level2 < 20 ? level2 + 1 : 0;
			}
			character->level1 = level1;
			character->level2 = level2;
		}

		DrawTextEx(font, buf, levelPosition, FONT_SIZE, 0, BLACK);
	}


	// Class name
	{
		const Vector2 levelSize = MeasureTextEx(font, buf, FONT_SIZE, 0);
		const Vector2 classPosition = {position.x + (float)labelWidth + levelSize.x, position.y};

		snprintf(buf, 16, "%s", class.name);

		const Vector2 classSize = MeasureTextEx(font, buf, FONT_SIZE, 0);
		const RectangleI16 levelRectangle = {
			(int16_t)classPosition.x,
			(int16_t)classPosition.y,
			(int16_t)classSize.x,
			(int16_t)classSize.y
		};
		if (mouse.isPressed && isPointIntersecting(mousePoint, levelRectangle)) {
			uint8_t c;
			if (isPrimaryClass) {
				classIndex1 = classIndex1 < 4 ? classIndex1 + 1 : 0;
				c = classIndex1;
			} else {
				classIndex2 = classIndex2 < 2 ? classIndex2 + 1 : 0;
				c = classIndex2 + INDEX_JEDI_START;
			}
			character->classIndices = classIndex2 << 3 | classIndex1;
			class = classes[c];
		}

		snprintf(buf, 16, "%s", class.name);
		DrawTextEx(font, buf, classPosition, FONT_SIZE, 0, BLACK);
	}
}


void drawVitals(const Font font, const PointU16 position, const MouseContext mouse, Character *character) {
#define X position.x
#define Y position.y

	uint16_t y = 0;

	drawClassInput(font, (Vector2){X, Y + y}, character,true, mouse);
	y += LABEL_ROW_HEIGHT;

	{
		const uint8_t classIndex1 = getPrimaryClassIndex(*character);
		const Class class1 = classes[classIndex1];
		if (getCanClassBecomeJedi(class1)) {
			drawClassInput(font, (Vector2){X, Y + y}, character,false, mouse);
			y += LABEL_ROW_HEIGHT;
		}
	}

	y += LABEL_ROW_HEIGHT;

	char buf[5];

	snprintf(buf, 5, "%d", getVitality(*character));
	DrawTextEx(font, "Vitality:", (Vector2){X, Y + y}, FONT_SIZE, 0, BLACK);
	DrawTextEx(font, buf, (Vector2){X + 75, Y + 1 + y}, FONT_SIZE, 0, BLACK);
	y += LABEL_ROW_HEIGHT;

	snprintf(buf, 5, "%d", getDefence(character->attributes.dexterity));
	DrawTextEx(font, "Defence:", (Vector2){X, Y + y}, FONT_SIZE, 0, BLACK);
	DrawTextEx(font, buf, (Vector2){X + 75, Y + 1 + y}, FONT_SIZE, 0, BLACK);
	y += LABEL_ROW_HEIGHT;

	// TODO: force points, main/off hand attacks, saves, resistances
}
