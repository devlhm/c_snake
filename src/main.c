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
    flushinp();
    struct Vector2 newDirection;

    newDirection.x = 0;
    newDirection.y = 0;

    switch(key) {
    case KEY_UP:
    case 'w':
        newDirection.y = -1; 
        break;
    case KEY_DOWN:
    case 's':
        newDirection.y = 1;
        break;
    case KEY_LEFT:
    case 'a':
        newDirection.x = -1;
        break;
    case KEY_RIGHT:
    case 'd':
        newDirection.x = 1;
        break;
    }

    return newDirection;
}

bool checkGameOver(WINDOW *win, struct Vector2 *snake, int snakeLength) {
    struct Vector2 head = snake[snakeLength - 1];

    if(head.x >= getmaxx(win) || head.x <= 0 || head.y >= getmaxy(win) || head.y <= 0) {
        return true;
    }

    for(int i = 0; i < snakeLength - 1; i++) {
        if(head.x == snake[i].x && head.y == snake[i].y) {
            return true;
        }
    }

    return false;
}

int main() {
    WINDOW* win = initialize();

    int delay = (1.0 / (double) FPS) * 1000;

    int snakeLength = 5;
    struct Vector2 *snake = malloc(sizeof(struct Vector2) * snakeLength);

    struct Vector2 startPos;
    startPos.x = 10;
    startPos.y = 10;

    struct Vector2 direction;
    direction.x = 1;
    direction.y = 0;

    initializeSnake(snake, snakeLength, direction, startPos);

    bool running = true;
    while(running) {
        
        struct Vector2 newDir = handleInput(win);

        if((newDir.x != 0 || newDir.y != 0) && (direction.x * -1) != newDir.x && (direction.y * -1) != newDir.y) {
            direction.x = newDir.x;
            direction.y = newDir.y;
        }

        //perform operations
        moveSnake(snakeLength, snake, direction);
        running = !checkGameOver(win, snake, snakeLength);

        //render changes
        //drawApple()

        werase(win);
        box(win, 0, 0);

        drawSnake(win, snakeLength, snake);

        wrefresh(win);
        mssleep(delay);
    }

    mvwprintw(win, 5, 5, "GAME OVER!");
    wrefresh(win);
    getch();
    delwin(win);
    endwin();
    return 0;
}