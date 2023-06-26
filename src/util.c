#include "../include/util.h"
#include "../include/vector2.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
  
void arrayInit(dynamic_array** arr_ptr, int size)
{
    dynamic_array *container;
    container = (dynamic_array*)malloc(sizeof(dynamic_array));
  
    container->size = 0;
    container->capacity = size*2;
    container->array = (Vector2 *)malloc(container->capacity * sizeof(Vector2));
  
    *arr_ptr = container;
}
  
void insertItem(dynamic_array* container, Vector2 item)
{
    if (container->size == container->capacity) {
        container->capacity <<= 1;
        container->array = (Vector2*) realloc(container->array, container->capacity * sizeof(Vector2));
    }

    container->array[container->size++] = item;
}
  
Vector2 getItem(dynamic_array* container, int index)
{
    return container->array[index];
}
  
void updateItem(dynamic_array* container, int index, Vector2 item)
{
    container->array[index] = item;
}
  
void freeArray(dynamic_array* container)
{
    free(container->array);
    free(container);
}

int mssleep(long miliseconds)
{
   struct timespec rem;
   struct timespec req= {
       (int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */ 
       (miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */ 
   };

   return nanosleep(&req , &rem);
}