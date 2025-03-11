#include <raylib.h>
#include <stdio.h>

#include "ui-constants.h"
#include "../character.h"
#include "../types.h"
#include "../utility.h"
#include "../data/species/species.h"


extern const Species speciesList[SPECIES_COUNT];

void drawSpeciesInput(const Font font, const Vector2 position, Character *character, const MouseContext mouse) {
	const char *label = "Species: ";
	DrawTextEx(font, label, position, FONT_SIZE, 0, BLACK);


	char buf[10];
	enum Species speciesIndex = getSpecies(*character);
	Species species = speciesList[speciesIndex];
	snprintf(buf, 10, "%s", species.name);

	const uint8_t labelWidth = (uint8_t)MeasureTextEx(font, label, FONT_SIZE, 0).x;
	const Vector2 speciesPosition = {position.x + (float)labelWidth, position.y};
	const Vector2 speciesSize = MeasureTextEx(font, buf, FONT_SIZE, 0);
	const RectangleI16 levelRectangle = {
		(int16_t)speciesPosition.x,
		(int16_t)speciesPosition.y,
		(int16_t)speciesSize.x,
		(int16_t)speciesSize.y
	};
	const PointU16 mousePoint = {mouse.position.x, mouse.position.y};

	if (mouse.isPressed && isPointIntersecting(mousePoint, levelRectangle)) {
		if (++speciesIndex >= SPECIES_COUNT - 1) {
			speciesIndex = 0;
		}
		character->data = speciesIndex << 5 | (character->data & 31);
		species = speciesList[getSpecies(*character)];
	}

	snprintf(buf, 10, "%s", species.name);
	DrawTextEx(font, buf, speciesPosition, FONT_SIZE, 0, BLACK);
}

void drawClassInput(
	const Font font,
	const Vector2 position,
	Character *character,
	const bool isPrimaryClass,
	const MouseContext mouse
) {
	const char *label = "Level ";
	DrawTextEx(font, label, position, FONT_SIZE, 0, BLACK);

	uint8_t classIndex1 = getPrimaryClassIndex(*character);
	uint8_t classIndex2 = getSecondaryClassIndex(*character);
	Class class = classes[isPrimaryClass ? classIndex1 : classIndex2 + INDEX_JEDI_START];

	char buf[16];
	const uint8_t labelWidth = (uint8_t)MeasureTextEx(font, label, FONT_SIZE, 0).x;
	const PointU16 mousePoint = {mouse.position.x, mouse.position.y};

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
			character->data = classIndex2 << 3 | classIndex1;
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

	drawSpeciesInput(font, (Vector2){X, Y + y}, character, mouse);
	y += LABEL_ROW_HEIGHT;

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
	// TODO: limit classes by species
}
