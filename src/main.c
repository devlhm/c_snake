#include <stdio.h>
#include <ncurses>

int main() {
    initscr();
    mvprintw(1, 1, "Hello world!");
    getch();
    endwin();
    return 0;
}