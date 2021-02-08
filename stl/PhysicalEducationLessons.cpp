//https://codeforces.com/problemset/problem/915/E
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

const int INF = 1e9 + 5;

// Retorna el intervalo a \ b
vector<Pair> SetMinus(const Pair& a, const Pair& b) {
  Pair intersection = {max(a.first, b.first), min(a.second, b.second)};
  vector<Pair> answer;
  Pair left = {a.first, intersection.first - 1};
  if (left.first <= left.second) answer.push_back(left);
  Pair right = {intersection.second + 1, a.second};
  if (right.first <= right.second) answer.push_back(right);
  return answer;
}

int Size(const Pair& a) {
  return a.second - a.first + 1;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  int q;
  cin >> q;
  set<Pair> intervals;
  intervals.insert({n, 1});
  int answer = n;
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    auto it = intervals.lower_bound({l, -INF});
    Pair query = {l, r};
    // Si es que existe al menos un intervalo
    if (it != intervals.end()) {
      while (!intervals.empty()) {
        it = intervals.lower_bound({l, -INF});
        if (it == intervals.end()) break;
        Pair current = {it->second, it->first};
        if (current.first <= query.second) {
          intervals.erase(it);
          answer -= Size(current);
          vector<Pair> remainders = SetMinus(current, query);
          for (Pair remainder : remainders) {
            intervals.insert({remainder.second, remainder.first});
            answer += Size(remainder);
          }
        } else {
          break;
        }
      }
    }
    if (k == 2) {
      intervals.insert({query.second, query.first});
      answer += Size(query);
    }
    cout << answer << '\n';
  }
  return 0;
}
