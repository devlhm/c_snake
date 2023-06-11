#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/vector2.h"
#include "../include/rendering.h"
#include "../include/util.h"

const int FPS = 8;

void initializeSnake(struct Vector2* snake, int snakeLength, struct Vector2 direction, struct Vector2 startPos) {
    for(int i = 0; i < snakeLength; i++) {
        snake[i].x = startPos.x + (direction.x * i);
        snake[i].y = startPos.y + (direction.y * i);
    }
}

void moveSnake(int snakeLength, struct Vector2* snake, struct Vector2 direction) {
    struct Vector2 prevPartPos = snake[0];
    snake[0].x += direction.x;
    snake[0].y += direction.y;

    for(int i = 1; i < snakeLength; i++) {
        struct Vector2 auxPos = prevPartPos;
        prevPartPos = snake[i];
        snake[i] = auxPos;
    }
}

struct Vector2 handleInput(WINDOW *win) {
    int key = wgetch(win);

    mvwprintw(win, 5, 5, "%d", key);

    struct Vector2 direction;

    direction.x = 0;
    direction.y = 0;

    switch(key) {
    case KEY_UP:
        direction.y = 1; 
        break;
    case KEY_DOWN:
        direction.y = -1;
        break;
    case KEY_LEFT:
        direction.x = -1;
        break;
    case KEY_RIGHT:
        direction.x = 1;
        break;
    default:
        ungetch(key);
        break;
    }

    return direction;
}


int main() {
    WINDOW* win = initialize();

    int delay = (1.0 / (double) FPS) * 1000;

    struct Vector2 direction;
    direction.x = 1;
    direction.y = 0;

    int snakeLength = 5;
    struct Vector2 *snake = malloc(sizeof(struct Vector2) * snakeLength);

    struct Vector2 startPos;
    startPos.x = 5;
    startPos.y = 5;

    initializeSnake(snake, snakeLength, direction, startPos);

    bool running = true;
    while(running) {

        
        //perform operations
        moveSnake(snakeLength, snake, direction);

        //render changes
        //drawApple()
        werase(win);
        box(win, 0, 0);
        struct Vector2 newDir = handleInput(win);
        if(newDir.x != 0 && newDir.y != 0) {
            direction = newDir;
        }

        //drawSnake(win, snakeLength, snake);

        wrefresh(win);
        mssleep(delay);
    }

    getch();
    delwin(win);
    endwin();
    return 0;
}