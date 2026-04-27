#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int total_cost(vector<vector<int>>& cost, vector<vector<int>>& hint, int n, int k, vector<bool>& use) {
  vector<int> hint_count(n, 0);
  int res = 0;

  for (int s = 0; s < n; s++) {
    res += cost[s][hint_count[s]];

    if (s < n - 1 && use[s]) {
      res += hint[s][0];
      for (int h = 1; h <= k; h++) {
        int target = hint[s][h] - 1;
        if (hint_count[target] < n - 1) {
          hint_count[target]++;
        }
      }
    }
  }

  return res;
}

void backtrack(vector<vector<int>>& cost, vector<vector<int>>& hint, int n, int k, vector<bool>& use, int& answer) {
  if (use.size() == n - 1) {
    answer = min(answer, total_cost(cost, hint, n, k, use));
    return;
  }

  for (bool u: {true, false}) {
    use.push_back(u);
    backtrack(cost, hint, n, k, use, answer);
    use.pop_back();
  }
}

int solution(vector<vector<int>> cost, vector<vector<int>> hint) {
  int answer = INF;

  int n = cost.size();
  int k = hint[0].size() - 1;

  vector<bool> use;
  backtrack(cost, hint, n, k, use, answer);

  return answer;
}