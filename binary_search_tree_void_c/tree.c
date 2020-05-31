#include "tree.h"

Node_ptr create_node(Object value)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

Tree_ptr create_tree(void)
{
  Tree_ptr tree = malloc(sizeof(Tree));
  tree->root = NULL;
  return tree;
}

void insert_node(Tree_ptr tree, Object value, Predicate predicate)
{
  Node_ptr p_walk = tree->root;
  Node_ptr *ptr_to_set = &tree->root;

  while (p_walk != NULL)
  {
    if ((*predicate)(value, p_walk->value))
    {
      ptr_to_set = &p_walk->left;
      p_walk = p_walk->left;
    }
    else
    {
      ptr_to_set = &p_walk->right;
      p_walk = p_walk->right;
    }
  }

  *ptr_to_set = create_node(value);
}

void left(Node_ptr * node)
{
  *node = (*node)->left;
}

void right(Node_ptr * node)
{
  *node = (*node)->right;
}

Bool search(Tree_ptr tree, Object value, Compare compare)
{
  Node_ptr p_walk = tree->root;
  Bool is_present = False;
  Change_Node functions[2] = {&left, &right};

  while (p_walk != NULL && !is_present)
  {
    Cmp_Status status = (*compare)(value, p_walk->value);

    if (status == Equal)
    {
      is_present = True;
    }
    else 
    {
      functions[status](&p_walk);
    }
  }
  
  return is_present;
}
