#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using pii = pair<int, int>;

const int INF = 1e9;

struct Edge {
  int to;
  int cost;
};

int n;
vector<vector<Edge>> graph;

vector<int> dijkstra(int s) {
  vector<int> dist(n, INF); // 0-index

  // {mindist, idx}
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  dist[s] = 0;
  pq.push({0, s});

  while (!pq.empty()) {
    pii cur = pq.top();
    pq.pop();

    if (dist[cur.second] < cur.first) continue;

    for (auto& e: graph[cur.second]) {
      if (cur.first + e.cost < dist[e.to]) {
        dist[e.to] = cur.first + e.cost;
        pq.push({dist[e.to], e.to});
      }
    }
  }

  return dist;
}
