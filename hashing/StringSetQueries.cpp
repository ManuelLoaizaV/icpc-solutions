#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 3e5;
const Long BASE[] = {29LL, 31LL};
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

void CalculateHash(const string& s) {
  int n = s.size();
  pref.resize(n, {0LL, 0LL});
  pref[0].first = pref[0].second = s[0] - 'a' + 1LL;
  for (int i = 1; i < n; i++) {
    pref[i].first = Add(Mul(pref[i - 1].first, BASE[0]), s[i] - 'a' + 1LL);
    pref[i].second = Add(Mul(pref[i - 1].second, BASE[1]), s[i] - 'a' + 1LL);
  }
}

Pair GetHash(int l, int r) {
  if (l == 0) return pref[r];
  Pair ans;
  ans.first = Sub(pref[r].first, Mul(pref[l - 1].first, pot[r - l + 1][0]));
  ans.second = Sub(pref[r].second, Mul(pref[l - 1].second, pot[r - l + 1][1]));
  return ans;
}

int main(void) {
  FAST_IO;
  Precalculate();
  int queries;
  cin >> queries;
  map<int, set<Pair>> exists;

  while (queries--) {
    int type;
    cin >> type;
    string s;
    cin >> s;
    if (type == 1) {
      int len = s.size();
      Pair current = GetHash(s);
      if (exists.count(len)) {
        exists[len].insert(current);
      } else {
        exists[len] = {current};
      }
    }
    if (type == 2) {
      int len = s.size();
      Pair current = GetHash(s);
      auto it = exists.find(len);
      if ((it->second).size() == 1) {
        exists.erase(it);
      } else {
        (it->second).erase(current);
      }
    }
    if (type == 3) {
      CalculateHash(s);
      int n = s.size();
      Long cnt = 0;
      for (auto it = exists.begin(); it != exists.end(); it++) {
        int len = it->first;
        if (len > n) break;
        for (int i = 0; i < n - len + 1; i++) {
          Pair current = GetHash(i, i + len - 1);
          if ((it->second).count(current)) cnt++;
        } 
      }
      cout << cnt << endl;
    }
  }
  return 0;
}
