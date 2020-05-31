const numbers = [8, 5, 20, 1, 6, 19, 21];

const createNode = value => {
  return {value, left: null, right: null};
};

const insert = (tree, value) => {
  if(!tree) {
    return createNode(value);
  }
  if(value < tree.value) {
    tree.left = insert(tree.left, value);
    return tree;
  }
  tree.right = insert(tree.right, value);
  return tree;
};

const inOrder = tree => {
  if(!tree) {
    return;
  }
  inOrder(tree.left);
  console.log(tree.value);
  inOrder(tree.right);
};

const preOrder = tree => {
  if(!tree) {
    return;
  }
  console.log(tree.value);
  preOrder(tree.left);
  preOrder(tree.right);
};

const postOrder = tree => {
  if(!tree) {
    return;
  }
  postOrder(tree.left);
  postOrder(tree.right);
  console.log(tree.value);
};

const search = (tree, value) => {
  if(tree === null) {
    return false;
  }
  console.log('ins');
  if(value === tree.value) {
    return true;
  }
  if(value < tree.value) {
    return search(tree.left, value);
  }
  return search(tree.right, value);
};
