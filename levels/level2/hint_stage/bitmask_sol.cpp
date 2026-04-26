#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int solution(vector<vector<int>> cost, vector<vector<int>> hint) {
  int answer = INF;

  int n = cost.size();
  int k = hint[0].size() - 1;

  vector<vector<int>> hint_inc(n, vector<int>(n, 0));
  for (int s = 0; s < n - 1; s++) {
    for (int h = 1; h <= k; h++) {
      hint_inc[s][hint[s][h] - 1]++;
    }
  }

  vector<vector<int>> dp(n, vector<int>((1 << n), INF));
  dp[0][0] = 0;

  for (int s = 0; s < n; s++) {
    for (int state = 0; state < (1 << s); state++) {
      if (dp[s][state] == INF) continue;

      int hint_count = 0;
      for (int i = 0; i < s; i++) {
        if (state & (1 << i)) hint_count += hint_inc[i][s];
      }
      hint_count = min(hint_count, n - 1);

      int cur_cost = cost[s][hint_count];

      if (s == n - 1) {
        answer = min(answer, cur_cost + dp[s][state]);
      } else {
        dp[s + 1][state] = min(dp[s + 1][state], dp[s][state] + cur_cost);
        dp[s + 1][state | (1 << s)] = min(
          dp[s + 1][state | (1 << s)],
          dp[s][state] + cur_cost + hint[s][0]
        );
      }
    }
  }

  return answer;
}