//https://codeforces.com/problemset/problem/1181/C
#include <iostream>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 1e3;
const int ALPHABET = 26;

string s[N];
int chr[N + 1][N + 1], cnt[N + 1][N + 1][ALPHABET];

Long GetArea(int i, int j, int x, int y) {
  return (Long) (x - i + 1) * (y - j + 1);
}

Long GetCount(int c, int i, int j, int x, int y) {
  return cnt[x][y][c] - cnt[x][j - 1][c] - cnt[i - 1][y][c] + cnt[i - 1][j - 1][c];
}

bool IsValid(int c, int i, int j, int x, int y) {
  return GetArea(i, j, x, y) == GetCount(c, i, j, x, y);
}

Pair GetRectangle(int i, int j, int n, int m) {
  int c = chr[i][j];
  Long h, w;
  if (IsValid(c, i, j, n, j)) {
    h = n - i + 1;
  } else {
    int l, r;
    l = i;
    r = n;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (IsValid(c, i, j, mid, j)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    h = l - i + 1;
  }
  if (IsValid(c, i, j, i + h - 1, m)) {
    w = m - j + 1;
  } else {
    int l, r;
    l = j;
    r = m;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (IsValid(c, i, j, i + h - 1, mid)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    w = l - j + 1;
  }
  return {h, w};
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> s[i];
  // Cambio los valores
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      chr[i + 1][j + 1] = s[i][j] - 'a';
    }
  }
  // Hallo las cantidades
  for (int c = 0; c < ALPHABET; c++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cnt[i][j][c] = cnt[i - 1][j][c] + cnt[i][j - 1][c] - cnt[i - 1][j - 1][c];
        if (chr[i][j] == c) cnt[i][j][c]++;
      }
    }
  }
  Long ans = 0LL;
  for (Long i = 1; i <= n - 2; i++) {
    for (Long j = 1; j <= m; j++) {
      Pair len_1 = GetRectangle(i, j, n, m);
      // Si tengo para analizar hacia abajo
      if (i + len_1.first > n) continue;
      Pair len_2 = GetRectangle(i + len_1.first, j, n, m);
      // Si es distinto
      if (len_1.first != len_2.first) continue;
      // Si tengo para analizar hacia abajo
      if (i + len_1.first + len_2.first > n) continue;
      Pair len_3 = GetRectangle(i + len_1.first + len_2.first, j, min(n, i + len_1.first + 2 * len_2.first - 1), m);
      if (len_2.first > len_3.first) continue;
      Long width = min(len_1.second, min(len_2.second, len_3.second));
      ans += width;
    }
  }
  cout << ans << '\n';
  return 0;
}
