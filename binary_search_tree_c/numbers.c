#include "tree.h"

int main(void) {
  Tree_ptr tree = create_tree();
  insert_node(tree, 8);
  insert_node(tree, 5);
  insert_node(tree, 20);
  insert_node(tree, 1);
  insert_node(tree, 6);
  insert_node(tree, 19);
  insert_node(tree, 21);
  in_order(tree);
  printf("\n");
  pre_order(tree);
  printf("\n");
  post_order(tree);
  return 0;
}