// https://open.kattis.com/problems/natrij
#include <bits/stdc++.h>
using namespace std;

int GetVal(char c) {
  return c - '0';
}

int GetNum(string s) {
  return 10 * GetVal(s[0]) + GetVal(s[1]);
}

char GetChar(int d) {
  return char('0' + d);
}

string GetStr(int t) {
  string ans = "";
  ans += GetChar(t / 10);
  t %= 10;
  ans += GetChar(t);
  return ans;
}

string GetTime(int t) {
  string ans = "";
  ans += GetStr(t / 3600);
  t %= 3600;
  ans += ":";
  ans += GetStr(t / 60);
  t %= 60;
  ans += ":";
  ans += GetStr(t);
  return ans;
}

int GetSeconds(string s) {
  int t = 0;
  t += 3600 * GetNum(s.substr(0, 2));
  t += 60 * GetNum(s.substr(3, 2));
  t += GetNum(s.substr(6, 2));
  return t;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string l, r;
  cin >> l >> r;
  int t = GetSeconds(r) - GetSeconds(l);
  if (t <= 0) t += 24 * 3600;
  cout << GetTime(t) << '\n';
  return 0;
}
