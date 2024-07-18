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
// 根据数组构建完全二叉树：
Node *buildTree(vector<int> &nums)
{
  if (nums.size() == 0) return nullptr;
  vector<Node *> nodes;
  for (int i = 0; i < nums.size(); i++)
  {
    nodes.push_back(new Node(nums[i]));
  }
  for (int i = 0; i < nodes.size() / 2; i++)
  {
    if (2 * i + 1 < nodes.size()) nodes[i]->left = nodes[2 * i + 1];
    if (2 * i + 2 < nodes.size()) nodes[i]->right = nodes[2 * i + 2];
  }
  return nodes[0];
}
void printtree(Node *root)
{
  if (root == nullptr) return;
  printtree(root->left);
  cout << root->val << " ";
  printtree(root->right);
}

bool isSolution(vector<Node *> &state) { return !state.empty() && state.back()->val == 7; }
void recordSolution(vector<Node *> &state, vector<vector<Node *>> &res) { res.push_back(state); }

bool isValid(vector<Node *> &state, Node *chioce) { return chioce != nullptr && chioce->val != 3; }

void makechioce(vector<Node *> &state, Node *&chioce) { state.push_back(chioce); }

void unmakechioce(vector<Node *> &state) { state.pop_back(); }

void backtrack(vector<Node *> &state, vector<Node *> chioces, vector<vector<Node *>> &res)
{
  if (isSolution(state))
  {
    recordSolution(state, res);
    // return;
  }

  // 遍历所有的选择：
  for (auto chioce : chioces)
  {
    if (isValid(state, chioce))
    {
      makechioce(state, chioce);
      vector<Node *> nextchioces = {chioce->left, chioce->right};
      backtrack(state, nextchioces, res);

      unmakechioce(state);
    }
  }
}

int main()
{
  vector<int> nums = {1, 7, 3, 4, 5, 6, 7, 7};
  Node *root = buildTree(nums);

  vector<Node *> chioces = {root};
  vector<Node *> state;
  vector<vector<Node *>> res;
  backtrack(state, chioces, res);

  for (auto path : res)
  {
    for (auto node : path)
    {
      cout << node->val << "->";
    }
    cout << endl;
  }
}