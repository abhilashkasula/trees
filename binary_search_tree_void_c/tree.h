#ifndef __TREE_H__
#define __TREE_H__

#include <stdio.h>
#include <stdlib.h>

typedef void *Object;

typedef struct node
{
  Object value;
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

typedef enum
{
  Lesser,
  Greater,
  Equal
} Cmp_Status;

typedef Bool (*Predicate)(Object, Object);
typedef Cmp_Status (*Compare)(Object, Object);
typedef void (*Change_Node)(Node_ptr);

Node_ptr create_node(Object);
Tree_ptr create_tree(void);
void insert_node(Tree_ptr, Object, Predicate);
Bool search(Tree_ptr, Object, Compare);

#endif
