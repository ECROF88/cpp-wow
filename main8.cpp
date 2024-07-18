#include <cmath>
#include <cstring>  // Include cstring for memset
#include <iostream>
#include <limits>
#include <vector>

#include "mycommon.h"

// using namespace std;
// 0-1背包问题
int knapsackDP(std::vector<int>& weight, std::vector<int>& value, int cap)
{
  int n = weight.size();

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(cap + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= cap; j++) {
      dp[i][j] = dp[i - 1][j];
      if (j >= weight[i - 1]) {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weight[i - 1]] + value[i - 1]);
      }
    }
  }
  return dp[n][cap];
}

// 0-1背包问题（空间优化）
int knapsackDPOpt(std::vector<int>& weight, std::vector<int>& value, int cap)
{
  int n = weight.size();
  std::vector<int> dp(cap + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = cap; j >= weight[i - 1]; j--) {
      dp[j] = std::max(dp[j], dp[j - weight[i - 1]] + value[i - 1]);
    }
  }
  return dp[cap];
}

double coinchangeDP(std::vector<double>& coins, double amount)
{
  int n = coins.size();
  int a = static_cast<int>(round(amount * 100));  // 将金额转换为整数
  int max = std::numeric_limits<int>::max() - 1;
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(a + 1, max));

  for (int i = 0; i <= n; i++) dp[i][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= a; j++) {
      int coinValue = static_cast<int>(round(coins[i - 1] * 100));  // 将硬币值转换为整数
      if (coinValue > j)
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] = std::min(dp[i][j], dp[i][j - coinValue] + 1);
    }
  }
  return dp[n][a] > max ? -1 : dp[n][a];  // 将结果转换回浮点数
}

int main()
{
  std::vector<double> coins = {0.01, 0.1, 0.25};
  double amount = 1.0;
  std::cout << coinchangeDP(coins, amount) << std::endl;

  int len = 10;
  char aa[10];
  std::cout << aa[0] << std ::endl;
}