#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 3e5;
const Long BASE[2] = {29LL, 31LL};
const Long MOD = 1e9 + 7;
Long pot[N + 1][2];

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

void Precalculate(void) {
  for (int j = 0; j < 2; j++) {
    pot[0][j] = 1LL;
    for (int i = 1; i <= N; i++)
      pot[i][j] = Mul(pot[i - 1][j], BASE[j]);
  }
}

Pair GetHash(const string& s) {
  int n = s.size();
  Long ans[] = {0LL, 0LL};
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < n; i++)
      ans[j] = Add(Mul(ans[j], BASE[j]), s[i] - 'a' + 1LL);
  }
  return {ans[0], ans[1]};
}

vector<Pair> pref;
void Build(const string& s) {
  int n = s.size();
  pref = vector<Pair>(n, {0LL, 0LL});
  pref[0].first = pref[0].second = s[0] - 'a' + 1LL;
  for (int i = 1; i < n; i++) {
    pref[i].first = Add(Mul(pref[i - 1].first, BASE[0]), s[i] - 'a' + 1LL);
    pref[i].second = Add(Mul(pref[i - 1].second, BASE[1]), s[i] - 'a' + 1LL);
  }
}

Pair Query(int l, int r) {
  if (l == 0) return pref[r];
  Pair ans;
  ans.first = Sub(pref[r].first, Mul(pref[l - 1].first, pot[r - l + 1][0]));
  ans.second = Sub(pref[r].second, Mul(pref[l - 1].second, pot[r - l + 1][1]));
  return ans;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Precalculate();
  int tt;
  cin >> tt;
  map<int, set<Pair>> words;
  while (tt--) {
    int t;
    cin >> t;
    if (t == 1) {
      string s;
      cin >> s;
      int n = (int) s.size();
      if (words.count(n) > 0) {
        words[n].insert(GetHash(s));
      } else {
        words[n] = {GetHash(s)};
      }
    } else if (t == 2) {
      string s;
      cin >> s;
      int n = (int) s.size();
      words[n].erase(GetHash(s));
      if (words[n].size() == 0) words.erase(n);
    } else {
      string s;
      cin >> s;
      Build(s);
      int n = s.size();
      Long ans = 0;
      for (auto it = words.begin(); it != words.end(); it++) {
        int len = it->first;
        if (len > n) break;
        for (int i = 0; i < n - len + 1; i++) {
          if ((it->second).count(Query(i, i + len - 1)) > 0) ans++;
        }
      }
      cout << ans << endl;
    }
  }
  return 0;
}
