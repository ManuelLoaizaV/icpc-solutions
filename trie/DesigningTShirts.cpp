// Gracias, Osman
#include <iostream>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

const int N = 1e5 + 30;
const int ALPHABET = 26;

struct Trie {
  int nodes;
  int trie[N][ALPHABET];
  int cnt[N][2];
  bool first_time = true;

  void Build(void) {
    if (first_time) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) cnt[i][j] = 0;
        for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
      }
      first_time = false;
      nodes = 1;
      return;
    }
    for (int i = 0; i < nodes; i++) {
      cnt[i][0] = cnt[i][1] = 0;
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
    }
    nodes = 1;
  }

  void AddWord(string& s) {
    int u = 0;
    for (char chr : s) {
      int c = chr - 'A';
      if (trie[u][c] == 0) trie[u][c] = nodes++;
      u = trie[u][c];
      cnt[u][0]++;
      //debug(chr);
      //debug(u);
    }
  }

  void Update(string& s) {
    int u = 0;
    for (char chr : s) {
      int c = chr - 'A';
      if (trie[u][c] == 0) return;
      u = trie[u][c];
      cnt[u][1]++;
    }
  }

  int Query(void) {
    int answer = 0;
    for (int i = 0; i < nodes; i++) answer += min(cnt[i][0], cnt[i][1]);
    return answer;
  }
} osman;

void Solve(int n) {
  osman.Build();
  string word;
  for (int i = 0; i < n; i++) {
    cin >> word;
    osman.AddWord(word);
  }
  for (int i = 0; i < n; i++) {
    cin >> word;
    osman.Update(word);
  }
  cout << osman.Query() << '\n';
}

int main(void) {
  FAST_IO;
  int n;
  while (cin >> n) {
    if (n == -1) break;
    Solve(n);
  }
  return 0;
}
