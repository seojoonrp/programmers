#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

pii dfs(int n, const vector<vector<int>>& tree, const vector<int>& sales, int cur) {
  pii result = {sales[cur], 0};
  if (tree[cur].size() == 0) {
    return result;
  }

  int min_diff = 2e9;
  bool is_all_second = true;
  for (int child: tree[cur]) {
    pii ret = dfs(n, tree, sales, child);

    int smaller = min(ret.first, ret.second);
    result.first += smaller;
    result.second += smaller;

    if (smaller == ret.first) {
      is_all_second = false;
    } else {
      min_diff = min(min_diff, ret.first - ret.second);
    }
  }
  if (is_all_second) result.second += min_diff;

  return result;
}

int solution(vector<int> sales, vector<vector<int>> links) {
  int n = sales.size();
  sales.insert(sales.begin(), 0);

  vector<vector<int>> tree(n + 1);
  for (auto& link: links) {
    tree[link[0]].push_back(link[1]);
  }

  pii result = dfs(n, tree, sales, 1);
  int answer = min(result.first, result.second);
  return answer;
}