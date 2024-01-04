#include <bits/stdc++.h>
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  set<char> u;
  for (char c : s) u.insert(c);
  if (u.size() & 1) {
    cout << "IGNORE HIM!" << '\n';
  } else {
    cout << "CHAT WITH HER!" << '\n';
  }
  return 0;
}
