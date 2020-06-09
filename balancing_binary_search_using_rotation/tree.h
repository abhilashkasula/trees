#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__

#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) x > y ? x : y

typedef struct node
{
  int value;
  struct node *left;
  struct node *right;
} Node;

typedef Node *Node_ptr;

typedef struct
{
  Node_ptr root;
} Tree;

typedef Tree *Tree_ptr;

typedef enum
{
  False,
  True
} Bool;

Node_ptr create_node(int value);
Tree_ptr create_tree(void);
void insert_node(Tree_ptr tree, int value);
Bool search(Tree_ptr tree, int value);
void in_order(Tree_ptr tree);
void pre_order(Tree_ptr tree);
void post_order(Tree_ptr tree);
Node_ptr delete (Node_ptr root, int value);
void delete_node(Tree_ptr, int);
Node_ptr rotate_right(Node_ptr);
Node_ptr rotate_left(Node_ptr root);
Node_ptr balance(Node_ptr);
void balance_tree(Tree_ptr tree);
int get_height(Node_ptr root, int height);
int get_tree_height(Tree_ptr);
Node_ptr arrange_left_right(Node_ptr);
Bool is_left_right(Node_ptr);
int get_balance_delta(Node_ptr);

#endif