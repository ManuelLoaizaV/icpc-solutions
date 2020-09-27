#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(0)
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;

int main() {
  FAST_IO;
  Long n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
 
  deque<Long> l, r;
  l.push_back(0LL);
  for (int i = 0; i < n; i++) {
    Long add = l[l.size() - 1] ^ a[i];
    l.push_back(add);
  }
  l.push_back(l[l.size() - 1]);
  r.push_front(0LL);
  for (int i = n - 1; i >= 0; i--) {
    Long add = r[0] ^ a[i];
    r.push_front(add);
  }
  r.push_front(r[0]);
  
  map<Long, vector<Long>> ind_r;
  for (Long i = 0; i <= n + 1; i++) {
    ind_r[r[i]].push_back(i);
  }

  Long ans = 0LL;
  for (Long i = 0; i < n; i++) {
    //debug(i);
    //debug(l[i]);
    Long cnt = 0LL;
    if (ind_r.count(l[i])) {
      Long sz = ind_r[l[i]].size();
      Long pos = lower_bound(ind_r[l[i]].begin(), ind_r[l[i]].end(), i + 2) - ind_r[l[i]].begin();
      cnt = sz - pos;
      //debug(sz);
      //debug(pos);
      //debug(cnt);
    }
    ans += cnt;
  }
  cout << ans << endl;
  return 0;
}
