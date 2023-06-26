#include <ncurses.h>
#include <stdbool.h>
#include "../include/rendering.h"
#include "../include/vector2.h"
#include "../include/util.h"

const int WIN_HEIGHT = 25;
const int WIN_WIDTH = 80;

void drawSnake(WINDOW *win, dynamic_array *snake)
{
    for (int i = 0; i < (int) snake->size; i++)
    {
        mvwprintw(win, getItem(snake, i).y, getItem(snake, i).x, "#");
    }
}

void drawApple(WINDOW *win, Vector2 applePos) {
    mvwprintw(win, applePos.y, applePos.x, "@");
}

WINDOW *initialize()
{
    initscr();
    noecho();
    curs_set(false);
    cbreak();

    WINDOW *win = newwin(WIN_HEIGHT, WIN_WIDTH, (getmaxy(stdscr) - WIN_HEIGHT) / 2, (getmaxx(stdscr) - WIN_WIDTH) / 2);
    box(win, 0, 0);
    keypad(win, true);
    nodelay(win, true);
    refresh();

    return win;
}