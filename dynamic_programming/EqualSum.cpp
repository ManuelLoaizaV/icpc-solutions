//https://open.kattis.com/problems/equalsumseasy
#include <iostream>
#include <map>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 20;
int a[N];

void Print(int mask, int n) {
  for (int i = 0; i < n; i++) {
    if (mask & 1) cout << a[i] << " ";
    mask >>= 1;
  }
  cout << '\n';
}

void Solve(void) {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  map<int, vector<int>> mp;
  int L = 1 << n;
  for (int mask = 1; mask < L; mask++) {
    int copy = mask;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      if (copy & 1) sum += a[i];
      copy >>= 1;
    }
    mp[sum].push_back(mask);
    if (mp[sum].size() == 2) {
      Print(mp[sum][0], n);
      Print(mp[sum][1], n);
      return;
    }
  }
  cout << "Impossible" << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case #" << i << ":\n";
    Solve();
  }
  return 0;
}
