#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

struct Node {
  int x;
  int left;
  int right;
};

int Y;
vector<vector<int>> compy_x;
vector<Node> nodes;

map<int, int> x_idx;

void get_compy_x(vector<vector<int>>& nodeinfo) {
  vector<int> ys;
  for (auto& node: nodeinfo) ys.push_back(node[1]);
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  Y = ys.size();
  compy_x.resize(Y);

  for (auto& node: nodeinfo) {
    int y_idx = lower_bound(ys.begin(), ys.end(), node[1]) - ys.begin();
    compy_x[y_idx].push_back(node[0]);
  }

  for (auto& xs: compy_x) sort(xs.begin(), xs.end());

  reverse(compy_x.begin(), compy_x.end());
}

void create_tree(int cur, int depth, int min_x, int max_x) {
  Node& node = nodes[cur];

  for (int d = depth + 1; d < Y; d++) {
    bool found = false;
    for (int x : compy_x[d]) {
      if (x > min_x && x < cur) {
        node.left = x;
        create_tree(x, d, min_x, cur);
        found = true;
        break;
      }
    }
    if (found) break; 
  }

  for (int d = depth + 1; d < Y; d++) {
    bool found = false;
    for (int x : compy_x[d]) {
      if (x > cur && x < max_x) {
        node.right = x;
        create_tree(x, d, cur, max_x);
        found = true;
        break;
      }
    }
    if (found) break; 
  }
}

void preorder(int cur, vector<int>& res) {
  Node& node = nodes[cur];

  res.push_back(x_idx[cur]);
  if (node.left != -1) preorder(node.left, res);
  if (node.right != -1) preorder(node.right, res);
}

void postorder(int cur, vector<int>& res) {
  Node& node = nodes[cur];

  if (node.left != -1) postorder(node.left, res);
  if (node.right != -1) postorder(node.right, res);
  res.push_back(x_idx[cur]);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
  get_compy_x(nodeinfo);
  // for (int i = 0; i < Y; i++) {
  //   cout << i << " | ";
  //   for (int x: compy_x[i]) cout << x << ' ';
  //   cout << '\n';
  // }

  nodes.resize(100001, {-1, -1, -1});
  int root = compy_x[0][0];

  create_tree(root, 0, -1, 100001);

  for (int i = 0; i < nodeinfo.size(); i++) {
    x_idx.insert({nodeinfo[i][0], i + 1});
  }

  vector<vector<int>> answer(2);
  preorder(root, answer[0]);
  postorder(root, answer[1]);
  return answer;
}