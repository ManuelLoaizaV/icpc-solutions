// https://codeforces.com/contest/1665/problem/D
#include <bits/stdc++.h>
using namespace std;
typedef long long Long;
typedef pair<Long, Long> Pair;
typedef tuple<Long, Long, Long> Trio;

Long GCD(Long a, Long b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}

// Find x, y such that ax + by = (a, b)
Pair ExtendedEuclidean(Long a, Long b) {
  if (b == 0) return {1, 0};
  Pair p = ExtendedEuclidean(b, a % b);
  Long x = p.second;
  Long y = p.first - (a / b) * x;
  if (a * x + b * y == -GCD(a, b)) {
    x = -x;
    y = -y;
  }
  return {x, y};
}

// Find all solutions to ax + by = c
// where (a, b) | c
pair<Pair, Pair> LinearDiophantine(Long a, Long b, Long c) {
  Long g = GCD(a, b);
  a /= g;
  b /= g;
  c /= g;
  Pair p = ExtendedEuclidean(a, b);
  p.first *= c;
  p.second *= c;
  // {x, y} = {p.first - t * b, p.second + t * a}, t integer
  return {p, {-b, a}};
}

Long Mod(__int128 a, Long m) {
  return ((a % m) + m) % m;
}

// Find x such that ax = 1 (mod m)
Long Invert(Long a, Long m) {
  assert(GCD(a, m) == 1);
  Long x = LinearDiophantine(a, m, 1LL).first.first;
  return Mod(x, m);
}

// ax = b (mod m)
Pair Solve(Trio equation) {
  Long a = get<0>(equation);
  Long b = get<1>(equation);
  Long m = get<2>(equation);
  Long g = GCD(a, m);
  if (g == 1) return {Mod((__int128)b * Invert(a, m), m), m};
  if (b % g == 0) return Solve(make_tuple(a / g, b / g, m / g));
  return {-1LL, -1LL};
}

// Find x such that a_i * x = b_i (mod m_i)
// Return {x, lcm(m_i)}
Pair CRT(vector<Trio> equations) {
  Long b = 0LL, lcm = 1LL, y, m;
  for (auto equation : equations) {
    tie(y, m) = Solve(equation);  // a_i * y = b_i (mod m)
    if ((b - y) % GCD(lcm, m) != 0) return {-1LL, -1LL};
    if (lcm == m) continue;
    Long k = LinearDiophantine(m, -lcm, b - y).first.second;
    Long new_lcm = lcm * (m / GCD(lcm, m));
    b = Mod((__int128)lcm * k + b, new_lcm);
    lcm = new_lcm;
  }
  return Solve(make_tuple(1LL, b, lcm));
}

Long Query(Long a, Long b) {
  cout << "? " << a << " " << b << endl;
  Long g;
  cin >> g;
  return g;
}

void Answer(Long x) {
  cout << "! " << x << endl;
}

void Go(void) {
  vector<Long> primes = {5, 7, 11, 13, 17, 19, 23, 29};
  Long product = 1LL;
  for (Long prime : primes) product *= prime;
  vector<Trio> equations;
  set<Long> used;
  for (Long i = 1; i <= 30; i++) {
    Long g = Query(i, i + product);
    for (Long prime : primes) {
      if (g % prime != 0) continue;
      if (used.count(prime) > 0) continue;
      equations.push_back(make_tuple(1LL, Mod(-i, prime), prime));
      used.insert(prime);
    }
  }
  Long x = CRT(equations).first;
  Answer(x);
}

int main(void) {
  int t;
  cin >> t;
  while (t--) Go();
  return 0;
}