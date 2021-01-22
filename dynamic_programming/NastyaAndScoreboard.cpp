//https://codeforces.com/problemset/problem/1340/B
#include <bitset>
#include <iostream>
using namespace std;

const int N = 2e3;

bitset<7> digits[N];
bitset<7> numbers[10];
int n;
bool is_done[N + 1][N + 1], dp[N + 1][N + 1];

// DP(i, r): posibilidad de formar una cadena valida con los digitos
// [i .. n - 1] cuando me faltan encender k sticks
bool DP(int i, int r) {
  if (i == n) return (r == 0);
  if (is_done[i][r]) return dp[i][r];
  dp[i][r] = false;
  for (int nxt = 9; nxt >= 0; nxt--) {
    bitset<7> fusion = digits[i] | numbers[nxt];
    if (fusion == numbers[nxt]) {
      int used = numbers[nxt].count() - digits[i].count();
      if (used <= r) {
        dp[i][r] = DP(i + 1, r - used);
        if (dp[i][r]) break;
      }
    }
  }
  is_done[i][r] = true;
  return dp[i][r];
}

void Reconstruct(int i, int r) {
  if (i == n) return;
  for (int nxt = 9; nxt >= 0; nxt--) {
    bitset<7> fusion = digits[i] | numbers[nxt];
    if (fusion == numbers[nxt]) {
      int used = numbers[nxt].count() - digits[i].count();
      if (used <= r) {
        if (DP(i + 1, r - used)) {
          cout << nxt;
          Reconstruct(i + 1, r - used);
          return;
        }
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  // Primero construyo los numeros
  numbers[0] = bitset<7>(string("1110111"));
  numbers[1] = bitset<7>(string("0010010"));
  numbers[2] = bitset<7>(string("1011101"));
  numbers[3] = bitset<7>(string("1011011"));
  numbers[4] = bitset<7>(string("0111010"));
  numbers[5] = bitset<7>(string("1101011"));
  numbers[6] = bitset<7>(string("1101111"));
  numbers[7] = bitset<7>(string("1010010"));
  numbers[8] = bitset<7>(string("1111111"));
  numbers[9] = bitset<7>(string("1111011"));
  // Luego resuelvo el problema
  int k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> digits[i];
  if (DP(0, k)) {
    Reconstruct(0, k);
    cout << '\n';
  } else {
    cout << -1 << '\n';
  }
  return 0;
}
