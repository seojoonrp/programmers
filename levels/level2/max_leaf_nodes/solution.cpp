#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int& dist_limit, const vector<int>& dist_vec, const vector<int>& b_dists, const vector<int>& b_leafs, int idx) {
  if (idx == dist_vec.size()) return 1;

  if (dist_limit >= b_dists[idx]) {
    dist_limit -= b_dists[idx];
    return b_leafs[idx];
  }

  if (dist_limit >= 1) {
    dist_limit -= 1; 
    int leaves = 0;
    for (int i = 0; i < dist_vec[idx]; i++) {
      leaves += solve(dist_limit, dist_vec, b_dists, b_leafs, idx + 1);
    }
    return leaves;
  }

  return 1;
}

int get_max_leafs(int dist_limit, const vector<int>& dist_vec) {
  int d = dist_vec.size();
  if (d == 0) return 1;

  vector<int> b_dists(d, 0);
  vector<int> b_leafs(d, 0);

  b_dists.back() = 1;
  b_leafs.back() = dist_vec.back();

  for (int i = d - 2; i >= 0; i--) {
    b_dists[i] = b_dists[i + 1] * dist_vec[i] + 1;
    b_leafs[i] = b_leafs[i + 1] * dist_vec[i];
  }

  return solve(dist_limit, dist_vec, b_dists, b_leafs, 0);
}
int solution(int dist_limit, int split_limit) {
  int answer = 0;

  int two_cnt = 0;
  while (split_limit > 0) {
    vector<int> dist_vec;

    for (int i = 0; i < two_cnt; i++) dist_vec.push_back(2);
    
    int temp = split_limit;
    while (temp >= 3) {
      dist_vec.push_back(3);
      temp /= 3;
    }

    answer = max(answer, get_max_leafs(dist_limit, dist_vec));

    split_limit /= 2;
    two_cnt++;
  }
  
  return answer;
}