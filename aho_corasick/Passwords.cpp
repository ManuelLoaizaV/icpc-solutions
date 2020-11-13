#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;

const Long MOD = 1e6 + 3;
const int ALPH = 26;
const int ALPHABET = 62;
const int N = 50;
const int NODES = 1005;
const int SIZE = 20;

Long A, B;
string words[N];
Long dp[NODES][SIZE][2][2][2];
bool is_done[NODES][SIZE][2][2][2];
vector<int> values;

Long Sum(Long a, Long b) {
  return (a + b) % MOD;
}

struct Trie {
  int trie[NODES][ALPHABET];
  bool is_end[NODES];
  int fail[NODES];
  int fail_out[NODES];
  int nodes = 1;

  void Initialize(void) {
    for (int i = 0; i < nodes; i++) {
      is_end[i] = false;
      fail[i] = 0;
      fail_out[i] = 0;
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
    }
    nodes = 1;
  }

  void AddWord(string& s) {
    int from = 0;
    for (char chr : s) {
      int to = chr - 'a';
      if (trie[from][to] == 0) trie[from][to] = nodes++;
      from = trie[from][to];
    }
    is_end[from] = true;
  }

  void Build(void) {
    queue<int> q;
    for (int i = 0; i < ALPHABET; i++) {
      int to = trie[0][i];
      if (to > 0) q.push(to);
    }
    while (!q.empty()) {
      int from = q.front();
      q.pop();
      for (int chr = 0; chr < ALPHABET; chr++) {
        int to = trie[from][chr];
        if (to > 0) {
          q.push(to);
          fail[to] = fail[from];
          while (fail[to] > 0 && trie[fail[to]][chr] == 0)
            fail[to] = fail[fail[to]];
          fail[to] = trie[fail[to]][chr];
          fail_out[to] = is_end[fail[to]] ? fail[to] : fail_out[fail[to]];
        }
      }
    }
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
} aho;

Long DP(Long node, Long size, bool has_low, bool has_upp, bool has_dig) {
  if (size == B) {
    if (has_low && has_upp && has_dig) return 1LL;
    return 0LL;
  }
  
  Long& memo = dp[node][size][has_low][has_upp][has_dig];
  
  if (is_done[node][size][has_low][has_upp][has_dig])
    return memo;
  
  memo = (size >= A && has_low && has_upp && has_dig);

  for (int i = 0; i < values.size(); i++) {
    int from = node;
    int to = values[i];
    while (from > 0 && aho.GetNode(from, to) == 0) from = aho.GetFail(from);
    int next_node = aho.GetNode(from, to);
    int back = next_node;
    bool is_valid = true;
    while (back > 0) {
      if (aho.IsEnd(back)) {
        is_valid = false;
        break;
      }
      back = aho.GetFailOut(back);
    }
    if (is_valid) {
      Long next_dp;
      if (i < ALPH) {
        next_dp = DP(next_node, size + 1, true, has_upp, has_dig);
      } else {
        if (i < 2 * ALPH) {
          next_dp = DP(next_node, size + 1, has_low, true, has_dig);
        } else {
          next_dp = DP(next_node, size + 1, has_low, has_upp, true);
        }
      }
      memo = Sum(memo, next_dp);
    }
  }

  is_done[node][size][has_low][has_upp][has_dig] = true;
  return memo;
}

void Initialize(void) {
  int n = aho.nodes;
  aho.Initialize();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < B; j++)
      for (int k = 0; k < 2; k++)
        for (int l = 0; l < 2; l++)
          for (int m = 0; m < 2; m++)
            is_done[i][j][k][l][m] = false;
}

void Solve(void) {
  Initialize();
  Long n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> words[i];
    aho.AddWord(words[i]);
  }
  aho.Build();
  cout << DP(0, 0, false, false, false) << '\n';
}

int main(void) {
  FAST_IO;
  for (int i = 0; i < ALPH; i++) values.push_back(i);
  for (int i = 0; i < ALPH; i++) values.push_back(i);
  for (int i = 0; i < 10; i++) values.push_back(52 + i);
  values[52] = 'o' - 'a';
  values[53] = 'i' - 'a';
  values[55] = 'e' - 'a';
  values[57] = 's' - 'a';
  values[59] = 't' - 'a';
  while (cin >> A >> B) Solve();
  return 0;
}
