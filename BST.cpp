#include <iostream>
using namespace std;

struct node
{
  int key;
  struct node *left, *right;
};

void traverseInOrder(struct node *root);
struct node *insertNode(struct node *root, int key);
struct node *deleteNode(struct node *root, int key);
bool searchKey(node *root, int key);
int successor(node *root);
int predecessor(node *root);

// Inorder traversal
void traverseInOrder(struct node *root)
{
  if (root != NULL)
  {
    traverseInOrder(root->left);
    cout << root->key << " ";
    traverseInOrder(root->right);
  }
}

// Insert a node
struct node *insertNode(struct node* root, int key)
{
  if (root == NULL)
  {
    struct node *newNode = new node;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    root = newNode;
  }
  else
  {
    if (key > root->key)
    {
      root->right = insertNode(root->right, key);
    }
    else
    {
      root->left = insertNode(root->left, key);
    }
  }
  return root;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key)
{
  if (root == NULL)
  {
    cout << "Empty Tree" << endl;
    return NULL;
  }
  else if (root->key < key)
  {
    root->right = deleteNode(root->right, key);
  }
  else if (root->key > key)
  {
    root->left = deleteNode(root->left, key);
  }
  else
  {
    if(root->left == NULL && root->right == NULL)
    {
      root = NULL;
    }
    else if(root->right != NULL)
    {
      root->key = successor(root);
      root->right = deleteNode(root->right, root->key);
    }
    else
    {
      root->key = predecessor(root);
      root->left = deleteNode(root->left, root->key);
    }
  }

  return root;
}

bool searchKey(node *root, int key)
{
  if (root == NULL)
  {
    return false;
  }
  else if (root->key == key)
  {
    return true;
  }
  else
  {
    if (root->key < key)
    {
      return searchKey(root->right, key);
    }
    else
    {
      return searchKey(root->left, key);
    }
  }
}

int successor(node *root)
{
  root = root->right;
  while (root->left != NULL)
  {
    root = root->left;
  }
  return root->key;
}

int predecessor(node *root)
{
  root = root->left;
  while (root->right != NULL)
  {
    root = root->right;
  }
  return root->key;
}

// Driver code
int main()
{
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1) {
    switch(operation) {
      case 1: // insert
        cin >> operand;
        root = insertNode(root, operand);
        cin >> operation;
        break;
      case 2: // delete
        cin >> operand;
        root = deleteNode(root, operand);
        cin >> operation;
        break;
      default:
        cout << "Invalid Operator!\n";
        return 0;
    }
  }

  traverseInOrder(root);
}