#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "attributes.h"


#define LABEL_WIDTH 104
#define LABEL_WIDTH_OFFSET 8
#define INPUT_WIDTH 50
#define INPUT_WIDTH_HALVED (INPUT_WIDTH >> 1)
#define LABEL_X 20
#define LABEL_Y 20
#define LABEL_ROW_HEIGHT 24
#define LABEL_ROW_MARGIN 6
#define ARROW_WIDTH 16
#define PADDING 4
#define FONT_SIZE 16
#define BUTTON_DEC_X1 LABEL_X + LABEL_WIDTH - LABEL_WIDTH_OFFSET
#define BUTTON_DEC_X2 BUTTON_DEC_X1 + ARROW_WIDTH
#define INPUT_X LABEL_X + LABEL_WIDTH + ARROW_WIDTH
#define BUTTON_INC_X1 INPUT_X + LABEL_WIDTH_OFFSET + INPUT_WIDTH
#define BUTTON_INC_X2 BUTTON_INC_X1 + ARROW_WIDTH

void drawAttributeInput(
	const char *label,
	Attribute *attribute,
	const uint8_t i,
	const bool isMousePressed,
	const Vector2 mousePosition
) {
	const uint16_t y = LABEL_Y + i * (LABEL_ROW_HEIGHT + LABEL_ROW_MARGIN);
	Color decrementColour = DARKBLUE;
	Color incrementColour = DARKBLUE;

	if (mousePosition.y >= y && mousePosition.y <= y + LABEL_ROW_HEIGHT) {
		if (mousePosition.x >= BUTTON_DEC_X1 && mousePosition.x <= BUTTON_DEC_X2) {
			decrementColour = BLACK;

			if (isMousePressed) {
				--attribute->value;
				// Divide with floor (default is to round towards 0)
				const int8_t a = attribute->value - 10;
				const uint8_t b = 2;
				attribute->modifier = a / b - (a % b != 0 && (a ^ b) < 0);
			}
		} else if (mousePosition.x >= BUTTON_INC_X1 && mousePosition.x <= BUTTON_INC_X2) {
			incrementColour = BLACK;

			if (isMousePressed) {
				++attribute->value;
				// Divide with floor (default is to round towards 0)
				const int8_t a = attribute->value - 10;
				const uint8_t b = 2;
				attribute->modifier = a / b - (a % b != 0 && (a ^ b) < 0);
			}
		}
	}

	DrawText(label, LABEL_X, y + PADDING, FONT_SIZE, BLACK);
	DrawRectangle(BUTTON_DEC_X1, y, ARROW_WIDTH, LABEL_ROW_HEIGHT, decrementColour);
	DrawRectangle(INPUT_X, y, INPUT_WIDTH, LABEL_ROW_HEIGHT, BLACK);
	DrawRectangle(BUTTON_INC_X1, y, ARROW_WIDTH, LABEL_ROW_HEIGHT, incrementColour);
	char buf[4];
	snprintf(buf, 3, "%d", attribute->value);
	// TODO one day: cache this?
	const uint8_t w = MeasureText(buf, FONT_SIZE) >> 2;
	DrawText(buf, INPUT_X + INPUT_WIDTH_HALVED - w, y + PADDING, FONT_SIZE, WHITE);
	snprintf(buf, 4, "%s%d", attribute->modifier >= 0 ? "+" : "", attribute->modifier);
	DrawText(buf, BUTTON_INC_X1 + ARROW_WIDTH + 8, y + PADDING, FONT_SIZE, BLACK);
}

void drawAttributeInputs(Attributes *attributes) {
	uint8_t i = 0;
	const bool isMousePressed = IsMouseButtonPressed(0);
	const Vector2 mousePosition = GetMousePosition();

	// TODO: add icon to buttons
	// TODO: add attribute modifier
	drawAttributeInput("Strength", &attributes->strength, i++, isMousePressed, mousePosition);
	drawAttributeInput("Dexterity", &attributes->dexterity, i++, isMousePressed, mousePosition);
	drawAttributeInput("Constitution", &attributes->constitution, i++, isMousePressed, mousePosition);
	drawAttributeInput("Intelligence", &attributes->intelligence, i++, isMousePressed, mousePosition);
	drawAttributeInput("Wisdom", &attributes->wisdom, i++, isMousePressed, mousePosition);
	drawAttributeInput("Charisma", &attributes->charisma, i, isMousePressed, mousePosition);
}
