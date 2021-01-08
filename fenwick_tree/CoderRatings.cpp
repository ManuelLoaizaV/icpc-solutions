//https://www.spoj.com/problems/RATING/en/
#include <algorithm>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 1e5;

struct Coder {
  int a, h, id;
  bool operator < (const Coder& other) const {
    if (a == other.a && h == other.h) return id < other.id;
    if (a == other.a) return h < other.h;
    return a < other.a;
  }
};

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
  int n;
  cin >> n;
  vector<Coder> coders(n);
  for (int i = 0; i < n; i++) {
    cin >> coders[i].a >> coders[i].h;
    coders[i].id = i;
  }

  sort(coders.begin(), coders.end());
  vector<int> ans(n, 0);
  int cur = 0;
  for (int i = 0; i < n; i++) {
    int aux = ft.Query(coders[i].h);
    if (i > 0 && coders[i - 1].a == coders[i].a && coders[i - 1].h == coders[i].h) {
      aux -= cur;
      cur++;
    } else {
      cur = 1;
    }
    ans[coders[i].id] = aux;
    ft.Update(coders[i].h, 1);
  }
  for (int i = 0; i < n; i++) cout << ans[i] << '\n';
  return 0;
}
