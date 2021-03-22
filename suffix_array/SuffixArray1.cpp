//https://codeforces.com/edu/course/2/lesson/2/1/practice/contest/269100/problem/A
#include <bits/stdc++.h>
using namespace std;

int main(void) {
  string s;
  cin >> s;
  s += '$';
  int n = (int) s.size();
  vector<int> p(n), c(n);
  {
    // k = 0
    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    int nxt = 0;
    for (int i = 0; i < n; i++) {
      if (i > 0 && a[i].first != a[i - 1].first) nxt++;
      c[p[i]] = nxt;
    }
  }
  int k = 0;
  while ((1 << k) < n) {
    // k -> k + 1
    vector<pair<pair<int, int>, int>> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    int nxt = 0;
    for (int i = 0; i < n; i++) {
      if (i > 0 && a[i].first != a[i - 1].first) nxt++;
      c[p[i]] = nxt;
    }
    k++;
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << p[i];
  }
  cout << '\n';
}
