#include <string>
#include <vector>
#include <set>

using namespace std;

struct Word {
  string s;
  bool shown;
};

set<string> shown;
vector<Word> words;

int solution(string message, vector<vector<int>> spoiler_ranges) {
  int n = message.length();

  int cur_word_start = 0;
  string cur_word = "";
  for (int i = 0; i <= n; i++) {
    if (i == n || message[i] == ' ') {
      int cur_word_end = i - 1;
      bool is_shown = true;

      for (auto& range: spoiler_ranges) {
        if (!(range[1] < cur_word_start || range[0] > cur_word_end)) {
          is_shown = false;
          break;
        }
      }

      if (is_shown) shown.insert(cur_word);

      words.push_back({cur_word, is_shown});
      cur_word = "";
      cur_word_start = i + 1;
    } else {
      cur_word += message[i];
    }
  }

  int answer = 0;

  for (auto& word: words) {
    if (word.shown) continue;
    
    if (shown.count(word.s)) continue;

    answer++;
    shown.insert(word.s);
  }

  return answer;
}