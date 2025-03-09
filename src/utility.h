#pragma once

#include "types.h"


inline bool isPointIntersecting(const PointU16 point, const RectangleI16 rect) {
	return point.x >= rect.x && point.y >= rect.y && point.x <= rect.x + rect.width && point.y <= rect.y + rect.height;
}
