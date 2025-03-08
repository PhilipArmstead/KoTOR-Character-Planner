#pragma once

#include <raylib.h>
#include <stdint.h>


inline void window_create(const uint32_t width, const uint32_t height, const uint16_t fps, const char *title) {
  InitWindow(width, height, title);
  SetTargetFPS(fps);
}

inline void window_destroy() {
  CloseWindow();
}

inline void window_beforeDraw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
}

inline void window_afterDraw() {
  EndDrawing();
}
