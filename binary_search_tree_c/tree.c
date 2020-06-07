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

Prev_Nodes_ptr create_prev_nodes(void)
{
  Prev_Nodes_ptr prev_nodes = malloc(sizeof(Prev_Nodes));
  prev_nodes->dir = 0;
  prev_nodes->parent = NULL;
  prev_nodes->prev = NULL;
  return prev_nodes;
}

Prev_Nodes_ptr get_prev_nodes(Node_ptr root, Node_ptr pivot)
{
  Prev_Nodes_ptr prev_nodes = create_prev_nodes();
  Node_ptr p_walk = root;
  Direction dir = Left;

  while(p_walk != NULL && p_walk != pivot)
  {
    prev_nodes->parent = prev_nodes->prev;
    prev_nodes->prev = p_walk;
    prev_nodes->dir = dir;

    if(pivot->value < p_walk->value)
    {
      dir = Left;
      p_walk = p_walk->left;
    }
    else
    {
      dir = Right;
      p_walk = p_walk->right;
    }
  }

  return prev_nodes;
}

void rotate_node_left(Tree_ptr tree, Node_ptr pivot)
{
  if(tree->root == NULL || pivot == NULL)
  {
    return;
  }

  Prev_Nodes_ptr prev_nodes = get_prev_nodes(tree->root, pivot);

  if(prev_nodes->prev == NULL || prev_nodes->prev->right != pivot)
  {
    return;
  }

  Node_ptr temp = pivot->left;
  pivot->left = prev_nodes->prev;
  prev_nodes->prev->right = temp;
  Node_ptr *ptr_to_set = &tree->root;

  if(prev_nodes->parent != NULL)
  {
    ptr_to_set = &prev_nodes->parent->right;

    if(prev_nodes->dir == 0)
    {
      ptr_to_set = &prev_nodes->parent->left;
    }
  }
  
  *ptr_to_set = pivot;
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
