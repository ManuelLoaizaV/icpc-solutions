#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  if (n & 1) {
    cout << 9 << " " << n - 9 << '\n';
  } else {
    cout << 4 << " " << n - 4 << '\n';
  }
  return 0;
}
