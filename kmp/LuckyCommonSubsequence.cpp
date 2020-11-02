#include <iostream>
#include <string>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int ALPHABET = 26;
const int N = 1e2;
const int INF = 1e3;

string s1, s2, virus;
int pi[N], aut[N + 1][ALPHABET];

void CalculatePi(string& s) {
  int n = s.size();
  pi[0] = 0;
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
}

void CalculateAutomata(string& s) {
  int n = s.size();
  for (int i = 0; i < ALPHABET; i++) aut[0][i] = 0;
  aut[0][s[0] - 'A'] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < ALPHABET; j++) {
      if (i < n && j == (s[i] - 'A')) {
        aut[i][j] = i + 1;
      } else {
        aut[i][j] = aut[pi[i - 1]][j];
      }
    }
  }
}

int dp[N][N][N];
bool is_done[N][N][N];

/*
 * DP(i, j, k) : longitud de la maxima subsecuencia que puedo obtener con los
 * caracteres de s1 en el rango [i, ..., |s1| - 1], los caracteres de s2 en el
 * rango [j, ..., |s2| - 1] y k caracteres de prefijo mathcheados de virus.
 */

int DP(int i, int j, int k) {
  if (k == virus.size()) return -INF;
  if (i == s1.size() || j == s2.size()) return 0;
  if (is_done[i][j][k]) return dp[i][j][k];
  dp[i][j][k] = 0;
  dp[i][j][k] = max(dp[i][j][k], DP(i + 1, j, k));
  dp[i][j][k] = max(dp[i][j][k], DP(i, j + 1, k));
  if (s1[i] == s2[j]) dp[i][j][k] = max(dp[i][j][k], 1 + DP(i + 1, j + 1, aut[k][s1[i] - 'A']));
  is_done[i][j][k] = true;
  return dp[i][j][k];
}

string answer = "";

void Reconstruct(int i, int j, int k) {
  int current = DP(i, j, k);
  if (current == 0) return;
  char chr = s1[i];
  if ((s1[i] == s2[j]) && (current == 1 + DP(i + 1, j + 1, aut[k][chr - 'A']))) {
    answer += chr;
    Reconstruct(i + 1, j + 1, aut[k][chr - 'A']);
    return;
  }
  if (current == DP(i + 1, j, k)) {
    Reconstruct(i + 1, j, k);
  } else {
    Reconstruct(i, j + 1, k);
  }
}


int main(void) {
  FAST_IO;
  cin >> s1 >> s2 >> virus;
  CalculatePi(virus);
  CalculateAutomata(virus);
  if (DP(0, 0, 0) == 0) {
    cout << 0 << '\n';
  } else {
    Reconstruct(0, 0, 0);
    cout << answer << '\n';
  }
  return 0;
}
