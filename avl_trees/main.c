#include "tree.h"

int main(void) {
  Tree_ptr tree = create_tree();

  //test cases

  // insert_node(tree, 50);
  // insert_node(tree, 25);
  // insert_node(tree, 60);
  // insert_node(tree, 59);
  // insert_node(tree, 10);
  // insert_node(tree, 30);
  // insert_node(tree, 9);
  // insert_node(tree, 11);
  // insert_node(tree, 29);
  // insert_node(tree, 31);

  // insert_node(tree, 3);
  // insert_node(tree, 1);
  // insert_node(tree, 2);

  // insert_node(tree, 6);
  // insert_node(tree, 5);
  // insert_node(tree, 1);
  // insert_node(tree, 2);
  // insert_node(tree, 3);
  // insert_node(tree, 4);

  insert_node(tree, 5);
  insert_node(tree, 1);
  insert_node(tree, 3);
  insert_node(tree, 4);
  insert_node(tree, 0);
  insert_node(tree, 7);

  // insert_node(tree, 1);
  // insert_node(tree, 2);
  // insert_node(tree, 3);
  // insert_node(tree, 4);
  // insert_node(tree, 5);

  // insert_node(tree, 5);
  // insert_node(tree, 7);
  // insert_node(tree, 6);

  printf("after insertion:\n");
  pre_order(tree);
  return 0;
}