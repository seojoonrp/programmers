#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph[4];

int infect(int n, int infection, vector<int>& types) {
  vector<bool> visited(n + 1, false);
  vector<int> idx;

  visited[infection] = true;
  idx.push_back(infection);

  for (int t: types) {
    for (int i = 0; i < idx.size(); i++) {
      int cur = idx[i];
      for (int nxt: graph[t][cur]) {
        if (!visited[nxt]) {
          visited[nxt] = true;
          idx.push_back(nxt);
        }
      }
    }
  }

  return idx.size();
}

void backtrack(int n, int infection, vector<int>& types, int& answer, int k) {
  if (types.size() == k) {
    answer = max(answer, infect(n, infection, types));
    return;
  }

  for (int t = 1; t <= 3; t++) {
    types.push_back(t);
    backtrack(n, infection, types, answer, k);
    types.pop_back();
  }
}

int solution(int n, int infection, vector<vector<int>> edges, int k) {
  for (int t = 1; t <= 3; t++) {
    graph[t].assign(n + 1, vector<int>());
  }

  for (auto& edge: edges) {
    auto& g = graph[edge[2]];
    g[edge[0]].push_back(edge[1]);
    g[edge[1]].push_back(edge[0]);
  }
  
  int answer = 0;
  vector<int> types;

  backtrack(n, infection, types, answer, k);

  return answer;
}