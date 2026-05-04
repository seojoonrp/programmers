#include <string>
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

vector<vector<Edge>> graph;

vector<int> dijkstra(int s, int n) {
  vector<int> dist(n + 1, INF);

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

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
  graph.resize(n + 1);
  for (auto& fare: fares) {
    graph[fare[0]].push_back({fare[1], fare[2]});
    graph[fare[1]].push_back({fare[0], fare[2]});
  }

  vector<int> scost = dijkstra(s, n);
  vector<int> acost = dijkstra(a, n);
  vector<int> bcost = dijkstra(b, n);

  int answer = INF;
  for (int i = 1; i <= n; i++) {
    if (scost[i] == INF || acost[i] == INF || bcost[i] == INF) continue;
    answer = min(answer, scost[i] + acost[i] + bcost[i]);
  }
  return answer;
}