#include <iostream>
#include <map>
#include <string>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef pair<int, int> Pair;

const int N = 1e5 + 5;

struct Trie {
  map<Pair, int> trie[N];
  Long cnt[N];
  int nodes = 1;

  void Initialize(void) {
    for (int i = 0; i < nodes; i++) {
      trie[i].clear();
      cnt[i] = 0;
    }
    nodes = 1;
  }

  void AddWord(string& s) {
    int from = 0;
    int len = s.size();
    for (int i = 0; i < len; i++) {
      Pair to = {s[i] - 'a', s[len - 1 - i] - 'a'};
      if (trie[from].count(to) == 0) trie[from][to] = nodes++;
      from = trie[from][to];
      cnt[from]++;
    }
  }

  Long DFS(int from, Long depth, Long& ans) {
    Long substract = 0;
    for (auto it : trie[from]) {
      int to = it.second;
      substract += DFS(to, depth + 1, ans);
    }
    if (from > 0) {
      cnt[from] -= substract;
      Long matches = cnt[from] / 2;
      ans += (matches * depth * depth);
      substract += (2 * matches);
      cnt[from] -= (2 * matches);
    }
    return substract;
  }
} trie;

void Solve(void) {
  trie.Initialize();
  int n;
  cin >> n;
  string word;
  for (int i = 0; i < n; i++) {
    cin >> word;
    trie.AddWord(word);
  }
  Long ans = 0LL;
  trie.DFS(0, 0LL, ans);
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
