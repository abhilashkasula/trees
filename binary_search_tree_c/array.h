#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

typedef struct
{
  Node_ptr *nodes;
  int length;
  int capacity;
} Array;

typedef Array *Array_ptr;

Array_ptr create_array(int capacity);
void push(Array_ptr array, Node_ptr node);
void resize(Array_ptr array);
void destroy_array(Array_ptr array);

#endif
