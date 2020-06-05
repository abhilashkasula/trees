#include "tree.h"
#include "array.h"

int main(void) {
  Tree_ptr tree = create_tree();
  insert_node(tree, 40);
  insert_node(tree, 41);
  insert_node(tree, 42);
  insert_node(tree, 43);
  insert_node(tree, 44);
  insert_node(tree, 45);
  insert_node(tree, 46);

  printf("before balance\n");
  pre_order(tree);
  balance_tree(tree);
  printf("\nafter balance\n");
  pre_order(tree);
  return 0;
}