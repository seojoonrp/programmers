#include <string>
#include <vector>

using namespace std;

const int HOUR = 24;

int solution(vector<int> players, int m, int k) {
  int answer = 0;

  vector<int> end_cnt(HOUR, 0);

  int cur_s = 1;
  for (int h = 0; h < HOUR; h++) {
    int cur_p = players[h];
    int needed = cur_p / m + 1;

    cur_s -= end_cnt[h];
    if (cur_s < needed) {
      answer += needed - cur_s;
      if (h + k < HOUR) {
        end_cnt[h + k] += needed - cur_s;
      }

      cur_s = needed;
    }
  }

  return answer;
}