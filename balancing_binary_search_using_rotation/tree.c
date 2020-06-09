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

Node_ptr rotate_left(Node_ptr root)
{
  Node_ptr temp = root->right;

  if (temp == NULL)
  {
    return root;
  }

  root->right = temp->left;
  temp->left = root;
  return temp;
}

Node_ptr rotate_right(Node_ptr root)
{
  Node_ptr temp = root->left;

  if (temp == NULL)
  {
    return root;
  }

  root->left = temp->right;
  temp->right = root;
  return temp;
}

int get_height(Node_ptr root, int height)
{
  if (root == NULL)
  {
    return height;
  }

  int right = get_height(root->right, height + 1);
  int left = get_height(root->left, height + 1);
  return MAX(right, left);
}

int get_tree_height(Tree_ptr tree)
{
  return get_height(tree->root, 0);
}

int get_balance_delta(Node_ptr root)
{
  if(root == NULL) {
    return 0;
  }

  int left_height = get_height(root->left, 0);
  int right_height = get_height(root->right, 0);
  return right_height - left_height;
}

Bool is_left_right(Node_ptr root)
{
  return get_balance_delta(root) == -2 && get_balance_delta(root->left) == 1;
}

Node_ptr arrange_left_right(Node_ptr root)
{
  root->left = rotate_left(root->left);
  return root;
}

Node_ptr balance(Node_ptr node)
{
  if (node == NULL)
  {
    return node;
  }

  node->left = balance(node->left);
  node->right = balance(node->right);
  int delta = get_balance_delta(node);

  if (delta >= -1 && delta <= 1)
  {
    return node;
  }

  if (is_left_right(node))
  {
    node = arrange_left_right(node);
  }

  Rotator rotate = &rotate_left;
  if (delta < -1)
  {
    rotate = &rotate_right;
  }

  return balance((*rotate)(node));
}

void balance_tree(Tree_ptr tree)
{
  tree->root = balance(tree->root);
}
