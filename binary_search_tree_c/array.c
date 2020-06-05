#include "array.h"

void resize(Array_ptr node_array)
{
  node_array->capacity *= 2;
  Node_ptr * temp = node_array->nodes;
  node_array->nodes = malloc(sizeof(Node_ptr) * node_array->capacity);
  memcpy(node_array->nodes, temp, sizeof(Node_ptr) * node_array->length);
  free(temp);
}

void push(Array_ptr node_array, Node_ptr node)
{
  if (node_array->capacity == node_array->length)
  {
    resize(node_array);
  }
  node_array->nodes[node_array->length] = node;
  node_array->length += 1;
}

Array_ptr create_array(int capacity)
{
  Array_ptr new_array = malloc(sizeof(Array));
  new_array->capacity = capacity;
  new_array->length = 0;
  new_array->nodes = malloc(sizeof(Node_ptr) * new_array->capacity);
  return new_array;
}

void destroy_array(Array_ptr array)
{
  free(array->nodes);
  free(array);
}
