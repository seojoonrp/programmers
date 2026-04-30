#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

const int BAN_MAX = 3e5 + 5;
const ll ALP = 26;

ll ban[BAN_MAX];

ll str_to_num(string& s) {
  ll res = 0;
  for (char c: s) {
    res *= ALP;
    res += c - 'a' + 1;
  }
  return res;
}

string num_to_str(ll n) {
    string res = "";
    while (n > 0) {
        n--; 
        res += (n % ALP) + 'a';
        n /= ALP;
    }
    reverse(res.begin(), res.end());
    return res;
}

string solution(long long n, vector<string> bans) {
  int ban_cnt = bans.size();
  for (int i = 0; i < ban_cnt; i++) {
    ban[i] = str_to_num(bans[i]);
  }
  sort(ban, ban + ban_cnt);

  // for (int i = 0; i < ban_cnt; i++) {
  //   cout << ban[i] << ' ';
  // }
  // cout << '\n';

  int prev_less_cnt = 0;
  while (true) {
    // n 이하의 밴 수
    int less_cnt = upper_bound(ban, ban + ban_cnt, n) - ban;

    // cout << n << ' ' << less_cnt << '\n';

    if (less_cnt == prev_less_cnt) break;
    
    n += (less_cnt - prev_less_cnt);
    prev_less_cnt = less_cnt;
  }

  string answer = num_to_str(n);
  return answer;
}