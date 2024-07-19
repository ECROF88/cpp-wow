#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
/*
给定一个字符串s,请你找出其中不含有重复字符的最长子串的长度。
*/
class Solution
{
public:
  int lengthOfLongestSubstring1(string s)
  {
    int n = s.size();
    // vevtor数组中存放的是每个字符在字符串s中出现的下标
    vector<int> pos(128, -1);
    int left = 0;
    int len = 0;
    for (int right = 0; right < n; right++) {
      left = std::max(left, pos[s[right]] + 1);
      len = max(len, right - left + 1);
      pos[s[right]] = right;
    }
    return len;
  }
  int lengthOfLongestSubstring2(string s)
  {
    // 使用unordered_set
    std::unordered_set<char> occ;
    int n = s.size();
    int ans = 0;
    int rk = -1;
    for (int l = 0; l < n; l++) {
      if (l != 0) occ.erase(s[l - 1]);

      while (rk < n - 1 && occ.count(s[rk + 1]) == 0) {
        occ.insert(s[rk + 1]);
        rk++;
      }
      ans = std::max(ans, rk - l + 1);
    }
    return ans;
  }
  int lengthOfLongestSubstring3(string s)
  {
    int n = s.size();
    int len = 0;
    int max = 0;
    int left = 0;
    for (int right = 0; right < n; right++) {
      for (int l = left; l < right; l++) {
        if (s[l] == s[right]) {
          left = l + 1;
          break;
        }
      }
      len = right - left + 1;
      max = std::max(max, len);
    }
    return max;
  }
};

int main()
{
  Solution s;
  std::cout << s.lengthOfLongestSubstring3("  ");
}