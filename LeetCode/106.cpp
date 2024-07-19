#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
/*
给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历
postorder是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。
*/
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
  std::unordered_map<int, int> map;
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
  {
    for (int i = 0; i < inorder.size(); i++) {
      map[inorder[i]] = i;
    }
    return helper(inorder, postorder, inorder.size() - 1, 0, inorder.size() - 1);
  }
  TreeNode* helper(vector<int>& inorder, vector<int>& postorder, int target, int l, int r)
  {
    if (l > r) return nullptr;
    TreeNode* root = new TreeNode(postorder[target]);
    int index = map[postorder[target]];
    root->right = helper(inorder, postorder, target - 1, index + 1, r);
    root->left = helper(inorder, postorder, target - r + index - 1, l, index - 1);
    return root;
  };
};
void print(TreeNode* root)
{
  if (root == nullptr) return;
  print(root->left);
  cout << root->val << " ";
  print(root->right);
}
int main()
{
  vector<int> inorder = {9, 3, 15, 20, 7};
  vector<int> postorder = {9, 15, 7, 20, 3};
  Solution s;
  TreeNode* root = s.buildTree(inorder, postorder);

  print(root);
}