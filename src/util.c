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
    container->capacity = size;
    container->array = (int *)malloc(size * sizeof(struct Vector2));
  
    *arr_ptr = container;
}
  
void insertItem(dynamic_array* container, struct Vector2 item)
{
    if (container->size == container->capacity) {
        int *temp = container->array;
        container->capacity <<= 1;
        container->array = realloc(container->array, container->capacity * sizeof(struct Vector2));
        if(!container->array) {
            printf("Out of Memory\n");
            container->array = temp;
            return;
        }
    }
    container->array[container->size++] = item;
}
  
struct Vector2 getItem(dynamic_array* container, int index)
{
    if(index >= container->size) {
        printf("Index Out of Bounds\n");
        return -1;
    }
    return container->array[index];
}
  
void updateItem(dynamic_array* container, int index, struct Vector2 item)
{
    if (index >= container->size) {
        printf("Index Out of Bounds\n");
        return;
    }

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