#include "tree.h"

int main(void) {
  Tree_ptr tree = create_tree();
  insert_node(tree, 23);
  insert_node(tree, 87);
  insert_node(tree, 2);
  insert_node(tree, 5);
  insert_node(tree, 37);
  insert_node(tree, 6);
  insert_node(tree, 53);
  insert_node(tree, 12);
  insert_node(tree, 85);
  insert_node(tree, 22);
  insert_node(tree, 36);
  insert_node(tree, 43);
  insert_node(tree, 95);
  insert_node(tree, 52);
  insert_node(tree, 7);
  insert_node(tree, 3);
  in_order(tree);
  printf("\n");
  pre_order(tree);
  printf("\n");
  post_order(tree);

  delete_node(tree, 7);
  printf("inorder\n");
  in_order(tree);
  return 0;
}