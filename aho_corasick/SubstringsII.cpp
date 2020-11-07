#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

const int ALPHABET = 26;
const int N = 6e5 + 5;

struct Trie {
  int trie[N][ALPHABET];
  bool is_end[N];
  int fail[N];
  int fail_out[N];
  int cnt[N];
  int nodes;

  Trie(void) {
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

  int Add(string& s) {
    int from = 0;
    for (char chr : s) {
      int to = chr - 'a';
      if (trie[from][to] == 0) trie[from][to] = nodes++;
      from = trie[from][to];
    }
    is_end[from] = true;
    return from;
  }

  void Update(int ind) {
    cnt[ind]++;
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

  int GetCnt(int ind) {
    return cnt[ind];
  }
} aho;

int A, B;

int GetChar(int ans) {
  return ((A * ans + B) % 26);
}

int main(void) {
  FAST_IO;
  string text;
  cin >> text;
  int q;
  cin >> q >> A >> B;
  vector<string> s(q);
  vector<int> pos(q);

  for (int i = 0; i < q; i++) {
    cin >> s[i];
    pos[i] = aho.Add(s[i]);
  }

  aho.Build();
  int from = 0;
  for (char chr : text) {
    int to = chr - 'a';
    while (from > 0 && aho.GetNode(from, to) == 0) from = aho.GetFail(from);
    from = aho.GetNode(from, to);
    int back = from;
    while (back > 0) {
      if (aho.IsEnd(back)) aho.Update(back);
      back = aho.GetFailOut(back);
    }
  }

  int ans = aho.GetCnt(pos[0]);
  cout << ans << '\n';

  for (int i = 1; i < q; i++) {
    int to = GetChar(ans);
    while (from > 0 && aho.GetNode(from, to) == 0) from = aho.GetFail(from);
    from = aho.GetNode(from, to);
    int back = from;
    while (back > 0) {
      if (aho.IsEnd(back)) aho.Update(back);
      back = aho.GetFailOut(back);
    }
    ans = aho.GetCnt(pos[i]);
    cout << ans << '\n';
  }
  return 0;
}
