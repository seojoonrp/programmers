#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int get_child_cnt(int cur, int par, const vector<vector<int>>& tree, vector<int>& child_cnt) {
  int ret = 1;

  for (int child: tree[cur]) {
    if (child == par) continue;

    ret += get_child_cnt(child, cur, tree, child_cnt);
  }

  return child_cnt[cur] = ret;
}

int solution(int n, vector<vector<int>> wires) {
  vector<vector<int>> tree(n + 1);
  for (auto& w: wires) {
    tree[w[0]].push_back(w[1]);
    tree[w[1]].push_back(w[0]);
  }

  vector<int> child_cnt(n + 1);
  get_child_cnt(1, -1, tree, child_cnt);

  int answer = 1e9;
  for (int i = 2; i <= n; i++) {
    answer = min(answer, abs(child_cnt[i] - (n - child_cnt[i])));
    if (answer <= 1) break;
  }
  return answer;
}