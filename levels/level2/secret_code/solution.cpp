#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool is_possible(vector<bool>& check, vector<vector<int>>& q, vector<int>& ans) {
  for (int i = 0; i < q.size(); i++) {
    int right = 0;
    for (int j: q[i]) {
      if (check[j]) right++;
    }
    if (right != ans[i]) {
      return false;
    }
  }
  return true;
}

int solution(int n, vector<vector<int>> q, vector<int> ans) {
  int answer = 0;
  vector<int> comb(n, 0);

  for (int i = n - 5; i < n; i++) comb[i] = 1;

  while (true) {
    vector<bool> check(n + 1, false);
    for (int i = 0; i < n; i++) {
      if (comb[i] == 1) {
        check[i + 1] = true;
      }
    }

    if (is_possible(check, q, ans)) answer++;

    if (!next_permutation(comb.begin(), comb.end())) {
      break;
    }
  }

  return answer;
}