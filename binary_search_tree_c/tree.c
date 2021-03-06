#include "tree.h"
#include "array.h"

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

Node_ptr rotate_right(Node_ptr root, Node_ptr pivot)
{
  if(root == NULL)
  {
    return root;
  }

  if(pivot->value < root->value)
  {
    root->left = rotate_right(root->left, pivot);
    return root;
  }
  if(pivot->value > root->value)
  {
    root->right = rotate_right(root->right, pivot);
    return root;
  }

  Node_ptr another = pivot->left;

  if(another == NULL)
  {
    return root;
  }

  Node_ptr temp = another->right;
  another->right = pivot;
  pivot->left = temp;

  return another;
}

void rotate_node_right(Tree_ptr tree, Node_ptr pivot)
{
  tree->root = rotate_right(tree->root, pivot);
}

Node_ptr rotate_left(Node_ptr root, Node_ptr pivot)
{
  if(root == NULL)
  {
    return root;
  }

  if(pivot->value < root->value)
  {
    root->left = rotate_left(root->left, pivot);
    return root;
  }
  if(pivot->value > root->value)
  {
    root->right = rotate_left(root->right, pivot);
    return root;
  }

  Node_ptr another = pivot->right;

  if(another == NULL)
  {
    return root;
  }

  Node_ptr temp = another->left;
  another->left = pivot;
  pivot->right = temp;

  return another;
}

void rotate_node_left(Tree_ptr tree, Node_ptr pivot)
{
  tree->root = rotate_left(tree->root, pivot);
}

void store_nodes_in_array(Node_ptr root, Array_ptr array)
{
  if(root == NULL)
  {
    return;
  }

  store_nodes_in_array(root->left, array);
  push(array, root);
  store_nodes_in_array(root->right, array);
}

Node_ptr balance(Array_ptr array, int start, int end)
{
  if(start > end)
  {
    return NULL;
  }

  int pivot = (start + end) / 2;
  Node_ptr root = array->nodes[pivot];
  root->left = balance(array, start, pivot - 1);
  root->right = balance(array, pivot + 1, end);
  return root;
}

void balance_tree(Tree_ptr tree)
{
  Array_ptr tree_nodes = create_array(3);
  store_nodes_in_array(tree->root, tree_nodes);
  tree->root = balance(tree_nodes, 0, tree_nodes->length - 1);
  destroy_array(tree_nodes);
}

int get_height(Node_ptr root, int height)
{
  if(root == NULL)
  {
    return height;
  }

  int right = get_height(root->right, height + 1);
  int left= get_height(root->left, height + 1);
  return MAX(right, left);
}

int get_tree_height(Tree_ptr tree)
{
  return get_height(tree->root, 0);
}
