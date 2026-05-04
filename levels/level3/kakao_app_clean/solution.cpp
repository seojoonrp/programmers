#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

struct App {
  int top;
  int bot;
  int left;
  int right;
  int size;
};

int n, m;
int app_cnt;
vector<App> apps;

void get_pushed_apps(int a, int d, set<int>& ret) {
  App aa = apps[a];
  for (int i = 0; i < app_cnt; i++) {
    if (i == a || ret.count(i) > 0) continue;

    App app = apps[i];
    bool pushed;
    switch (d) {
      case 1: pushed = (app.left == aa.right + 1) && !(app.bot < aa.top || app.top > aa.bot); break;
      case 2: pushed = (app.top == aa.bot + 1) && !(app.right < aa.left || app.left > aa.right); break;
      case 3: pushed = (app.right == aa.left - 1) && !(app.bot < aa.top || app.top > aa.bot); break;
      case 4: pushed = (app.bot == aa.top - 1) && !(app.right < aa.left || app.left > aa.right); break;
    }

    if (pushed) {
      ret.insert(i);
      get_pushed_apps(i, d, ret);
    }
  }
}

void push(int a, int d, queue<int>& offs) {
  set<int> pushed;
  pushed.insert(a);
  get_pushed_apps(a, d, pushed);

  // cout << "pushing: (a, d) = " << a << ' ' << d << '\n';
  // cout << "pushed apps: ";
  // for (int p: pushed) cout << p << ' ';
  // cout << "\n-----------------------\n";

  for (auto idx: pushed) {
    App& app = apps[idx];
    
   switch (d) {
    case 1: {
      app.left += 1;
      app.right += 1;
      if (app.right >= m) {
        offs.push(idx);
        app.right = -1;
        app.left = -app.size;
      }
      break;
    }
    case 2: {
      app.top += 1;
      app.bot += 1;
      if (app.bot >= n) {
        offs.push(idx);
        app.bot = -1;
        app.top = -app.size;
      }
      break;
    }
    case 3: {
      app.left -= 1;
      app.right -= 1;
      if (app.left < 0) {
        offs.push(idx);
        app.left = m;
        app.right = m + app.size - 1;
      }
      break;
    }
    case 4: {
      app.top -= 1;
      app.bot -= 1;
      if (app.top < 0) {
        offs.push(idx);
        app.top = n;
        app.bot = n + app.size - 1;
      }
      break;
    }
   }
  }
}

vector<vector<int>> solution(vector<vector<int>> board, vector<vector<int>> commands) {
  n = board.size();
  m = board[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) app_cnt = max(app_cnt, board[i][j]);
  }

  apps = vector<App>(app_cnt, {-1, -1, -1, -1, -1});
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] != 0 && apps[board[i][j] - 1].size == -1) {
        int a = board[i][j] - 1;
        apps[a] = {i, -1, j, -1, 0};
        while (j < m && board[i][j] == a + 1) {
          apps[a].size++;
          j++;
        }
        j--;
      }
    }
  }

  for (App& app: apps) {
    app.bot = app.top + app.size - 1;
    app.right = app.left + app.size - 1;
  }

  for (auto c: commands) {
    int a = c[0] - 1;
    int d = c[1];

    queue<int> offs;
    push(a, d, offs);

    while (!offs.empty()) {
      int o = offs.front();
      offs.pop();

      for (int i = 0; i < apps[o].size; i++) {
        push(o, d, offs);
      }
    }
  }

  vector<vector<int>> answer(n, vector<int>(m, 0));
  for (int a = 0; a < app_cnt; a++) {
    App app = apps[a];
    for (int i = 0; i < app.size; i++) {
      for (int j = 0; j < app.size; j++) {
        answer[app.top + i][app.left + j] = a + 1;
      }
    }
  }

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     cout << answer[i][j] << ' ';
  //   }
  //   cout << '\n';
  // }
  return answer;
}