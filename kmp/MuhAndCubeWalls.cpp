// Gracias, Osman
#include <iostream>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int INF = 1e9;

int KMP(vector<int>& p, vector<int>& t) {
  int n = p.size();
  int m = t.size();
  vector<int> pi(n + 1 + m);
  vector<int> s;
  for (int x : p) s.push_back(x);
  s.push_back(-INF);
  for (int x : t) s.push_back(x);
  int len = s.size();

  int ans = 0;
  for (int i = 1; i < len; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
    if (pi[i] == n) ans++;
  }
  return ans;
}

int main(void) {
  FAST_IO;
  int n, w, aux;
  cin >> n >> w;
  vector<int> a;
  for (int i = 0; i < n; i++) {
    cin >> aux;
    a.push_back(aux);
  }
  vector<int> b;
  for (int i = 0; i < w; i++) {
    cin >> aux;
    b.push_back(aux);
  }

  if (w == 1) {
    cout << n << '\n';
  } else {
    vector<int> t;
    for (int i = 1; i < a.size(); i++) t.push_back(a[i] - a[i - 1]);
    vector<int> p;
    for (int i = 1; i < b.size(); i++) p.push_back(b[i] - b[i - 1]);
    cout << KMP(p, t) << '\n';
  }
  return 0;
}
