#include "tree.h"

int main(void) {
  Tree_ptr tree = create_tree();
  insert_node(tree, 8);
  insert_node(tree, 5);
  insert_node(tree, 20);
  insert_node(tree, 1);
  insert_node(tree, 19);
  insert_node(tree, 21);
  return 0;
}