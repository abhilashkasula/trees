#include "tree.h"

int main(void) {
  Tree_ptr tree = create_tree();

  insert_node(tree, 5);
  insert_node(tree, 7);
  insert_node(tree, 6);

  printf("before balancing:\n");
  pre_order(tree);
  balance_tree(tree);
  printf("\nafter balancing:\n");
  pre_order(tree);
  return 0;
}