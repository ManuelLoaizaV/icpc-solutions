//https://codeforces.com/problemset/problem/1202/E
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int ALPHABET = 26;
const int N = 2e5 + 5;

struct Trie {
  int trie[N][ALPHABET];
  bool is_end[N];
  int fail[N];
  int fail_out[N];
  Long cnt[N];
  int h[N];
  int nodes;

  void Clear(void) {
    for (int i = 0; i < N; i++) {
      is_end[i] = false;
      fail[i] = 0;
      fail_out[i] = 0;
      cnt[i] = 0;
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

  void AddWord(string& s) {
    int from = 0;
    int len = 0;
    for (char chr : s) {
      int to = chr - 'a';
      if (trie[from][to] == 0) trie[from][to] = nodes++;
      from = trie[from][to];
      h[from] = ++len;
    }
    is_end[from] = true;
    cnt[from]++;
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

  int GetHeight(int ind) {
    return h[ind];
  }

  Long GetCnt(int ind) {
    return cnt[ind];
  }
} aho;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string t;
  cin >> t;
  int n;
  cin >> n;
  aho.Clear();
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    aho.AddWord(s);
  }
  aho.Build();
  int from = 0;
  int len = (int) t.size();
  vector<Long> start(len, 0LL);
  vector<Long> finish(len, 0LL);
  for (int i = 0; i < len; i++) {
    int to = t[i] - 'a';
    while (from > 0 && aho.GetNode(from, to) == 0) from = aho.GetFail(from);
    from = aho.GetNode(from, to);
    int back = from;
    while (back > 0) {
      if (aho.IsEnd(back)) {
        int h = aho.GetHeight(back);
        Long cnt = aho.GetCnt(back);
        finish[i] += cnt;
        start[i - h + 1] += cnt;
      }
      back = aho.GetFailOut(back);
    }
  }
  Long ans = 0;
  for (int i = 0; i < len - 1; i++) {
    ans += finish[i] * start[i + 1];
  }
  cout << ans << '\n';
  return 0;
}
