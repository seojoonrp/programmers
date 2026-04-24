#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

vector<int> solution(int m, int n, int h, int w, vector<vector<int>> drops) {
  vector<int> answer;
  const int INF = drops.size() + 1;
  vector<vector<int>> board(m, vector<int>(n, INF));

  for (int i = 0; i < (int)drops.size(); i++) {
    auto& drop = drops[i];
    board[drop[0]][drop[1]] = i + 1;
  }

  vector<vector<int>> row_min(m);
  for (int i = 0; i < m; i++) {
    deque<int> dq;
    for (int j = 0; j < n; j++) {
      if (!dq.empty() && dq.front() <= j - w) dq.pop_front();

      while (!dq.empty() && board[i][dq.back()] >= board[i][j]) dq.pop_back();

      dq.push_back(j);
      if (j >= w - 1) row_min[i].push_back(board[i][dq.front()]);
    }
  }

  int ans_val = -1;
  int ans_i = m, ans_j = n;

  for (int j = 0; j < n - w + 1; j++) {
    deque<int> dq;
    for (int i = 0; i < m; i++) {
      if (!dq.empty() && dq.front() <= i - h) dq.pop_front();

      while (!dq.empty() && row_min[dq.back()][j] >= row_min[i][j]) dq.pop_back();

      dq.push_back(i);
      if (i >= h - 1) {
        int cur_val = row_min[dq.front()][j];
        int cur_i = i - h + 1;

        if (ans_val < cur_val) {
          ans_val = cur_val;
          ans_i = cur_i;
          ans_j = j;
        } else if (ans_val == cur_val) {
          if (cur_i < ans_i) {
            ans_i = cur_i;
            ans_j = j;
          }
        }
      }
    }
  }

  answer.push_back(ans_i);
  answer.push_back(ans_j);
  return answer;
}