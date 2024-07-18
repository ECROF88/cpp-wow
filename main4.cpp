#include <bits/stdc++.h>

using namespace std;

class treeNode
{
public:
  int value;
  treeNode* left;
  treeNode* right;
  treeNode(int value)
  {
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
  }
};
class searchTree
{
public:
  treeNode* root;
  vector<treeNode*> path;
  vector<vector<treeNode*>> res;
  constexpr searchTree(treeNode* root) : root(root) {};
  treeNode* searchbyValue(int value)
  {
    treeNode* current = root;
    while (current != nullptr)
    {
      if (current->value == value)
      {
        return current;
      }
      else if (current->value > value)
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    return nullptr;
  }
  void insert(int value)
  {
    treeNode* cur = root;
    treeNode* pre = nullptr;
    while (cur != nullptr)
    {
      if (cur->value == value)
      {
        return;
      }
      pre = cur;  // 记录当前节点,也就是下面转移之后节点的父节点
      if (cur->value > value)
      {
        cur = cur->left;
      }
      else if (cur->value < value)
      {
        cur = cur->right;
      }
      // 直到找到一个空的位置，跳出循环
    }
    treeNode* newNode = new treeNode(value);
    if (pre->value < value)
    {
      pre->right = newNode;
    }
    else
    {
      pre->left = newNode;
    }
  }
  void deleteNode(int value)
  {
    // 考虑三种情况：1.删除的节点是叶子节点 2.删除的节点只有一个子节点 3.删除的节点有两个子节点
    treeNode* cur = root;
    treeNode* pre = nullptr;
    while (cur != nullptr)
    {
      if (cur->value == value)
      {
        break;
      }
      pre = cur;
      if (cur->value > value)
      {
        cur = cur->left;
      }
      else if (cur->value < value)
      {
        cur = cur->right;
      }
    }
    if (cur == nullptr)
    {
      return;
    }
    // 度为0或1的情况：
    if (cur->left == nullptr || cur->right == nullptr)
    {
      treeNode* child = cur->left == nullptr ? cur->right : cur->left;
      if (cur == root)
        root = child;
      else
      {
        if (pre->left == cur)
          pre->left = child;
        else
          pre->right = child;
      }
      delete cur;
    }
    // 度为2的情况：用右子树最小节点或者左子树最大的节点来代替当前节点
    else if (cur->left != nullptr && cur->right != nullptr)  // 要加上else，否则上面删除之后cur就变了
    {
      // 这里用右子树最小的节点来代替当前节点
      treeNode* minNode = cur->right;
      while (minNode->left != nullptr)
      {
        minNode = minNode->left;
      }
      int tmpVualue = minNode->value;
      deleteNode(minNode->value);
      // 之所以要递归地删除，是因为它可能还有右子树，需要进行安全的操作，直接delete是不可以的。
      cur->value = tmpVualue;  // 赋值语句要在最后，否则先赋值的话，后面又会给删掉。
    }
  }
  void printTreebyLevel()
  {
    // 广度优先遍历：
    queue<treeNode*> q;
    q.push(root);
    while (!q.empty())
    {
      q.pop();
      treeNode* cur = q.front();
      cout << cur->value << " ";
      if (cur->left != nullptr) q.push(cur->left);
      if (cur->right != nullptr) q.push(cur->right);
    }
    cout << endl;
  }
  void printTreebyInorder()
  {
    std::stack<treeNode*> s;
    treeNode* cur = root;
    if (cur == nullptr)
    {
      cout << "empty tree" << endl;
      return;
    }
    s.push(cur);
    // 由于while循环只想判断栈是否为空，所以要先入栈根节点
    while (!s.empty())
    {
      while (cur->left != nullptr)
      {
        cur = cur->left;
        s.push(cur);
      }
      cur = s.top();
      cout << cur->value << " ";
      s.pop();
      if (cur->right != nullptr)
      {
        cur = cur->right;
        s.push(cur);
      }
    }
  }
  // 记录路径：（回溯）
  void preorder(treeNode* root)
  {
    if (root == nullptr) return;

    path.push_back(root);
    if (root->value == 8) res.push_back(path);
    if (root->value == 4) res.push_back(path);
    preorder(root->left);
    preorder(root->right);
    path.pop_back();
  }

  // 在记录基础上加上剪枝操作：遇到3则提前返回，不再搜索
  void preorder2(treeNode* root)
  {
    if (root == nullptr || root->value == 3) return;

    path.push_back(root);
    if (root->value == 8) res.push_back(path);
    if (root->value == 4) res.push_back(path);
    preorder2(root->left);
    preorder2(root->right);
    path.pop_back();
  }
};
int main()
{
  treeNode* root = new treeNode(5);
  searchTree tree(root);
  int a[10] = {3, 7, 1, 2, 9, 8, 6, 4, 10};
  for (int i = 0; i < 9; i++)
  {
    tree.insert(a[i]);
  }
  tree.printTreebyLevel();
  cout << endl;
  // tree.deleteNode(7);
  // tree.printTreebyInorder();
  cout << endl;
  tree.preorder2(root);

  for (auto i : tree.res)
  {
    for (auto j : i)
    {
      cout << j->value << " ";
    }
    cout << endl;
  }
}