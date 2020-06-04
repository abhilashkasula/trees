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

Node_ptr find_min(Node_ptr node)
{
  Node_ptr p_walk = node;

  while (p_walk != NULL && p_walk->left != NULL)
  {
    p_walk = p_walk->left;
  }

  return p_walk;
}

Node_ptr delete (Node_ptr root, int value)
{
  if (root == NULL)
  {
    return root;
  }

  if (value < root->value)
  {
    root->left = delete (root->left, value);
    return root;
  }

  if (value > root->value)
  {
    root->right = delete (root->right, value);
    return root;
  }

  if (root->left == NULL)
  {
    Node_ptr right = root->right;
    free(root);
    return right;
  }

  if (root->right == NULL)
  {
    Node_ptr left = root->left;
    free(root);
    return left;
  }

  Node_ptr min = find_min(root->right);
  root->value = min->value;
  root->right = delete (root->right, min->value);
  return root;
}

void delete_node(Tree_ptr tree, int value)
{
  tree->root = delete (tree->root, value);
}

Prev_ptr get_prev_with_direction(Node_ptr root, Node_ptr node)
{
  Node_ptr p_walk = root;
  Prev_ptr previous_node = malloc(sizeof(Prev));
  previous_node->prev = NULL;
  previous_node->dir = Left;

  while (p_walk != NULL && p_walk != node)
  {
    previous_node->prev = p_walk;
    if (node->value < p_walk->value)
    {
      p_walk = p_walk->left;
      previous_node->dir = Left;
    }
    else
    {
      p_walk = p_walk->right;
      previous_node->dir = Right;
    }
  }

  return previous_node;
}

Node_ptr *get_ptr_to_set(Node_ptr *root, Prev_ptr node)
{
  Node_ptr * ptr_to_set = root;
  if(node->prev != NULL)
  {
    ptr_to_set = &node->prev->left;

    if(node->dir == Right)
    {
      ptr_to_set = &node->prev->right;
    }
  }
  return ptr_to_set;
}

void rotate_node_right(Tree_ptr tree, Node_ptr pivot)
{
  if (tree->root == NULL)
  {
    return;
  }

  Prev_ptr previous_node = get_prev_with_direction(tree->root, pivot);
  Node_ptr another = pivot->left;
  if (another == NULL)
  {
    return;
  }

  Node_ptr temp = another->right;
  another->right = pivot;
  pivot->left = temp;

  Node_ptr *ptr_to_set = get_ptr_to_set(&tree->root, previous_node);
  *ptr_to_set = another;
}

void rotate_node_left(Tree_ptr tree, Node_ptr pivot)
{
  if (tree->root == NULL)
  {
    return;
  }
  Prev_ptr previous_node = get_prev_with_direction(tree->root, pivot);
  Node_ptr another = pivot->right;
  if (another == NULL)
  {
    return;
  }

  Node_ptr temp = another->left;
  another->left = pivot;
  pivot->right = temp;

  Node_ptr *ptr_to_set = get_ptr_to_set(&tree->root, previous_node);
  *ptr_to_set = another;
}
