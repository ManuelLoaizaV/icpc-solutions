//https://codeforces.com/contest/1478/problem/F
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct Punto {
  Long x, y;
  void Read(void) {
    cin >> x >> y;
  }
};

Long Square(Long a) {
  return a * a;
}

Long SquareDistance(const Punto& p1, const Punto& p2) {
  return Square(p1.x - p2.x) + Square(p1.y - p2.y);
}

void Solve(void) {
  int n;
  cin >> n;
  vector<Punto> p(n);
  for (int i = 0; i < n; i++) p[i].Read();
  vector<bool> is_done(n, false);
  is_done[0] = true;
  vector<int> answer;
  answer.push_back(0);
  for (int i = 0; i < n - 1; i++) {
    int last = answer.end()[-1];
    int who = -1;
    Long maximum = 0;
    for (int j = 0; j < n; j++) {
      if (!is_done[j]) {
        Long current = SquareDistance(p[last], p[j]);
        if (current > maximum) {
          maximum = current;
          who = j;
        }
      }
    }
    answer.push_back(who);
    is_done[who] = true;
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << answer[i] + 1;
  }
  cout << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}

