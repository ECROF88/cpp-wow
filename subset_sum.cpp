#include "mycommon.h"

using namespace std;
// 元素可以重复选，但是最后返回的子序列不能重复。
//  如果没有重复元素：
void backtrack(vector<int>& state, vector<int>& chioces, vector<vector<int>>& res, int target, int start)
{
  if (target == 0)
  {
    res.push_back(state);
    return;
  }
  for (int i = start; i < chioces.size(); i++)
  {
    int chioce = chioces[i];
    if (target < chioce) return;
    state.push_back(chioces[i]);
    backtrack(state, chioces, res, target - chioce, i);
    state.pop_back();
  }
}
// 如果chioces存在重复元素:
void backtrack2(vector<int>& state, vector<int>& chioces, vector<vector<int>>& res, int target, int start)
{
  if (target == 0)
  {
    res.push_back(state);
    return;
  }

  for (int i = start; i < chioces.size(); i++)
  {
    // int chioce = chioces[i];
    if (target - chioces[i] < 0) break;
    if (i > start && chioces[i] == chioces[i - 1]) continue;  // 避免重复(如果有重复元素)
    state.push_back(chioces[i]);
    backtrack2(state, chioces, res, target - chioces[i], i);
    state.pop_back();
  }
}
int main()
{
  vector<int> state;
  vector<int> chioces = {1, 2, 2, 3, 4};
  // chioces.erase(std::unique(chioces.begin(), chioces.end()), chioces.end());
  sort(chioces.begin(), chioces.end());  // 排序的原因是因为要使用start来避免重复
  vector<vector<int>> res;
  backtrack2(state, chioces, res, 10, 0);
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
