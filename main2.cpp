/*
  从个位开始排序。
*/

#include "mycommon.h"

using namespace std;
const static int BASE = 2;
int getdigit(int num, int e) { return (num / e) % BASE; }  // 取出数字num的第e位数字

void s(vector<int> &nums, int e)
{
  vector<int> count(BASE, 0);
  for (int i = 0; i < nums.size(); i++) count[getdigit(nums[i], e)]++;
  for (int i = 1; i < count.size(); i++) count[i] += count[i - 1];

  vector<int> result(nums.size(), 0);
  for (int i = nums.size() - 1; i >= 0; i--)
  {
    int j = getdigit(nums[i], e);
    result[count[j] - 1] = nums[i];
    count[j]--;
  }
  nums = result;
}

void radixsort(vector<int> &nums)
{
  int max = *max_element(nums.begin(), nums.end());
  for (int e = 1; max / e > 0; e *= BASE) s(nums, e);
}
void printvector(vector<int> &nums)
{
  for (auto i : nums) printf("%d ", i);
}

int main()
{
  // BASE=2;
  vector<int> nums = {11, 10, 111, 1111, 1010, 1001};
  radixsort(nums);
  printvector(nums);
  return 0;
}