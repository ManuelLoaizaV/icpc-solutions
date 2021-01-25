//https://codeforces.com/problemset/problem/811/C
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 5e3;
vector<int> positions[N + 1];

struct Interval {
  int l, r;
  Long value;

  bool operator < (const Interval& other) const {
    if (l == other.l) return r < other.r;
    return l < other.l;
  }
};

vector<Interval> intervals;
bool is_done[N];
Long dp[N];

Long DP(int i) {
  if (i == intervals.size()) return 0;
  if (is_done[i]) return dp[i];
  int nxt = intervals.size();
  for (int j = i + 1; j < intervals.size(); j++) {
    if (intervals[j].l > intervals[i].r) {
      nxt = j;
      break;
    }
  }
  dp[i] = max(intervals[i].value + DP(nxt), DP(i + 1));
  is_done[i] = true;
  return dp[i];
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    positions[a[i]].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    int left = positions[a[i]][0];
    int right = positions[a[i]].end()[-1];
    int j = left;
    set<Long> elements;
    while (j <= right) {
      elements.insert(a[j]);
      left = min(left, positions[a[j]][0]);
      right = max(right, positions[a[j]].end()[-1]);
      j++;
    }
    Long value = 0;
    for (Long element : elements) value ^= element;
    if (left == i) intervals.push_back({left, right, value});
  }
  sort(intervals.begin(), intervals.end());
  cout << DP(0) << '\n';
  return 0;
}
