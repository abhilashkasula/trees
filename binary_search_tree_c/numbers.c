#include "tree.h"

int main(void) {
  Tree_ptr tree = create_tree();
  insert_node(tree, 40);
  insert_node(tree, 41);
  insert_node(tree, 20);
  insert_node(tree, 21);
  insert_node(tree, 10);
  insert_node(tree, 11);
  insert_node(tree, 9);

  Node_ptr pivot = tree->root->left;
  rotate_node_right(tree, pivot);
  printf("inorder\n");
  in_order(tree);
  return 0;
}