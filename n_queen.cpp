#include "mycommon.h"

using namespace std;
// N皇后问题，皇后的数量和棋盘的大小相同，皇后之间不能在同一行，同一列，同一对角线上
void backtrack(int row, int n, vector<vector<string>>& state, vector<vector<vector<string>>>& res, vector<bool> col,
               vector<bool> slash, vector<bool> backslash)
{
  // 从上到下每一行放一个，row表示当前放到第几行
  if (row == n)
  {
    res.push_back(state);
    return;
  }

  for (int i = 0; i < n; i++)
  {
    int slash_index = row - i + n - 1;  // 主对角线
    int backslash_index = row + i;      // 副对角线
    // 如果当前列，主对角线，副对角线都没有放置皇后
    if (!col[i] && !slash[slash_index] && !backslash[backslash_index])
    {
      col[i] = true;
      slash[slash_index] = true;
      backslash[backslash_index] = true;
      state[row][i] = 'Q';
      backtrack(row + 1, n, state, res, col, slash, backslash);
      col[i] = false;
      slash[slash_index] = false;
      backslash[backslash_index] = false;
      state[row][i] = '#';
    }
  }
}
int main()
{
  int n = 8;
  vector<vector<vector<string>>> res;
  vector<vector<string>> state(n, vector<string>(n, "#"));
  vector<bool> col(n, false);
  vector<bool> slash(2 * n - 1, false);
  vector<bool> backslash(2 * n - 1, false);
  backtrack(0, n, state, res, col, slash, backslash);
  int count = 1;
  for (auto v : res)
  {
    cout << "Solution:" << count++ << endl;
    for (auto s : v)
    {
      for (auto c : s)
      {
        cout << c << "";
      }
      cout << endl;
    }
    cout << endl;
  }
}