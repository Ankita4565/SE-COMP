#include <iostream>
#include <stack>
#include <cctype>
using namespace std;
struct TreeNode {
char data;
TreeNode* left;
TreeNode* right; 
TreeNode(char value) : data(value), left(nullptr), right(nullptr) {}
};
bool isOperator(char c) {
return (c == '+' || c == '-' || c == '*' || c == '/');
}
TreeNode* constructExpressionTree(const string& prefixExpression) {
stack<TreeNode*> st;
int n = prefixExpression.length();
for (int i = n - 1; i >= 0; --i) {
char c = prefixExpression[i];
TreeNode* newNode = new TreeNode(c);
if (isOperator(c)) {
newNode->left = st.top();
st.pop();
newNode->right = st.top();
st.pop();
}
st.push(newNode);
}
return st.top();
}
void postOrderTraversal(TreeNode* root) {
if (!root) return; 
stack<TreeNode*> st;
TreeNode* current = root; 
do
{
while (current) {
if (current->right) st.push(current->right);
st.push(current);
current = current->left;
} 
current = st.top();
st.pop(); 
if (current->right && !st.empty() && current->right == st.top()) {
st.pop();
st.push(current);
current = current->right;
}
else
{
cout << current->data << " ";
current = nullptr;
}
}
while (!st.empty());
}
void deleteExpressionTree(TreeNode* root) {
if (!root) return;
stack<TreeNode*> st;
TreeNode* current = root;
do
{
while (current) {
if (current->right) st.push(current->right);
st.push(current);
current = current->left;
} 
current = st.top();
st.pop(); 
if (current->right && !st.empty() && current->right == st.top()) {
st.pop();
st.push(current);
current = current->right;
}
else
{
delete current;
current = nullptr;
}
}
while (!st.empty());
}
int main()
{
string prefixExpression = "+-a*bc/def";
TreeNode* root = constructExpressionTree(prefixExpression); 
cout << "Post-order traversal: ";
postOrderTraversal(root);
cout << endl;
char choice;
cout << "Do you want to delete the expression tree? (y/n): ";
cin >> choice;
if (tolower(choice) == 'y') {
deleteExpressionTree(root);
cout << "Expression tree deleted." << endl;
} 
return 0;
}
