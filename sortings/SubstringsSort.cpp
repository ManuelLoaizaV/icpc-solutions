//https://codeforces.com/problemset/problem/988/B?mobile=false
#include <bits/stdc++.h>
using namespace std;

bool Increasing(const string& s1, const string& s2) {
  return s1.size() < s2.size();
}

bool IsSubstring(const string& s1, const string& s2) {
  int n1 = s1.size();
  int n2 = s2.size();
  for (int i = 0; i < n2 - n1 + 1; i++) {
    bool ok = true;
    for (int j = 0; j < n1; j++) {
      if (s1[j] == s2[i + j]) continue;
      ok = false;
      break;
    }
    if (ok) return true;
  }
  return false;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<string> s(n);
  for (int i = 0; i < n; i++) cin >> s[i];
  sort(s.begin(), s.end(), Increasing);
  for (int i = 0; i < n - 1; i++) {
    if (IsSubstring(s[i], s[i + 1])) continue;
    cout << "NO" << '\n';
    return 0;
  }
  cout << "YES" << '\n';
  for (int i = 0; i < n; i++) cout << s[i] << '\n';
  return 0;
}
