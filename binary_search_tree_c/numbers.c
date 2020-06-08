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

  printf("height: ");
  int a = get_tree_height(tree);
  printf("%d\n", a);
  return 0;
}