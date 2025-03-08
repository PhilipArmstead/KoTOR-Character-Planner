#include <raylib.h>
#include <stdio.h>

#include "attributes.h"
#include "ui-constants.h"
#include "../character.h"


#define LABEL_WIDTH 104
#define LABEL_WIDTH_OFFSET 8
#define INPUT_WIDTH 50
#define INPUT_WIDTH_HALVED (INPUT_WIDTH >> 1)
#define LABEL_ROW_MARGIN 6
#define ARROW_WIDTH 16
#define PADDING 4
#define BUTTON_DEC_X1 LABEL_X + LABEL_WIDTH - LABEL_WIDTH_OFFSET
#define BUTTON_DEC_X2 BUTTON_DEC_X1 + ARROW_WIDTH
#define INPUT_X LABEL_X + LABEL_WIDTH + ARROW_WIDTH
#define BUTTON_INC_X1 INPUT_X + LABEL_WIDTH_OFFSET + INPUT_WIDTH
#define BUTTON_INC_X2 BUTTON_INC_X1 + ARROW_WIDTH

void drawAttributeInput(
	const RectangleU16 position,
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

	DrawText(label, LABEL_X, y + PADDING, FONT_SIZE, BLACK);
	DrawRectangle(BUTTON_DEC_X1, y, ARROW_WIDTH, LABEL_ROW_HEIGHT, decrementColour);
	DrawRectangle(INPUT_X, y, INPUT_WIDTH, LABEL_ROW_HEIGHT, BLACK);
	DrawRectangle(BUTTON_INC_X1, y, ARROW_WIDTH, LABEL_ROW_HEIGHT, incrementColour);
	char buf[5];
	const uint8_t attributeValue = *attribute;
	snprintf(buf, 4, "%d", attributeValue);
	// TODO one day: cache this?
	const uint8_t w = MeasureText(buf, FONT_SIZE) >> 1;
	DrawText(buf, INPUT_X + INPUT_WIDTH_HALVED - w, y + PADDING, FONT_SIZE, WHITE);

	const int8_t modifier = getModifier(attributeValue);
	snprintf(buf, 5, "%s%d", modifier >= 0 ? "+" : "", modifier);
	DrawText(buf, BUTTON_INC_X1 + ARROW_WIDTH + 8, y + PADDING, FONT_SIZE, BLACK);
}

void drawAttributeInputs(const RectangleU16 position, Attributes *attributes) {
	uint8_t i = 0;
	const bool isMousePressed = IsMouseButtonPressed(0);
	const Vector2 mousePosition = GetMousePosition();

	// TODO: add icon to buttons
	drawAttributeInput(position, "Strength", &attributes->strength, i++, isMousePressed, mousePosition);
	drawAttributeInput(position, "Dexterity", &attributes->dexterity, i++, isMousePressed, mousePosition);
	drawAttributeInput(position, "Constitution", &attributes->constitution, i++, isMousePressed, mousePosition);
	drawAttributeInput(position, "Intelligence", &attributes->intelligence, i++, isMousePressed, mousePosition);
	drawAttributeInput(position, "Wisdom", &attributes->wisdom, i++, isMousePressed, mousePosition);
	drawAttributeInput(position, "Charisma", &attributes->charisma, i, isMousePressed, mousePosition);
}
