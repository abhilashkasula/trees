#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__

#include <stdio.h>
#include <stdlib.h>

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

typedef struct
{
  Node_ptr prev;
  Node_ptr curr;
  int direction;
} Prev_Curr;

typedef Prev_Curr *Prev_Curr_ptr;

Node_ptr create_node(int value);
Tree_ptr create_tree(void);
void insert_node(Tree_ptr tree, int value);
Bool search(Tree_ptr tree, int value);
void in_order(Tree_ptr tree);
void pre_order(Tree_ptr tree);
void post_order(Tree_ptr tree);
void delete_node(Tree_ptr, int);

#endif