#include <iostream>
#include <algorithm>
using namespace std;
class Node {
public:
string key;
string value;
Node* left;
Node* right;
int height;
Node(string key, string value) {
this->key = key;
this->value = value;
left = nullptr;
right = nullptr;
height = 1;
}
};
class AVLTree {
private:
Node* root;
int height(Node* node) {
if (node == nullptr)
return 0;
return node->height;
}
int balanceFactor(Node* node) {
if (node == nullptr)
return 0;
return height(node->left) - height(node->right);
}
Node* rotateRight(Node* y) {
Node* x = y->left;
Node* T2 = x->right;
x->right = y;
y->left = T2;
y->height = 1 + max(height(y->left), height(y->right));
x->height = 1 + max(height(x->left), height(x->right));
return x;
}
Node* rotateLeft(Node* x) {
Node* y = x->right;
Node* T2 = y->left;
y->left = x;
x->right = T2;
x->height = 1 + max(height(x->left), height(x->right));
y->height = 1 + max(height(y->left), height(y->right));
return y;
}
Node* insert(Node* node, string key, string value) {
if (node == nullptr)
return new Node(key, value);
if (key < node->key)
node->left = insert(node->left, key, value);
else if (key > node->key)
node->right = insert(node->right, key, value);
else
node->value = value;
node->height = 1 + max(height(node->left), height(node->right));
int balance = balanceFactor(node);
if (balance > 1 && key < node->left->key)
return rotateRight(node);
if (balance < -1 && key > node->right->key)
return rotateLeft(node);
if (balance > 1 && key > node->left->key) {
node->left = rotateLeft(node->left);
return rotateRight(node);
}
if (balance < -1 && key < node->right->key) {
node->right = rotateRight(node->right);
return rotateLeft(node);
}
return node;
}
Node* minValueNode(Node* node) {
Node* current = node;
while (current->left != nullptr)
current = current->left;
return current;
}
Node* deleteNode(Node* root, string key) {
if (root == nullptr)
return root;
if (key < root->key)
root->left = deleteNode(root->left, key);
else if (key > root->key)
root->right = deleteNode(root->right, key);
else {
if (root->left == nullptr || root->right == nullptr) {
Node* temp = root->left ? root->left : root->right;
if (temp == nullptr) {
temp = root;
root = nullptr;
} else
*root = *temp;
delete temp;
} else {
Node* temp = minValueNode(root->right);
root->key = temp->key;
root->value = temp->value;
root->right = deleteNode(root->right, temp->key);
}
}
if (root == nullptr)
return root;
root->height = 1 + max(height(root->left), height(root->right));
int balance = balanceFactor(root);
if (balance > 1 && balanceFactor(root->left) >= 0)
return rotateRight(root);
if (balance > 1 && balanceFactor(root->left) < 0) {
root->left = rotateLeft(root->left);
return rotateRight(root);
}
if (balance < -1 && balanceFactor(root->right) <= 0)
return rotateLeft(root);
if (balance < -1 && balanceFactor(root->right) > 0) {
root->right = rotateRight(root->right);
return rotateLeft(root);
}
return root;
}
void inorder(Node* root) {
if (root != nullptr) {
inorder(root->left);
cout << root->key << ": " << root->value << endl;
inorder(root->right);
}
}
void reverseInorder(Node* root) {
if (root != nullptr) {
reverseInorder(root->right);
cout << root->key << ": " << root->value << endl;
reverseInorder(root->left);
}
}
int findMaxComparisons(Node* node, string key, int comparisons) {
if (node == nullptr)
return comparisons;
comparisons++;
if (key == node->key)
return comparisons;
else if (key < node->key)
return findMaxComparisons(node->left, key, comparisons);
else
return findMaxComparisons(node->right, key, comparisons);
}
public:
AVLTree() {
root = nullptr;
}
void insert(string key, string value) {
root = insert(root, key, value);
}
void remove(string key) {
root = deleteNode(root, key);
}
void displayAscending() {
inorder(root);
}
void displayDescending() {
reverseInorder(root);
}
int getMaxComparisons(string key) {
return findMaxComparisons(root, key, 0);
}
};
int main() {
AVLTree dictionary;
dictionary.insert("apple", "A fruit");
dictionary.insert("banana", "An elongated fruit");
dictionary.insert("cat", "A small domesticated carnivorous mammal");
dictionary.insert("dog", "A domesticated carnivorous mammal");
cout << "Ascending order:" << endl;
dictionary.displayAscending();
cout << "\nDescending order:" << endl;
dictionary.displayDescending();
string searchKey = "banana";
cout << "\nMax comparisons required for searching '" << searchKey << "': " << 
dictionary.getMaxComparisons(searchKey) << endl;
return 0;
}