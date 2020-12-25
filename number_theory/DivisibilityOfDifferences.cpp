#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

int main(void) {
  FAST_IO;
  int n, k, m;
  cin >> n >> k >> m;
  vector<int> cnt(m, 0);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    cnt[a[i] % m]++;
  }
  int id = -1;
  for (int i = 0; i < m; i++) {
    if (cnt[i] >= k) {
      id = i;
      break;
    }
  }
  if (id == -1) {
    cout << "No" << '\n';
  } else {
    cout << "Yes" << '\n';
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] % m == id) {
        cout << a[i] << " ";
        ans++;
      }
      if (ans == k) {
        cout << '\n';
        break;
      }
    }
  }
  return 0;
}
