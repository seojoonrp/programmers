#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int traverse(int cur, int& cut_count, int m, const vector<int>& num, const vector<vector<int>>& links) {
  int left = links[cur][0];
  int right = links[cur][1];
  int curn = num[cur];

  if (left == -1 && right == -1) return curn;

  if (left == -1 || right == -1) {
    int child = left == -1 ? right : left;
    int child_ret = traverse(child, cut_count, m, num, links);
    
    if (child_ret + curn > m) {
      cut_count++;
      return curn;
    } else {
      return curn + child_ret;
    }
  }

  int left_ret = traverse(left, cut_count, m, num, links);
  int right_ret = traverse(right, cut_count, m, num, links);
  
  int total = left_ret + right_ret + curn;
  if (total <= m) return total;
  else {
    int cut_bigger = total - max(left_ret, right_ret);
    cut_count++;
    if (cut_bigger <= m) return cut_bigger;
    else {
      cut_count++;
      return curn;
    }
  }
}

bool check(int m, int k, const vector<int>& num, const vector<vector<int>>& links, int root) {
  int cut_count = 0;
  traverse(root, cut_count, m, num, links);
  return cut_count < k;
}

int solution(int k, vector<int> num, vector<vector<int>> links) {
  int answer = 0;

  int lo = 0;
  int hi = 0;
  for (int cap: num) {
    lo = max(lo, cap);
    hi += cap;
  }

  int n = num.size();
  vector<bool> visited(n, false);
  int root = n * (n - 1) / 2;
  for (auto& link: links) {
    for (int c: link) {
      if (c >= 0 && !visited[c]) {
        visited[c] = true;
        root -= c;
      }
    }
  }
  
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (check(mid, k, num, links, root)) {
      answer = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  return answer;
}