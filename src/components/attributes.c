#include <raylib.h>
#include <stdio.h>

#include "attributes.h"
#include "ui-constants.h"
#include "../character.h"


#define LABEL_WIDTH 104
#define LABEL_WIDTH_OFFSET 8
#define INPUT_WIDTH 50
#define INPUT_WIDTH_HALVED (INPUT_WIDTH >> 1)
#define PADDING 4
#define BUTTON_DEC_X1 (LABEL_X + LABEL_WIDTH - LABEL_WIDTH_OFFSET)
#define BUTTON_DEC_X2 (BUTTON_DEC_X1 + ARROW_WIDTH)
#define INPUT_X (LABEL_X + LABEL_WIDTH + ARROW_WIDTH)
#define BUTTON_INC_X1 (INPUT_X + LABEL_WIDTH_OFFSET + INPUT_WIDTH)
#define BUTTON_INC_X2 (BUTTON_INC_X1 + ARROW_WIDTH)

void drawAttributeInput(
	const Font font,
	const AttributesContext context,
	const char *label,
	uint8_t *attribute,
	const uint8_t i,
	const MouseContext mouse
) {
#define LABEL_X context.contentPosition.x
#define LABEL_Y context.contentPosition.y

	const uint16_t y = LABEL_Y + i * (LABEL_ROW_HEIGHT + LABEL_ROW_MARGIN);
	Color decrementColour = WHITE;
	Color incrementColour = WHITE;

	if (mouse.position.y >= y && mouse.position.y <= y + LABEL_ROW_HEIGHT) {
		if (mouse.position.x >= BUTTON_DEC_X1 && mouse.position.x <= BUTTON_DEC_X2) {
			decrementColour = GRAY;

			if (mouse.isPressed) {
				--*attribute;
			}
		} else if (mouse.position.x >= BUTTON_INC_X1 && mouse.position.x <= BUTTON_INC_X2) {
			incrementColour = GRAY;

			if (mouse.isPressed) {
				++*attribute;
			}
		}
	}

	DrawTextEx(font, label, (Vector2){LABEL_X, (float)y + PADDING}, FONT_SIZE, 0, BLACK);
	DrawTexture(context.arrowLeft, BUTTON_DEC_X1, y, decrementColour);
	DrawRectangle(INPUT_X, y, INPUT_WIDTH, LABEL_ROW_HEIGHT, BLACK);
	DrawTexture(context.arrowRight, BUTTON_INC_X1, y, incrementColour);
	char buf[5];
	const uint8_t attributeValue = *attribute;
	snprintf(buf, 4, "%d", attributeValue);
	// TODO one day: cache this?
	const Vector2 size = MeasureTextEx(font, buf, FONT_SIZE, 0);
	DrawTextEx(
		font,
		buf,
		(Vector2){INPUT_X + INPUT_WIDTH_HALVED - ((int)size.x >> 1), (float)y + PADDING},
		FONT_SIZE,
		0,
		WHITE
	);

	const int8_t modifier = getModifier(attributeValue);
	snprintf(buf, 5, "%s%d", modifier >= 0 ? "+" : "", modifier);
	DrawTextEx(font, buf, (Vector2){BUTTON_INC_X1 + ARROW_WIDTH + 8, (float)y + PADDING}, FONT_SIZE, 0, BLACK);
}

void drawAttributeInputs(
	const Font font,
	const AttributesContext context,
	const MouseContext mouse,
	Attributes *attributes
) {
	uint8_t i = 0;

	drawAttributeInput(font, context, "Strength", &attributes->strength, i++, mouse);
	drawAttributeInput(font, context, "Dexterity", &attributes->dexterity, i++, mouse);
	drawAttributeInput(font, context, "Constitution", &attributes->constitution, i++, mouse);
	drawAttributeInput(font, context, "Intelligence", &attributes->intelligence, i++, mouse);
	drawAttributeInput(font, context, "Wisdom", &attributes->wisdom, i++, mouse);
	drawAttributeInput(font, context, "Charisma", &attributes->charisma, i++, mouse);
}
