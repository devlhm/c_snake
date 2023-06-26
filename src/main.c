#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/vector2.h"
#include "../include/rendering.h"
#include "../include/util.h"

const int FPS = 8;

void initializeSnake(dynamic_array *snake, int snakeLength, struct Vector2 direction, struct Vector2 startPos)
{
    for (int i = snakeLength - 1; i >= 0; i--)
    {
        struct Vector2 pos;
        pos.x = direction.x * i;
        pos.y = direction.y * i;

        insertItem(snake, pos);

        // snake[snakeLength - 1 - i].x = startPos.x + (direction.x * i);
        // snake[snakeLength - 1 - i].y = startPos.y + (direction.y * i);
    }
}

void moveSnake(int snakeLength, dynamic_array *snake, struct Vector2 direction)
{
    struct Vector2 prevPartPos = getItem(snake, 0);
    
    struct Vector2 newHead = prevPartPos;

    newHead.x += direction.x;
    newHead.y += direction.y;

    updateItem(snake, 0, newHead);

    for (int i = 1; i < snakeLength; i++)
    {
        struct Vector2 auxPos = prevPartPos;
        prevPartPos = getItem(snake, i);
        updateItem(snake, i, auxPos);
    }
}

struct Vector2 handleInput(WINDOW *win)
{
    int key = wgetch(win);
    flushinp();
    struct Vector2 newDirection;

    newDirection.x = 0;
    newDirection.y = 0;

    switch (key)
    {
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

bool checkGameOver(WINDOW *win, dynamic_array *snake, int snakeLength)
{
    struct Vector2 head = getItem(snake, 0);

    if (head.x >= getmaxx(win) || head.x <= 0 || head.y >= getmaxy(win) || head.y <= 0)
        return true;

    for (int i = 1; i < snakeLength; i++)
        if (head.x == getItem(snake, i).x && head.y == getItem(snake, i).y)
            return true;

    return false;
}

void setDirection(struct Vector2 *directionPtr, struct Vector2 newDir)
{
    if ((newDir.x != 0 || newDir.y != 0) && ((*directionPtr).x * -1) != newDir.x && ((*directionPtr).y * -1) != newDir.y)
    {
        (*directionPtr).x = newDir.x;
        (*directionPtr).y = newDir.y;
    }
}

bool isSnakeAtPos(dynamic_array *snake, int snakeLength, struct Vector2 pos)
{
    for (int i = 0; i < snakeLength; i++)
        if (getItem(snake, i).x == pos.x && getItem(snake, i).y == pos.y)
            return true;

    return false;
}

struct Vector2 setApplePos(WINDOW *win, dynamic_array *snake, int snakeLength)
{
    struct Vector2 applePos;

    do
    {
        applePos.x = (rand() % (getmaxx(win))) + 1;
        applePos.y = (rand() % (getmaxy(win))) + 1;
    } while (isSnakeAtPos(snake, snakeLength, applePos));

    return applePos;
}

void *growSnake(dynamic_array *snake, int *snakeLength, struct Vector2 direction)
{
    (*snakeLength)++;

    struct Vector2 newPos = getItem(snake, (*snakeLength) - 2);
    newPos.x -= direction.x;
    newPos.y -= direction.y;

    insertItem(snake, newPos);
}

void *checkAppleCollision(dynamic_array *snake, struct Vector2 applePos, int *snakeLength, struct Vector2 direction)
{
    struct Vector2 head = getItem(snake, 0);

    if (head.x == applePos.x && head.y == applePos.y)
        growSnake(snake, snakeLength, direction);
}

int main()
{
    WINDOW *win = initialize();

    int delay = (1.0 / (double)FPS) * 1000;

    int snakeLength = 5;
    dynamic_array *snake;
    arrayInit(&snake);

    struct Vector2 startPos;
    startPos.x = 10;
    startPos.y = 10;

    struct Vector2 direction;
    direction.x = 1;
    direction.y = 0;

    struct Vector2 applePos = setApplePos(win, snake, snakeLength);

    initializeSnake(snake, snakeLength, direction, startPos);

    bool running = true;
    while (running)
    {
        struct Vector2 newDir = handleInput(win);

        setDirection(&direction, newDir);

        // perform operations
        moveSnake(snakeLength, snake, direction);
        // running = !checkGameOver(win, snake, snakeLength);
        checkAppleCollision(snake, applePos, &snakeLength, direction);

        // render changes
        werase(win);
        box(win, 0, 0);

        if (running)
        {
            drawApple(win, applePos);
            drawSnake(win, snakeLength, snake);
            wrefresh(win);
            mssleep(delay);
        }
    }

    mvwprintw(win, 5, 5, "GAME OVER!");
    wrefresh(win);
    mssleep(1000);
    getch();
    delwin(win);
    endwin();
    return 0;
}