#include<iostream>
#include <sstream>
#include <vector>
using namespace std;

// Creates class AVLNode for AVL tree
class AVLNode
{
// To store data
int data;
// To point to left
struct AVLNode *leftChild=NULL;
// To point to right
struct AVLNode *rightChild=NULL;
// To store height
int height=0;

// Function to get maximum of two integers
int getMax(int a, int b);
// Function to get minimum node
AVLNode * minValueNode(AVLNode* node);
// Function to get height of the tree
int getHeight(AVLNode *node);
// Function that allocates a new node with the given key and sets NULL to the left and right child
AVLNode* newNode(int value);
// Function to right rotate subtree rooted with temp.
AVLNode *rightRotate(AVLNode *temp);
// Function to left rotate subtree rooted with temp
AVLNode *leftRotate(AVLNode *temp);
// Get Balance factor of node ND
int getBalance(AVLNode *ND);

public:

// Function to insert a node
AVLNode* insertNode(AVLNode* node, int value);
// Function to delete a node
AVLNode* deleteNode(AVLNode* root, int value);
// Function to print pr eorder traversal of the tree.
void preOrder(AVLNode *root);
// Function to print postorder traversal of the tree.
void postOrder(AVLNode *root);
// Recursive function to in order traversal
void inOrder(AVLNode *root);
};// End of class


// Function to get height of the tree
int AVLNode::getHeight(AVLNode *node)
{
// Checks if root is null return 0
if (node == NULL)
return 0;
// Otherwise return height
return node -> height;
}// End of function

// Function to get maximum of two integers
int AVLNode::getMax(int a, int b)
{
return (a > b)? a : b;
}// End of function

// Function that allocates a new node with the given key and sets NULL to the left and right child
AVLNode* AVLNode::newNode(int value)
{
// Allocates memory to create a new node
AVLNode* node = new AVLNode();
node->data = value;
node->leftChild = NULL;
node->rightChild = NULL;
// new node is added at leaf
node->height = 1;
// returns the newly created node
return(node);
}// End of function

// Function to right rotate subtree rooted with temp.
AVLNode* AVLNode::rightRotate(AVLNode *temp)
{
// Creates two temporary pointers for left and right sub tree
AVLNode *newRoot = temp->leftChild;
AVLNode *T2 = newRoot->rightChild;

// Perform rotation
newRoot->rightChild = temp;
temp->leftChild = T2;

// Update heights
temp->height = max(getHeight(temp->leftChild), getHeight(temp->rightChild))+1;
newRoot->height = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild))+1;

// Return new root
return newRoot;
}// End of function

// Function to left rotate subtree rooted with temp
AVLNode*AVLNode::leftRotate(AVLNode *temp)
{
// Creates two temporary pointers for left and right sub tree
AVLNode *newRoot = temp->rightChild;
AVLNode *T2 = newRoot->leftChild;

// Perform rotation
newRoot->leftChild = temp;
temp->rightChild = T2;

// Update heights
temp->height = max(getHeight(temp->leftChild), getHeight(temp->rightChild))+1;
newRoot->height = max(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild))+1;

// Return new root
return newRoot;
}// End of function

// Get Balance factor of node NodeBalance
int AVLNode::getBalance(AVLNode *NodeBalance)
{
if (NodeBalance == NULL)
return 0;
return getHeight(NodeBalance->leftChild) - getHeight(NodeBalance->rightChild);
}// End of function

// Function to insert a node
AVLNode* AVLNode::insertNode(AVLNode* node, int value)
{
// Perform the normal BST rotation
if (node == NULL)
return(newNode(value));

// Checks if the parameter value is less than the current node data
if (value < node->data)
// Recursively calls the function for left child
node->leftChild = insertNode(node->leftChild, value);
// Otherwise checks if the parameter value is greater than the current node data
else if (value > node->data)
// Recursively calls the function for right child
node->rightChild = insertNode(node->rightChild, value);
// Otherwise equals
else
return node;

// Update height of this ancestor node
node->height = 1 + max(getHeight(node->leftChild),getHeight(node->rightChild));

// Get the balance factor of this ancestor node to check whether this node became unbalanced
int balance = getBalance(node);

// If this node becomes unbalanced, then there are four cases need to consider
// Left Left Case
if (balance > 1 && value < node->leftChild->data)
return rightRotate(node);

// Right Right Case
if (balance < -1 && value > node->rightChild->data)
return leftRotate(node);

// Left Right Case
if (balance > 1 && value > node->leftChild->data)
{
node->leftChild = leftRotate(node->leftChild);
return rightRotate(node);
}// End of if condition

// Right Left Case
if (balance < -1 && value < node->rightChild->data)
{
node->rightChild = rightRotate(node->rightChild);
return leftRotate(node);
}// End of if condition

// return the (unchanged) node pointer
return node;
}// End of function

/*
* Given a non-empty binary search tree, return the node with minimum key value found in that tree.
* Note that the entire tree does not need to be searched.
*/
AVLNode * AVLNode::minValueNode(AVLNode* node)
{
AVLNode* current = node;

// Loops down to find the leftmost leaf
while (current->rightChild != NULL)
current = current->rightChild;
// Return the current node
return current;
}// End of function

