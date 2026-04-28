// B[i] 합이 m보다 작다는 조건하에 A[i] 합을 최대화

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int CNT_MAX = 40;
const int M_MAX = 120;

// dp[i][j] = i번째 물건까지 고려헸을 때 B 합이 j이하로 만들 수 있는 A 합 최댓값
int dp[CNT_MAX + 5][M_MAX + 5];

int solution(vector<vector<int>> info, int n, int m) {
  int cnt = info.size();
  vector<int> A(cnt + 1), B(cnt + 1);
  for (int i = 1; i <= cnt; i++) {
    A[i] = info[i - 1][0];
    B[i] = info[i - 1][1];
  }

  for (int i = 1; i <= cnt; i++) {
    for (int j = 0; j < m; j++) {
      if (j >= B[i]) {
        dp[i][j] = max(
          dp[i - 1][j],
          dp[i - 1][j - B[i]] + A[i]
        );
      } else dp[i][j] = dp[i - 1][j];
    }
  }

  int not_a_sum = dp[cnt][m - 1];
  int a_total = 0;
  for (int i = 1; i <= cnt; i++) a_total += A[i];
  int a_sum = a_total - not_a_sum;

  int answer;
  if (a_sum >= n) answer = -1;
  else answer = a_sum;

  return answer;
}