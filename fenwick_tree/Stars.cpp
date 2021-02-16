//https://github.com/Sky-Nik/Codeforces/blob/main/FenwickTree/statements.pdf
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 128;

struct FenwickTree {
  Long tree[N + 1][N + 1][N + 1];
  void Update(int i, int j, int k, Long delta) {
    while (i <= N) {
      int y = j;
      while (y <= N) {
        int z = k;
        while (z <= N) {
          tree[i][y][z] += delta;
          z += (z & -z);
        }
        y += (y & -y);
      }
      i += (i & -i);
    }
  }
  Long Query(int i, int j, int k) {
    Long ans = 0;
    while (i > 0) {
      int y = j;
      while (y > 0) {
        int z = k;
        while (z > 0) {
          ans += tree[i][y][z];
          z -= (z & -z);
        }
        y -= (y & -y);
      }
      i -= (i & -i);
    }
    return ans;
  }
  Long Query(int x1, int y1, int z1, int x2, int y2, int z2) {
    return Query(x2, y2, z2)
      - Query(x1 - 1, y2, z2) - Query(x2, y1 - 1, z2) - Query(x2, y2, z1 - 1)
      + Query(x1 - 1, y1 - 1, z2) + Query(x1 - 1, y2, z1 - 1)
      + Query(x2, y1 - 1, z1 - 1) - Query(x1 - 1, y1 - 1, z1 - 1);
  }
} ft;

// Principio de inclusion exclusion:
//
// A U B U C U D =
// A + B + C + D
// - A ^ B - A ^ C - A ^ D
// - B ^ C - B ^ D
// - C ^ D
// + A ^ B ^ C + A ^ B ^ D
// + B ^ C ^ D
// - A ^ B ^ C ^ D
//
// A U B U C U D =
// A + B + C + D
// - A ^ B - A ^ C
// - B ^ C
// + A ^ B ^ C
//
// Despejando:
// D =
// A U B U C U D
// - A - B - C
// + A ^ B + A ^ C
// + B ^ C
// - A ^ B ^ C

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen("stars.in", "r", stdin);
  freopen("stars.out", "w", stdout);
  int n;
  cin >> n;
  int t;
  while (cin >> t) {
    if (t == 3) break;
    if (t == 1) {
      int x, y, z;
      Long k;
      cin >> x >> y >> z >> k;
      ft.Update(x + 1, y + 1, z + 1, k);
    } else {
      int x1, y1, z1, x2, y2, z2;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      cout << ft.Query(x1 + 1, y1 + 1, z1 + 1, x2 + 1, y2 + 1, z2 + 1) << '\n';
    }
  }
  return 0;
}
