#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
using pii = pair<int, int>;

const int GRID = 40 + 5;
const int PANEL = 15 + 1;

int n, m, p, s;
int edist[GRID][GRID];
int pdist[PANEL][PANEL];

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

const int INF = 1e9;
int dp[PANEL][1 << PANEL];
int need[PANEL];

bool is_safe(int x, int y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

void get_edist(vector<string>& grid) {
  int ex, ey;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '@') {
        ex = i; ey = j;
        break;
      }
    }
  }

  queue<pii> q;
  q.push({ex, ey});
  
  while (!q.empty()) {
    pii cur = q.front();
    q.pop();

    for (int d = 0; d < 4; d++) {
      int nx = cur.first + dx[d];
      int ny = cur.second + dy[d];

      if (is_safe(nx, ny) && !edist[nx][ny] && grid[nx][ny] == '.') {
        edist[nx][ny] = edist[cur.first][cur.second] + 1;
        q.push({nx, ny});
      }
    }
  }
}

int bfs_same_floor(vector<string>& grid, int sx, int sy, int ex, int ey) {
  vector<vector<int>> dist(n, vector<int>(m, -1));
  queue<pii> q;
  q.push({sx, sy});
  dist[sx][sy] = 0;

  while (!q.empty()) {
    pii cur = q.front(); q.pop();
    if (cur.first == ex && cur.second == ey) return dist[ex][ey];

    for (int d = 0; d < 4; d++) {
      int nx = cur.first + dx[d];
      int ny = cur.second + dy[d];

      if (is_safe(nx, ny) && dist[nx][ny] == -1 && grid[nx][ny] != '#') {
        dist[nx][ny] = dist[cur.first][cur.second] + 1;
        q.push({nx, ny});
      }
    }
  }
  return -1;
}

void get_pdist(vector<string>& grid, vector<vector<int>>& panels) {
  for (int i = 0; i < p; i++) {
    for (int j = i + 1; j < p; j++) {
      if (i == j) continue;

      vector<int> pi = panels[i];
      vector<int> pj = panels[j];

      if (pi[0] != pj[0]) {
        pdist[i][j] = edist[pi[1] - 1][pi[2] - 1]
          + edist[pj[1] - 1][pj[2] - 1]
          + abs(pi[0] - pj[0]);
      } else {
        pdist[i][j] = bfs_same_floor(grid, pi[1] - 1, pi[2] - 1, pj[1] - 1, pj[2] - 1);
      }

      pdist[j][i] = pdist[i][j];
    }
  }
}

int solution(int h, vector<string> grid, vector<vector<int>> panels, vector<vector<int>> seqs) {
  n = grid.size();
  m = grid[0].length();
  p = panels.size();
  s = seqs.size();

  get_edist(grid);
  get_pdist(grid, panels);

  for (auto& seq: seqs) {
    need[seq[1] - 1] |= 1 << (seq[0] - 1);
  }

  for (int cur = 0; cur < p; cur++) {
    for (int state = 0; state < (1 << p); state++) {
      dp[cur][state] = INF;
    }
  }
  dp[0][0] = 0;

  for (int state = 0; state < (1 << p); state++) {
    for (int cur = 0; cur < p; cur++) {
      if (dp[cur][state] == INF) continue;

      for (int nxt = 0; nxt < p; nxt++) {
        if (state & (1 << nxt)) continue;

        if ((need[nxt] & state) == need[nxt]) {
          int nxt_state = state | (1 << nxt);
          dp[nxt][nxt_state] = min(
            dp[nxt][nxt_state],
            dp[cur][state] + pdist[cur][nxt]
          );
        }
      }
    }
  }

  int answer = INF;
  for (int i = 0; i < p; i++) answer = min(answer, dp[i][(1 << p) - 1]);
  return answer;
}