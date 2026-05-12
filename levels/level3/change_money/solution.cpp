#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;

int solution(int n, vector<int> money) {
  vector<int> dp(n + 1, 0);

  dp[0] = 1;
  for (int m : money) {
    for (int i = m; i <= n; i++) {
      dp[i] = (dp[i] + dp[i - m]) % MOD;
    }
  }
    
  int answer = dp[n];
  return answer;
}