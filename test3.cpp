#include <iostream>

#include "mycommon.h"

using namespace std;

class Solution
{
public:
  int lengthOfLongestSubstring(string s)
  {
    int n = s.size();
    // vevtor数组中存放的是每个字符在字符串s中出现的下标
    vector<int> pos(128, -1);
    int left = 0;
    int len = 0;
    for (int right = 0; right < n; right++) {
      left = max(left, pos[s[right]] + 1);
      len = max(len, right - left + 1);
      pos[s[right]] = right;
    }
    return len;
  }
};

int main()
{
  Solution s;
  std::cout << s.lengthOfLongestSubstring("bbba");
}