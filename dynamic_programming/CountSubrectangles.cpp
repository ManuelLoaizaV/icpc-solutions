#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 4e4;

vector<Long> Compress(const vector<Long>& v) {
  vector<Long> ans;
  int n = v.size();
  for (int i = 0; i < n; i++) {
    int acc = 0;
    if (v[i] == 1) {
      acc = 0;
      int j = i;
      while (j < n && v[j] == 1) {
        acc++;
        j++;
      }
      ans.push_back(acc);
      i = j - 1;
    }
  }
  return ans;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long n, m, k;
  cin >> n >> m >> k;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<Long> b(m);
  for (int i = 0; i < m; i++) cin >> b[i];
  // Compresion de adyacentes en a y en b
  vector<Long> comp_a = Compress(a);
  vector<Long> comp_b = Compress(b);
  // Guardo divisores
  vector<Long> divisors;
  for (Long i = 1; i * i <= k; i++) {
    if (k % i == 0) {
      divisors.push_back(i);
      Long j = k / i;
      if (i != j) divisors.push_back(j);
    }
  }
  // Cuento para cada bloque
  map<Long, Long> acc_a;
  map<Long, Long> acc_b;
  for (Long d : divisors) {
    for (Long len : comp_a) {
      if (len >= d) acc_a[d] += (len - d + 1);
    }
    for (Long len : comp_b) {
      if (len >= d) acc_b[d] += (len - d + 1);
    }
  }
  // Acumulo
  Long ans = 0;
  for (Long d : divisors) {
    ans += acc_a[d] * acc_b[k / d];
  }
  cout << ans << '\n';
  return 0;
}