// Recursive function to delete a node with given value from subtree with given root.
// It returns root of the modified subtree.
AVLNode* AVLNode::deleteNode(AVLNode* root, int value)
{
// Checks if root is NULL then empty tree
if (root == NULL)
return root;

// If the value to be deleted is smaller than the root's data, then it lies in left subtree
if ( value < root->data )
root->leftChild = deleteNode(root->leftChild, value);

// If the value to be deleted is greater than the root's data, then it lies in right subtree
else if( value > root->data)
root->rightChild = deleteNode(root->rightChild, value);

// If value is same as root's data, then This is the node to be deleted
else
{
// node with only one child or no child
if( (root->leftChild == NULL) || (root->rightChild == NULL) )
{
AVLNode *temp = root->leftChild ? root->leftChild : root->rightChild;

// No child case
if (temp == NULL)
{
temp = root;
root = NULL;
}// End of if condition
// One child case
else
// Copy the contents of the non-empty child
*root = *temp;
delete(temp);
}// End of if outer condition
else
{
// node with two children: Get the inorder successor (smallest in the right subtree)
AVLNode* temp = minValueNode(root->leftChild);

// Copy the inorder successor's data to this node
root->data = temp->data;

// Delete the inorder successor
root->leftChild = deleteNode(root->leftChild, temp->data);
}// End of inner else
}// End of outer else

// If the tree had only one node then return
if (root == NULL)
return root;

// Update hight of the current node
root->height = 1 + max(getHeight(root->leftChild), getHeight(root->rightChild));

int bf = getBalance(root);
    // Left Left Imbalance/Case or Right rotation
    if (bf == 2 && getBalance(root -> leftChild) >= 0)
      return rightRotate(root);
    // Left Right Imbalance/Case or LR rotation
    else if (bf == 2 && getBalance(root -> leftChild) == -1) {
      root -> leftChild = leftRotate(root -> leftChild);
      return rightRotate(root);
    }
    // Right Right Imbalance/Case or Left rotation
    else if (bf == -2 && getBalance(root -> rightChild) <= -0)
      return leftRotate(root);
    // Right Left Imbalance/Case or RL rotation
    else if (bf == -2 && getBalance(root -> rightChild) == 1) {
      root -> rightChild = rightRotate(root -> rightChild);
      return leftRotate(root);
    }

    return root;
  }

// Function to print preorder traversal of the tree.
void AVLNode::preOrder(AVLNode *root)
{
// Traverse: Left, Root, Right
// Checks if current node is not null
if(root == NULL)
return;
cout<<root->data<<" ";
preOrder(root->leftChild);
preOrder(root->rightChild);
}// End of function

// Function to print postorder traversal of the tree.
void AVLNode::postOrder(AVLNode *root)
{
// Traverse: Left, Right, Root
// Checks if current node is not null
if(root == NULL)
return;
postOrder(root->leftChild);
postOrder(root->rightChild);
cout<<root->data<<" ";
}// End of function


// Recursive function to inorder traversal
void AVLNode::inOrder(AVLNode *root)
{
// Traverse: Left, Root, Right
// Checks if current node is not null
if (root == NULL)
return;
// Moves towards left
inOrder(root->leftChild);
// Displays the root node value
cout<<root->data<<" ";
// Moves towards right
inOrder(root->rightChild);
}// End of function

int main()
{
   string str,word;
   getline(cin, str);//get the line from user
   AVLNode *root=NULL;//intitializing tree
   vector<string> out;
   istringstream enter(str);//string stream for tokenizing
   //we split the input into each opearation
   do {
       enter >> word;
       out.push_back(word);
   } while (enter);
   //we traverse upto operations only either insertion or deletion

   int len=out.size();
   for(int i=0;i<len-1;i++){
       if(out[i][0]=='A'){ // if the string first char is 'A' then it is insertion
           int number=0;//here we are calculating value after 'A'
           for(int j=1;j<(int)out[i].size();j++){
               number=number*10+(out[i][j]-'0');
           }
          root = root->insertNode(root,number);

       }else if(out[i][0]=='D'){// if the string first char is 'A' then it is insertion
           int number=0;//here we are calculating value after 'A'
           for(int j=1;j<(int)out[i].size();j++){
               number=number*10+(out[i][j]-'0');
           }
           //cout<<"D "<<val<<endl;
           root = root->deleteNode(root, number);
       }
   }
   string order=out[out.size()-1];//last operation tells about Traversal pre,in,post order
   if(order=="IN"){
       if(root==NULL){
           cout<<"EMPTY";
       }else{
           root->inOrder(root);
       }
       cout<<endl;
   }else if(order=="PRE"){
       if(root==NULL){
           cout<<"EMPTY";
       }else{
           root->preOrder(root);
       }
       cout<<endl;
   }else if(order=="POST"){
       if(root==NULL){
           cout<<"EMPTY";
       }else{
           root->postOrder(root);
       }
       cout<<endl;
   }

}

