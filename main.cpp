#include "mycommon.h"

using namespace std;

vector<std::pair<int, int>> twosumhashtbale(vector<int>& nums, int target)
{
  // 返回所有可能得取值：
  vector<std::pair<int, int>> results;
  int size = nums.size();
  unordered_map<int, int> hashtable;
  for (int i = 0; i < size; i++)
  {
    if (hashtable.find(target - nums[i]) != hashtable.end())
    {
      results.push_back({hashtable[target - nums[i]], i});
    }
    hashtable.emplace(nums[i], i);
  }
  return results;
}
vector<int> bubble(vector<int>& nums)
{
  int size = nums.size();
  // 有两种写法，一种是从后往前，一种是从前往后
  for (int i = 0; i < size - 1; i++)
  {
    bool flag = false;
    // 未排序区间为[i, size - 1]，每次都将最小的放在最前
    for (int j = size - 1; j > i; j--)
    {
      if (nums[j] < nums[j - 1])
      {
        swap(nums[j], nums[j - 1]);
        flag = true;
      }
    }
    if (!flag) break;
  }

  //   for (int i = size - 1; i > 0; i--)
  //   {
  //     // 未排序区间为[0,i]，每次都将最大的放在最后
  //     for (int j = 0; j < i; j++)
  //     {
  //       if (nums[j] > nums[j + 1])
  //       {
  //         swap(nums[j], nums[j + 1]);
  //       }
  //     }
  //   }

  return nums;
}
vector<int> insertsort1(vector<int>& nums)
{
  int size = nums.size();
  for (int i = 1; i < size; i++)
  {
    int base = nums[i];
    int j = i - 1;
    while (j >= 0 && nums[j] > base)
    {
      nums[j + 1] = nums[j];
      j--;
    }
    nums[j + 1] = base;
  }
  return nums;
}
vector<int> select_sort(vector<int>& nums)
{
  int size = nums.size();
  for (int i = 0; i < size; i++)
  {
    int min = i;
    for (int j = i + 1; j < size; j++)
    {
      if (nums[j] < nums[min]) min = j;
    }
    swap(nums[i], nums[min]);
  }
  return nums;
}
int qs_helper(vector<int>& nums, int l, int r)
{
  int i = l, j = r;
  while (i < j)
  {
    // find first element < base
    while (j > i && nums[j] >= nums[l]) j--;
    // find first element > base
    while (i < j && nums[i] <= nums[l]) i++;
    swap(nums[i], nums[j]);
  }
  swap(nums[i], nums[l]);
  return i;
}

void qs(vector<int>& nums, int l, int r)
{
  if (l >= r) return;

  int pivot = qs_helper(nums, l, r);
  qs(nums, l, pivot - 1);
  qs(nums, pivot + 1, r);
}
void mergesort_helper(vector<int>& nums, int left, int mid, int right)
{
  vector<int> temp;
  int i = left, j = mid + 1;
  while (i <= mid && j <= right)
  {
    if (nums[i] <= nums[j])
      temp.push_back(nums[i++]);
    else
      temp.push_back(nums[j++]);
  }
  while (i <= mid) temp.push_back(nums[i++]);
  while (j <= right) temp.push_back(nums[j++]);
  for (int i = 0; i < temp.size(); i++)
  {
    nums[left + i] = temp[i];
  }
}
void mergesort(vector<int>& nums, int l, int r)
{
  if (l >= r) return;
  int mid = l + (r - l) / 2;
  mergesort(nums, l, mid);
  mergesort(nums, mid + 1, r);
  mergesort_helper(nums, l, mid, r);
}

void siftdown(vector<int>& nums, int n, int i = 0)
{
  while (1)
  {
    int l = 2 * i + 1, r = 2 * i + 2;
    int max = i;
    if (l < n && nums[l] > nums[max]) max = l;
    if (r < n && nums[r] > nums[max]) max = r;
    if (max == i) break;

    swap(nums[i], nums[max]);
    i = max;
  }
}
void siftup(vector<int>& nums, int i)
{
  while (i > 0)
  {
    int parent = (i - 1) / 2;
    if (nums[parent] < nums[i])
    {
      swap(nums[parent], nums[i]);
      i = parent;
    }
    else
      break;
  }
}
void heapsort(vector<int>& nums)
{
  // 建堆，使用siftdown
  // i从最后一个非叶子节点开始，时间复杂度为O(n)
  for (int i = nums.size() / 2 - 1; i >= 0; i--) siftdown(nums, nums.size(), i);
  // 也可使用siftup,i从1开始，时间复杂度为O(nlogn)
  // for (int i = 1; i < nums.size(); i++) siftup(nums, i);
  // 排序，每次将堆顶元素与最后一个元素交换，然后调整堆
  for (int i = nums.size() - 1; i > 0; i--)
  {
    swap(nums[0], nums[i]);
    siftdown(nums, i);  // 每次堆的大小都在减小，i表示堆的大小
  }
}

void countingsort(vector<int>& nums)
{
  int max = *max_element(nums.begin(), nums.end());

  vector<int> count(max + 1, 0);
  for (auto num : nums) count[num]++;

  for (int i = 0; i < max; i++) count[i + 1] += count[i];

  vector<int> result(nums.size(), 0);
  for (int i = nums.size() - 1; i >= 0; i--)
  {
    int num = nums[i];
    result[count[num] - 1] = num;
    count[num]--;
  }
  nums = result;
}

int main()
{
  vector<int> nums = {2, 4, 1, 2, 6, 3, 5, 3, 1, 10, 2};
  int target = 24;
  // vector<std::pair<int, int>> result = twosumhashtbale(nums, target);
  // for (auto& [i, j] : result)
  // {
  //   cout << i << " " << j << endl;
  // }
  // vector<int> result = mergesort(nums, 0, nums.size() - 1);
  countingsort(nums);
  for (auto& i : nums)
  {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}