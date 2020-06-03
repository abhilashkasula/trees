#include "tree.h"

Node_ptr create_node(int value)
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

void insert_node(Tree_ptr tree, int value)
{
  Node_ptr p_walk = tree->root;
  Node_ptr *ptr_to_set = &tree->root;

  while (p_walk != NULL)
  {
    if (value < p_walk->value)
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

Bool search(Tree_ptr tree, int value)
{
  Node_ptr p_walk = tree->root;
  Bool flag = False;

  while (p_walk != NULL && !flag)
  {
    if (value == p_walk->value)
    {
      flag = True;
    }

    if (value < p_walk->value)
    {
      p_walk = p_walk->left;
    }
    else
    {
      p_walk = p_walk->right;
    }
  }

  return flag;
}

void in_order(Tree_ptr tree)
{
  if (tree->root == NULL)
  {
    return;
  }

  Tree_ptr left_tree = create_tree();
  Tree_ptr right_tree = create_tree();
  left_tree->root = tree->root->left;
  right_tree->root = tree->root->right;

  in_order(left_tree);
  printf("%d\n", tree->root->value);
  in_order(right_tree);

  free(left_tree);
  free(right_tree);
}

void pre_order(Tree_ptr tree)
{
  if (tree->root == NULL)
  {
    return;
  }

  Tree_ptr left_tree = create_tree();
  Tree_ptr right_tree = create_tree();
  left_tree->root = tree->root->left;
  right_tree->root = tree->root->right;

  printf("%d\n", tree->root->value);
  pre_order(left_tree);
  pre_order(right_tree);

  free(left_tree);
  free(right_tree);
}

void post_order(Tree_ptr tree)
{
  if (tree->root == NULL)
  {
    return;
  }

  Tree_ptr left_tree = create_tree();
  Tree_ptr right_tree = create_tree();
  left_tree->root = tree->root->left;
  right_tree->root = tree->root->right;

  post_order(left_tree);
  post_order(right_tree);
  printf("%d\n", tree->root->value);

  free(left_tree);
  free(right_tree);
}


Prev_Curr_ptr get_node(Tree_ptr tree, int value)
{
  Prev_Curr_ptr prev_curr = malloc(sizeof(Prev_Curr));
  prev_curr->curr = tree->root;
  prev_curr->prev = NULL;
  prev_curr->direction = Left;

  while (prev_curr->curr != NULL && prev_curr->curr->value != value)
  {
    prev_curr->prev = prev_curr->curr;
    if (value < prev_curr->curr->value)
    {
      prev_curr->direction = Left;
      prev_curr->curr = prev_curr->curr->left;
    }
    else
    {
      prev_curr->direction = Right;
      prev_curr->curr = prev_curr->curr->right;
    }
  }
  return prev_curr;
}

Node_ptr get_min(Node_ptr node)
{
  Node_ptr p_walk = node;

  while (p_walk != NULL && p_walk->left != NULL)
  {
    p_walk = p_walk->left;
  }

  return p_walk;
}

void delete_node(Tree_ptr tree, int value)
{
  if(tree->root == NULL || (tree->root->right == NULL && tree->root->left == NULL && tree->root->value == value))
  {
    free(tree->root);
    tree->root = NULL;
    return;
  }

  Prev_Curr_ptr node = get_node(tree, value);
  if(node->curr == NULL)
  {
    return;
  }

  if(node->curr->right == NULL && node->curr->value == value && node->prev == NULL)
  {
    Node_ptr temp = tree->root;
    tree->root = tree->root->left;
    free(temp);
    return;
  }

  if(node->curr->right == NULL)
  {
    Node_ptr ptr_to_free = node->prev->left;
    Node_ptr *ptr_to_set = &node->prev->left;

    if(node->direction == Right)
    {
      ptr_to_free = node->prev->right;
      ptr_to_set = &node->prev->right;
    }

    *ptr_to_set = node->curr->left;
    free(ptr_to_free);
    return;
  }

  Node_ptr min = get_min(node->curr->right);
  node->curr->value = min->value;

  Tree_ptr temp_tree = create_tree();
  temp_tree->root = node->curr->right;
  delete_node(temp_tree, min->value);
  
  node->curr->right = temp_tree->root;
}
