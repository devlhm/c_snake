#ifndef RENDERING_H
#define RENDERING_H

#include <ncurses.h>
#include "./vector2.h"

extern const int WIN_HEIGHT;
extern const int WIN_WIDTH;

void drawSnake(WINDOW *win, int snakeLength, struct Vector2 *snake);
WINDOW* initialize();

#endif