// https://codeforces.com/contest/1900/problem/D
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const char ENDL = '\n';

const int N = 1e5;
int primes[N + 1];

void Sieve(void) {
  for (int i = 0; i <= N; i++) primes[i] = i;
  for (int i = 2; i <= N; i++) {
    if (primes[i] != i) continue;
    for (Long j = 1LL * i * i; j <= N; j += i) primes[j] = i;
  }
}

vector<pair<int, int>> Factorize(int n) {
  vector<pair<int, int>> factors;
  while (n > 1) {
    int p = primes[n];
    int e = 0;
    while (n % p == 0) {
      n /= p;
      e++;
    }
    factors.push_back({p, e});
  }
  return factors;
}

void GenerateDivisors(int i, int product, const vector<pair<int, int>>& factors, vector<int>& divisors) {
  if (i == factors.size()) {
    divisors.push_back(product);
    return;
  }
  for (int e = 0; e <= factors[i].second; e++) {
    GenerateDivisors(i + 1, product, factors, divisors);
    product *= factors[i].first;
  }
}

vector<int> GetDivisors(int n) {
  vector<pair<int, int>> factors = Factorize(n);
  vector<int> divisors;
  GenerateDivisors(0, 1, factors, divisors);
  return divisors;
}

void Solve(void) {
  Long n;
  cin >> n;

  vector<Long> a(n);
  Long mx = 0LL;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    mx = max(mx, a[i]);
  }

  sort(a.begin(), a.end());

  vector<vector<Long>> positions(mx + 1);

  for (Long i = 0; i < n; i++) {
    vector<int> divisors = GetDivisors(a[i]);
    for (int d : divisors) {
      positions[d].push_back(i);
    }
  }

  Long ans = 0LL;
  vector<Long> cnt(mx + 1, 0);
  for (Long g = mx; g >= 1; g--) {
    // Number of triplets with f = kg, k >= 1
    int n_positions = (int)positions[g].size();
    for (Long i = 0; i < n_positions; i++) {
      cnt[g] += i * (n - 1 - positions[g][i]);
    }
    // Subtract number of triplets that are f = kg, k >= 2
    for (Long kg = 2LL * g; kg <= mx; kg += g) {
      cnt[g] -= cnt[kg];
    }
    ans += g * cnt[g];
  }

  cout << ans << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve();
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}