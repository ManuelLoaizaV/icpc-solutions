// https://codeforces.com/contest/1902/problem/D
#include <algorithm>
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";

struct Punto {
  Long x, y;
  Punto(void) {}
  Punto(Long x, Long y) : x(x), y(y) {}
  bool operator == (const Punto& p) { return x == p.x && y == p.y; }
  bool operator != (const Punto& p) { return !(*this == p); }
  Punto operator + (const Punto& p) { return Punto(x + p.x, y + p.y); }
  Punto operator - (const Punto& p) { return Punto(x - p.x, y - p.y); }
  bool operator < (Punto p) const { return  x < p.x || x == p.x && y < p.y; }
};

void Solve(void) {
  map<char, Punto> moves{
    {'U', Punto(0, 1)},
    {'D', Punto(0, -1)},
    {'L', Punto(-1, 0)},
    {'R', Punto(1, 0)}
  };

  Long n, Q;
  cin >> n >> Q;
  string s;
  cin >> s;

  vector<Punto> points;
  map<Punto, vector<int>> point_positions;
  points.emplace_back(0, 0);
  point_positions[points[0]].push_back(0);

  for (int i = 0; i < n; i++) {
    points.push_back(points.back() + moves[s[i]]);
    point_positions[points.back()].push_back(i + 1);
  }

  vector<Punto> suffixes;
  map<Punto, vector<int>> suffix_positions;
  suffixes.emplace_back(0, 0);
  suffix_positions[suffixes[0]].push_back(0);

  for (int i = 0; i < n; i++) {
    suffixes.push_back(suffixes.back() + moves[s[n - 1 - i]]);
    suffix_positions[suffixes.back()].push_back(i + 1);
  }

  for (int q = 0; q < Q; q++) {
    Long x, y, l, r;
    cin >> x >> y >> l >> r;
    l--;
    r--;

    Punto target(x, y);

    if (point_positions.count(target) > 0 && (point_positions[target][0] <= l || point_positions[target].back() > r)) {
      cout << YES << ENDL;
      continue;
    }

    int base_suffix_position = n - (r + 1);
    int last_suffix_position = n - l;

    Punto target_suffix = target + suffixes[base_suffix_position] - points[l];
    if (suffix_positions.count(target_suffix) > 0) {
      auto it = upper_bound(suffix_positions[target_suffix].begin(), suffix_positions[target_suffix].end(), base_suffix_position);
      if (it != suffix_positions[target_suffix].end() && *it <= last_suffix_position) {
        cout << YES << ENDL;
        continue;
      }
    }

    cout << NO << ENDL;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}

