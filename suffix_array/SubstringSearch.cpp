#include <bits/stdc++.h>
using namespace std;

int Check(int i, const string& s, const string& t, const vector<int>& p) {
  int len = min((int) s.size(), (int) t.size() - 1 - p[i]);
  return s.compare(t.substr(p[i], len));
}

void CountingSort(vector<int>& p, vector<int>& c) {
  int n = (int) p.size();
  vector<int> cnt(n, 0);
  for (auto x : c) cnt[x]++;
  vector<int> new_p(n);
  vector<int> pos(n);
  pos[0] = 0;
  for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
  for (auto x : p) {
    int i = c[x];
    new_p[pos[i]] = x;
    pos[i]++;
  }
  p = new_p;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
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

  {
    int k = 0;
    while ((1 << k) < n) {
      // k -> k + 1
      for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
      CountingSort(p, c);
      vector<int> c_new(n);
      int nxt = 0;
      c_new[p[0]] = 0;
      for (int i = 1; i < n; i++) {
        pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
        pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
        if (prev != now) nxt++;
        c_new[p[i]] = nxt;
      }
      c = c_new;
      k++;
    }
  }

  int q;
  cin >> q;
  while (q--) {
    string t;
    cin >> t;
    int l = 1;
    int r = n - 1;
    bool found = false;
    while (l <= r) {
      int m = (l + r) / 2;
      int cur = Check(m, t, s, p);
      if (cur == 0) {
        found = true;
        break;
      }
      if (cur < 0) {
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
    cout << ((found) ? "Yes" : "No") << '\n';
  }
  return 0;
}
