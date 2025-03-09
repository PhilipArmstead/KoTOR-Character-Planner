#include <raylib.h>
#include <stdio.h>

#include "attributes.h"
#include "ui-constants.h"
#include "../character.h"


#define LABEL_WIDTH 104
#define LABEL_WIDTH_OFFSET 8
#define INPUT_WIDTH 50
#define INPUT_WIDTH_HALVED (INPUT_WIDTH >> 1)
#define ARROW_WIDTH 16
#define PADDING 4
#define BUTTON_DEC_X1 LABEL_X + LABEL_WIDTH - LABEL_WIDTH_OFFSET
#define BUTTON_DEC_X2 BUTTON_DEC_X1 + ARROW_WIDTH
#define INPUT_X LABEL_X + LABEL_WIDTH + ARROW_WIDTH
#define BUTTON_INC_X1 INPUT_X + LABEL_WIDTH_OFFSET + INPUT_WIDTH
#define BUTTON_INC_X2 BUTTON_INC_X1 + ARROW_WIDTH

void drawAttributeInput(
	const Font font,
	const PointU16 position,
	const char *label,
	uint8_t *attribute,
	const uint8_t i,
	const bool isMousePressed,
	const Vector2 mousePosition
) {
#define LABEL_X position.x
#define LABEL_Y position.y

	const uint16_t y = LABEL_Y + i * (LABEL_ROW_HEIGHT + LABEL_ROW_MARGIN);
	Color decrementColour = DARKBLUE;
	Color incrementColour = DARKBLUE;

	if (mousePosition.y >= y && mousePosition.y <= y + LABEL_ROW_HEIGHT) {
		if (mousePosition.x >= BUTTON_DEC_X1 && mousePosition.x <= BUTTON_DEC_X2) {
			decrementColour = BLACK;

			if (isMousePressed) {
				--*attribute;
			}
		} else if (mousePosition.x >= BUTTON_INC_X1 && mousePosition.x <= BUTTON_INC_X2) {
			incrementColour = BLACK;

			if (isMousePressed) {
				++*attribute;
			}
		}
	}

	DrawTextEx(font, label, (Vector2){LABEL_X, y + PADDING}, FONT_SIZE, 0, BLACK);
	DrawRectangle(BUTTON_DEC_X1, y, ARROW_WIDTH, LABEL_ROW_HEIGHT, decrementColour);
	DrawRectangle(INPUT_X, y, INPUT_WIDTH, LABEL_ROW_HEIGHT, BLACK);
	DrawRectangle(BUTTON_INC_X1, y, ARROW_WIDTH, LABEL_ROW_HEIGHT, incrementColour);
	char buf[5];
	const uint8_t attributeValue = *attribute;
	snprintf(buf, 4, "%d", attributeValue);
	// TODO one day: cache this?
	const Vector2 size = MeasureTextEx(font, buf, FONT_SIZE, 0);
	DrawTextEx(font, buf, (Vector2){INPUT_X + INPUT_WIDTH_HALVED - ((int)size.x >> 1), y + PADDING}, FONT_SIZE, 0, WHITE);

	const int8_t modifier = getModifier(attributeValue);
	snprintf(buf, 5, "%s%d", modifier >= 0 ? "+" : "", modifier);
	DrawTextEx(font, buf, (Vector2){BUTTON_INC_X1 + ARROW_WIDTH + 8, y + PADDING}, FONT_SIZE, 0, BLACK);
}

void drawAttributeInputs(
	const Font font,
	const PointU16 position,
	Attributes *attributes,
	const bool isMousePressed,
	const Vector2 mousePosition
) {
	uint8_t i = 0;

	// TODO: add icon to buttons
	drawAttributeInput(font, position, "Strength", &attributes->strength, i++, isMousePressed, mousePosition);
	drawAttributeInput(font, position, "Dexterity", &attributes->dexterity, i++, isMousePressed, mousePosition);
	drawAttributeInput(font, position, "Constitution", &attributes->constitution, i++, isMousePressed, mousePosition);
	drawAttributeInput(font, position, "Intelligence", &attributes->intelligence, i++, isMousePressed, mousePosition);
	drawAttributeInput(font, position, "Wisdom", &attributes->wisdom, i++, isMousePressed, mousePosition);
	drawAttributeInput(font, position, "Charisma", &attributes->charisma, i, isMousePressed, mousePosition);
}
