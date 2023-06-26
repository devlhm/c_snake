#ifndef UTIL_H
#define UTIL_H

int mssleep(long miliseconds);

typedef struct {
    size_t size;
    size_t capacity;
    int* array;
}dynamic_array;

// function prototypes
//  array container functions
void arrayInit(dynamic_array** arr_ptr, int size);
void freeArray(dynamic_array* container);
  
// Basic Operation functions
void insertItem(dynamic_array* container, struct Vector2 item);
void updateItem(dynamic_array* container, int i, struct Vector2 item);
struct Vector2 getItem(dynamic_array* container, int i);

#endif