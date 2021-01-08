//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3238
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
const int N = 2e5;

struct FenwickTree {
  Long tree[N + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0LL;
  }

  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  Long Query(int i) {
    Long ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft;

void Solve(int n) {
  ft.Build(n);
  vector<Long> a(n + 1);
  a[0] = 0;
  for (int i = 1; i <= n; i++) cin >> a[i];
  vector<Long> acc(n + 1);
  acc[0] = 0LL;
  for (int i = 1; i <= n; i++) acc[i] = acc[i - 1] + a[i];
  string action;
  Long x, y;
  while (true) {
    cin >> action;
    if (action[0] == 'E') break;
    cin >> x >> y;
    if (action[0] == 'S') {
      Long delta = y - a[x];
      ft.Update(x, delta);
      a[x] = y;
    } else {
      Long r = acc[y] + ft.Query(y);
      Long l = acc[x - 1] + ft.Query(x - 1);
      Long sum = r - l;
      cout << sum << '\n';
    }
  }
}

int main(void) {
  FAST_IO;
  int n;
  int t = 0;
  while (cin >> n) {
    if (n == 0) break;
    if (t > 0) cout << '\n';
    t++;
    cout << "Case " << t << ":" << '\n';
    Solve(n);
  }
  return 0;
}
