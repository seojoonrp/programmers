#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> signals) {
  int n = signals.size();

  vector<int> periods;
  int period_mul = 1;
  for(auto& sig: signals) {
    periods.push_back(sig[0] + sig[1] + sig[2]);
    period_mul *= periods.back();
  }

  int answer = -1;
  for (int t = 1; t <= period_mul; t++) {
    bool flag = true;
    for (int i = 0; i < n; i++) {
      if (t % periods[i] < signals[i][0] ||
          t % periods[i] >= signals[i][0] + signals[i][1]) {
        flag = false;
        break;
      }
    }

    if (flag) {
      answer = t + 1;
      break;
    }
  }

  return answer;
}