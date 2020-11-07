#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define debug(x) cout << #x << " = " << x << '\n'
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int ALPHABET = 26;
const int INF = 1e9;
const int N = 3e5 + 5;

struct Trie {
  int trie[N][ALPHABET];
  bool is_end[N];
  int fail[N];
  int fail_out[N];
  multiset<int> value[N];
  int nodes;

  Trie(void) {
    for (int i = 0; i < N; i++) {
      is_end[i] = false;
      fail[i] = 0;
      fail_out[i] = 0;
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
    }
    nodes = 1;
  }

  void Build(void) {
    queue<int> q;
    q.push(0);
    while (q.size() > 0) {
      int from = q.front();
      q.pop();
      for (int chr = 0; chr < ALPHABET; chr++) {
        int to = trie[from][chr];
        if (to > 0) {
          q.push(to);
          if (from > 0) {
            fail[to] = fail[from];
            while (fail[to] > 0 && trie[fail[to]][chr] == 0) fail[to] = fail[fail[to]];
            fail[to] = trie[fail[to]][chr];
            fail_out[to] = is_end[fail[to]] ? fail[to] : fail_out[fail[to]];
          }
        }
      }
    }
  }

  int Add(string& s) {
    int from = 0;
    for (char chr : s) {
      int to = chr - 'a';
      if (trie[from][to] == 0) trie[from][to] = nodes++;
      from = trie[from][to];
    }
    value[from].insert(0);
    is_end[from] = true;
    return from;
  }

  void Update(int from, int new_value, int prev_value) {
    auto it = value[from].find(-1 * prev_value);
    //assert(it != value[from].end());
    value[from].erase(it);
    value[from].insert(-1 * new_value);
  }

  bool IsEnd(int ind) {
    return is_end[ind];
  }

  int GetFail(int ind) {
    return fail[ind];
  }

  int GetFailOut(int ind) {
    return fail_out[ind];
  }

  int GetNode(int from, int to) {
    return trie[from][to];
  }

  int GetValue(int ind) {
    auto it = value[ind].begin();
    return ((-1) * (*it));
  }
} trie;

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  vector<string> people(n);
  vector<int> prev(n);
  vector<int> last(n);
  for (int i = 0; i < n; i++) {
    cin >> people[i];
    last[i] = trie.Add(people[i]);
    prev[i] = 0;
  }
  trie.Build();

  while (m--) {
    int type;
    cin >> type;
    if (type == 1) {
      int ind, val;
      cin >> ind >> val;
      ind--;
      trie.Update(last[ind], val, prev[ind]);
      prev[ind] = val;
    } else {
      string s;
      cin >> s;
      int from = 0;
      int ans = -1;
      //debug(s);
      for (char chr : s) {
        //debug(chr);
        int to = chr - 'a';
        while (from > 0 && trie.GetNode(from, to) == 0) from = trie.GetFail(from);
        from = trie.GetNode(from, to);
        int back = from;
        while (back > 0) {
          //debug(back);
          //debug(trie.GetValue(back));
          if (trie.IsEnd(back)) ans = max(ans, trie.GetValue(back));
          back = trie.GetFailOut(back);
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
