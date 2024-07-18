// buildtreebyinorderandpreorder.cpp
#include "mycommon.h"

using namespace std;

class Node
{
public:
  int val;
  Node *left;
  Node *right;
  Node(int val) : val(val), left(nullptr), right(nullptr) {}
  Node() {}
};

Node *dfs(vector<int> &pre, vector<int> &in, int i, int l, int r)
{
  if (l > r) return nullptr;

  Node *root = new Node(pre[i]);
  std::cout << "root->val: " << pre[i] << std::endl;
  int m = 0;  // root.index in inorder
  for (int ii = 0; ii < in.size(); ii++)
  {
    if (in[ii] == pre[i])
    {
      m = ii;
      break;
    }
  }
  root->left = dfs(pre, in, i + 1, l, m - 1);
  root->right = dfs(pre, in, i + m - l + 1, m + 1, r);
  return root;
}
Node *build(vector<int> &pre, vector<int> &in)
{
  Node *root = dfs(pre, in, 0, 0, pre.size() - 1);
  return root;
}
void print(Node *root)
{
  if (root == nullptr) return;
  print(root->left);
  cout << root->val << " ";
  print(root->right);
}
void move(char a, char b) { cout << a << "->" << b << endl; }
void hanoi(int n, char a, char b, char c)
{
  if (n == 1)
    move(a, c);
  else
  {
    hanoi(n - 1, a, c, b);
    move(a, c);
    hanoi(n - 1, b, a, c);
  }
}
int main()
{
  vector<int> preorder = {3, 9, 2, 1, 7};
  vector<int> inorder = {9, 3, 1, 2, 7};
  Node *root = build(preorder, inorder);
  print(root);
  cout << '\n';
  hanoi(2, 'a', 'b', 'c');
}