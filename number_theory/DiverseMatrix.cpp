#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  if (n == 1 && m == 1) {
    cout << 0 << '\n';
  } else {
    if (n == 1) {
      for (int i = 0; i < m; i++) {
        cout << i + 2 << " ";
      }
      cout << '\n';
      return 0;
    }
    if (m == 1) {
      for (int i = 0; i < n; i++) {
        cout << i + 2 << '\n';
      }
      return 0;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int a = (n + 1 + j) * (i + 1);
        cout << a << " ";
      }
      cout << '\n';
    }
  }
  return 0;
}
