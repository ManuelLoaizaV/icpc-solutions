#include <iostream>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef unsigned int Long;

const int N = 50;
const int ALPHABET = 26;

struct Matrix {
  vector<vector<Long>> m;

  Matrix(int n, bool is_identity) {
    m.resize(n, vector<Long> (n, 0));
    if (is_identity) {
      for (int i = 0; i < n; i++) m[i][i] = 1;
    }
  }

  int Size(void) {
    return m.size();
  }
};

Matrix operator * (Matrix& a, Matrix& b) {
  int n = a.Size();
  Matrix ans(n, false);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        ans.m[i][j] += (a.m[i][k] * b.m[k][j]);
      }
    }
  }
  return ans;
}

Matrix FastPow(Matrix base, Long exponent) {
  Matrix ans(base.Size(), true);
  while (exponent > 0) {
    if (exponent & 1) ans = ans * base;
    base = base * base;
    exponent >>= 1;
  }
  return ans;
}

vector<Long> CalculatePi(const string& p) {
  int n = p.size();
  vector<Long> pi(n);
  pi[0] = 0;
  for (int i = 1, j = 0; i < n; i++) {
    if (p[i] == p[j]) {
      j++;
    } else {
      while (j > 0 && p[i] != p[j]) j = pi[j - 1];
      if (p[i] == p[j]) j++;
    }
    pi[i] = j;
  }
  return pi;
}

void Solve(int iteration) {
  Long n;
  cin >> n;
  string valid, ban;
  cin >> valid >> ban;

  int len = max((int)ban.size() + 1, ALPHABET);
  
  vector<Long> pi = CalculatePi(ban);

  vector<bool> exists(ALPHABET, false);
  for (char chr : valid) exists[chr - 'a'] = true;

  // dp[i][j] = numero de maneras de llegar del nodo i al nodo j
  // del kmp automata
  Matrix dp(len, false);

  // Construyo el automata
  vector<vector<int>> aut(ban.size() + 1, vector<int> (ALPHABET, 0));
  for (int i = 0; i < ALPHABET; i++) aut[0][i] = 0;
  aut[0][ban[0] - 'a'] = 1;
  for (int i = 1; i <= ban.size(); i++) {
    for (int j = 0; j < ALPHABET; j++) {
      if (i < ban.size() && j == ban[i] - 'a') {
        aut[i][j] = i + 1;
      } else {
        aut[i][j] = aut[pi[i - 1]][j];
      }
    }
  }

  // Construyo el dp como si fuese un conteo de rutas en un grafo
  for (int to = 0; to < ALPHABET; to++) {
    if (exists[to]) {
      int to_node = aut[0][to];
      if (to_node == 0 || ban.size() > 1) {
        dp.m[0][to_node]++;
      }
    }
  }
  for (int i = 1; i <= ban.size(); i++) {
    int from = ban[i - 1] - 'a';
    for (int to = 0; to < ALPHABET; to++) {
      // Si existen los nodos, entonces cuento la arista
      if (exists[from] && exists[to]) {
        int to_node = aut[i][to];
        if (to_node < ban.size()) dp.m[i][to_node]++;
      }
    }
  }

  Matrix ans = FastPow(dp, n);
  Long cnt = 0;
  for (int i = 0; i < len; i++) {
    cnt += ans.m[0][i];
  }
  cout << "Case " << iteration << ": " << cnt << '\n';
}

int main(void) {
  FAST_IO;
  Long t;
  cin >> t;
  for (int i = 1; i <= t; i++) Solve(i);
  return 0;
}
