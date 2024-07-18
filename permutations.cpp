#include "mycommon.h"
using namespace std;

void backtrack(vector<int>& state, vector<int>& chioces, vector<bool>& selected, vector<vector<int>>& res)
{
  if (state.size() == chioces.size())
  {
    res.push_back(state);
    return;
  }
  unordered_set<int> used;
  // set中没有重复元素，所以可以用set来判断是否有重复元素,每一层选择都会创建一个新的set
  for (int i = 0; i < chioces.size(); i++)
  {
    int chioce = chioces[i];
    if (!selected[i] && used.find(chioce) == used.end())
    {
      used.emplace(chioce);
      selected[i] = true;
      state.push_back(chioces[i]);
      backtrack(state, chioces, selected, res);
      selected[i] = false;
      state.pop_back();
    }
  }
}

int main()
{
  vector<int> state;
  vector<int> chioces = {1, 2, 2, 2};
  vector<bool> selected(chioces.size(), false);
  vector<vector<int>> res;
  backtrack(state, chioces, selected, res);
  cout << "res.size():" << res.size() << endl;
  for (auto v : res)
  {
    for (auto i : v)
    {
      cout << i << " ";
    }
    cout << endl;
  }
}