#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int ALPHABET = 26;
const int INF = 1e9;
const int N = 2e6 + 5;

struct Trie {
  int trie[N][ALPHABET];
  int mn[N];
  int fail[N];
  //int fail_out[N];
  //int end_word[N];
  int nodes;

  Trie() {
    for (int i = 0; i < N; i++) {
      mn[i] = INF;
      fail[i] = 0;
      //fail_out[i] = 0;
      //end_word[i] = 0;
      for (int j = 0; j < ALPHABET; j++) {
        trie[i][j] = 0;
      }
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
          // Si existe, lo agrego
          q.push(to);
          // Los hijos inmediatos de la raiz ya estan calculados
          if (from > 0) {
            fail[to] = fail[from];
            while (fail[to] > 0 && trie[fail[to]][chr] == 0) fail[to] = fail[fail[to]];
            fail[to] = trie[fail[to]][chr];
            mn[to] = min(mn[to], mn[fail[to]]);
            //fail_out[to] = end_word[fail[to]] ? fail[to] : fail_out[fail[to]];
          }
        }
      }
    }
  }

  void Add(string& s, int timer) {
    int from = 0;
    for (char chr : s) {
      int to = chr - 'a';
      if (trie[from][to] == 0) trie[from][to] = nodes++;
      from = trie[from][to];
    }
    mn[from] = min(mn[from], timer);
    //end_word[from] = id;
  }

  int GetFail(int ind) {
    return fail[ind];
  }

  int GetMin(int ind) {
    return mn[ind];
  }

  int GetNode(int from, int to) {
    return trie[from][to];
  }
} trie;

int main(void) {
  FAST_IO;
  int queries;
  cin >> queries;

  int type;
  string task;
  vector<pair<string, int>> todo;

  for (int i = 0; i < queries; i++) {
    cin >> type >> task;
    if (type == 0) {
      trie.Add(task, i);
    } else {
      todo.push_back({task, i});
    }
  }
  trie.Build();

  int len = todo.size();
  for (int i = 0; i < len; i++) {
    int minimum = INF;
    int from = 0;
    for (char chr : todo[i].first) {
      int to = chr - 'a';
      while (from > 0 && trie.GetNode(from, to) == 0) from = trie.GetFail(from);
      from = trie.GetNode(from, to);
      minimum = min(minimum, trie.GetMin(from));
    }
    if (minimum < todo[i].second) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
  return 0;
}
