#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/vector2.h"
#include "../include/rendering.h"
#include "../include/util.h"

const int FPS = 10;

void initializeSnake(dynamic_array *snake, Vector2 direction, Vector2 startPos, int initSize)
{
    for (int i = initSize - 1; i >= 0; i--)
    {
        Vector2 pos;
        pos.x = startPos.x + direction.x * i;
        pos.y = startPos.y + direction.y * i;

        insertItem(snake, pos);
    }
}

void moveSnake(dynamic_array *snake, Vector2 direction)
{
    Vector2 prevPartPos = getItem(snake, 0);
    
    Vector2 newHead = prevPartPos;

    newHead.x += direction.x;
    newHead.y += direction.y;

    updateItem(snake, 0, newHead);

    for (int i = 1; i < (int) snake->size; i++)
    {
        Vector2 auxPos = prevPartPos;
        prevPartPos = getItem(snake, i);
        updateItem(snake, i, auxPos);
    }
}

Vector2 handleInput(WINDOW *win)
{
    int key = wgetch(win);
    flushinp();
    Vector2 newDirection;

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

bool checkGameOver(WINDOW *win, dynamic_array *snake)
{
    Vector2 head = getItem(snake, 0);

    if (head.x >= getmaxx(win) - 1 || head.x <= 0 || head.y >= getmaxy(win) - 1 || head.y <= 0)
        return true;

    for (int i = 1; i < (int) snake->size; i++)
        if (head.x == getItem(snake, i).x && head.y == getItem(snake, i).y)
            return true;

    return false;
}

void setDirection(Vector2 *directionPtr, Vector2 newDir)
{
    if ((newDir.x != 0 || newDir.y != 0) && ((*directionPtr).x * -1) != newDir.x && ((*directionPtr).y * -1) != newDir.y)
    {
        (*directionPtr).x = newDir.x;
        (*directionPtr).y = newDir.y;
    }
}

bool isSnakeAtPos(dynamic_array *snake, Vector2 pos)
{
    for (int i = 0; i < (int) snake->size; i++)
        if (getItem(snake, i).x == pos.x && getItem(snake, i).y == pos.y)
            return true;

    return false;
}

Vector2 setApplePos(WINDOW *win, dynamic_array *snake)
{
    Vector2 applePos;

    do
    {
        applePos.x = (rand() % (getmaxx(win)) - 2) + 2;
        applePos.y = (rand() % (getmaxy(win)) - 2) + 2;
    } while (isSnakeAtPos(snake, applePos));

    return applePos;
}

void growSnake(dynamic_array *snake, Vector2 direction)
{
    Vector2 newPos = getItem(snake, snake->size - 1);
    newPos.x -= direction.x;
    newPos.y -= direction.y;

    insertItem(snake, newPos);
}

Vector2 checkAppleCollision(WINDOW* win, dynamic_array *snake, Vector2 applePos, Vector2 direction)
{
    Vector2 head = getItem(snake, 0);
    Vector2 newApplePos = applePos;

    if (head.x == applePos.x && head.y == applePos.y) {

        growSnake(snake, direction);
        newApplePos = setApplePos(win, snake);
    }

    return newApplePos;
}

int main()
{
    WINDOW *win = initialize();

    int delay = (1.0 / (double)FPS) * 1000;

    int initSnakeLength = 5;
    dynamic_array *snake;
    arrayInit(&snake, initSnakeLength);

    Vector2 startPos;
    startPos.x = 10;
    startPos.y = 10;

    Vector2 direction;
    direction.x = 1;
    direction.y = 0;

    initializeSnake(snake, direction, startPos, initSnakeLength);
    Vector2 applePos = setApplePos(win, snake);

    bool running = true;
    while (running)
    {
        //handle input
        Vector2 newDir = handleInput(win);
        setDirection(&direction, newDir);

        // perform operations
        moveSnake(snake, direction);
        running = !checkGameOver(win, snake);
        applePos = checkAppleCollision(win, snake, applePos, direction);

        // render changes
        werase(win);
        box(win, 0, 0);

        if (running)
        {
            drawApple(win, applePos);
            drawSnake(win, snake);
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