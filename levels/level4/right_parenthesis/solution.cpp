#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[29][29]; // dp[i][j] = i번째 문자까지 고려했을 때 카운터가 j인 경우의 수 합

int solution(int n) {
  dp[1][1] = 1;
  for (int i = 1; i < 2 * n; ++i) {
    for (int j = i % 2; j <= min(i, n); j += 2) {
      int p1 = (i + j) / 2;
      if (p1 < n) dp[i + 1][j + 1] += dp[i][j];
      if (j > 0) dp[i + 1][j - 1] += dp[i][j];
    }
  }

  return dp[2 * n][0];
}