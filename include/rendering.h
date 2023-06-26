#ifndef RENDERING_H
#define RENDERING_H

#include <ncurses.h>
#include "./vector2.h"
#include "./util.h"

extern const int WIN_HEIGHT;
extern const int WIN_WIDTH;

void drawSnake(WINDOW *win, dynamic_array *snake);
void drawApple(WINDOW *win, Vector2 applePos);
WINDOW* initialize();

#endif