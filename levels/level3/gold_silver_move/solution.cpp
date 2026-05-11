#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

bool check(ll mid, int a, int b, vector<int>& g, vector<int>& s, vector<int>& w, vector<int>& t) {
  ll total_g = 0, total_s = 0, total_sum = 0;

  for (size_t i = 0; i < g.size(); ++i) {
    ll move_cnt = (mid + t[i]) / (2LL * t[i]);
    ll max_payload = move_cnt * w[i];

    ll cur_g = g[i];
    ll cur_s = s[i];

    total_g += min(cur_g, max_payload);
    total_s += min(cur_s, max_payload);
    total_sum += min(cur_g + cur_s, max_payload);
  }

  return total_g >= a && total_s >= b && total_sum >= (ll)a + b;
}

long long solution(int a, int b, vector<int> g, vector<int> s, vector<int> w, vector<int> t) {
  ll lo = 0;
  ll hi = 4e14;
  ll answer = hi;

  while (lo <= hi) {
    ll mid = (lo + hi) / 2;

    if (check(mid, a, b, g, s, w, t)) {
      answer = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  
  return answer;
}