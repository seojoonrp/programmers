#include <string>
#include <vector>

using namespace std;

const int INF = 1e9;

struct Memo {
  int darts;
  int sb;
};

struct Throw {
  int score;
  int sb;
};

vector<int> solution(int target) {
  vector<Memo> dp(target + 1, {INF, 0});
  dp[0] = {0, 0};

  vector<Throw> throws;
  for (int i = 1; i <= 20; ++i) {
    throws.push_back({i, 1});
    throws.push_back({i * 2, 0});
    throws.push_back({i * 3, 0});
  }
  throws.push_back({50, 1});

  for (int i = 1; i <= target; ++i) {
    for (Throw& t: throws) {
      if (i >= t.score) {
        Memo cur = {dp[i - t.score].darts + 1, dp[i - t.score].sb + t.sb};

        if (cur.darts < dp[i].darts) {
          dp[i] = {cur.darts, cur.sb};
        } else if (cur.darts == dp[i].darts && cur.sb > dp[i].sb) {
          dp[i].sb = cur.sb;
        }
      }
    }
  }

  vector<int> answer = {dp[target].darts, dp[target].sb};
  return answer;
}