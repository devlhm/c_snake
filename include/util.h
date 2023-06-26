#ifndef UTIL_H
#define UTIL_H

#include "./vector2.h"

int mssleep(long miliseconds);

typedef struct {
    unsigned int size;
    unsigned int capacity;
    Vector2* array;
}dynamic_array;

// function prototypes
//  array container functions
void arrayInit(dynamic_array** arr_ptr, int size);
void freeArray(dynamic_array* container);
  
// Basic Operation functions
void insertItem(dynamic_array* container, Vector2 item);
void updateItem(dynamic_array* container, int i, Vector2 item);
Vector2 getItem(dynamic_array* container, int i);

#endif