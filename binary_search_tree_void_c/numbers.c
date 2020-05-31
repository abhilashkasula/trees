#include "tree.h"

Object create_int(int value)
{
  int * element = malloc(sizeof(int));
  *element = value;
  return (Object)element;
}

Bool is_number_lesser(Object data_1, Object data_2)
{
  return *(int *)data_1 < *(int *)data_2;
}

int main(void) {
  Tree_ptr tree = create_tree();
  insert_node(tree, create_int(8), &is_number_lesser);
  return 0;
}