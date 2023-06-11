#include <ncurses.h>
#include "../include/rendering.h"
#include "../include/vector2.h"

const int WIN_HEIGHT = 25;
const int WIN_WIDTH = 80;

void drawSnake(WINDOW *win, int snakeLength, struct Vector2 *snake)
{
    for (int i = 0; i < snakeLength; i++)
    {
        mvwprintw(win, snake[i].y, snake[i].x, ".");
    }
}

WINDOW *initialize()
{
    initscr();
    noecho();
    curs_set(false);
    nodelay(stdscr, true);
    cbreak();

    WINDOW *win = newwin(WIN_HEIGHT, WIN_WIDTH, (getmaxy(stdscr) - WIN_HEIGHT) / 2, (getmaxx(stdscr) - WIN_WIDTH) / 2);
    box(win, 0, 0);
    refresh();

    return win;
}