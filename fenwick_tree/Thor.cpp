//https://codeforces.com/problemset/problem/704/A
#include <iostream>
#include <queue>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 3e5;

struct FenwickTree {
  int tree[N + 1];

  void Update(int i, int delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  int Query(int i) {
    int ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft;

int main(void) {
  FAST_IO;
  int n, q;
  cin >> n >> q;
  vector<int> cnt(n + 1, 0);
  vector<int> read(n + 1, 0);
  vector<int> cur(n + 1, 0);
  queue<int> ntf;
  int mx = 0;
  while (q--) {
    int t, x;
    cin >> t >> x;
    if (t == 1) {
      cnt[x]++;
      ntf.push(x);
      ft.Update(x, 1);
    }
    if (t == 2) {
      ft.Update(x, read[x] - cnt[x]);
      read[x] = cnt[x];
    }
    if (t == 3) {
      if (x > mx) {
        int delta = x - mx;
        mx = x;
        while (delta--) {
          int fst = ntf.front();
          ntf.pop();
          if (cur[fst] == read[fst]) {
            read[fst]++;
            ft.Update(fst, -1);
          }
          cur[fst]++;
        }
      }
    }
    cout << ft.Query(n) << '\n';
  }
  return 0;
}
