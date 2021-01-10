//https://www.hackerrank.com/contests/university-codesprint-4/challenges/unique-art
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef pair<int, int> Pair;

const int N = 1e6 + 5;

struct Student {
  int l, r, id;
  bool operator < (const Student& other) {
    return l < other.l;
  }
};

struct FenwickTree {
  int tree[N + 1];

  void Update(int i, int delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  int Query(int i) {
    int ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} good_ft, bad_ft;

int CoordinateCompression(vector<int>& a) {
  int n = a.size();
  vector<Pair> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({a[i], i});
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return (nxt + 1);
}

bool IsValid(Pair p) {
  return p.first <= p.second;
}

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  vector<int> t(n);
  for (int i = 0; i < n; i++) cin >> t[i];
  
  int len = CoordinateCompression(t);
  vector<vector<int>> pos(len);
  for (int i = 0; i < len; i++) pos[i].push_back(0);
  for (int i = 0; i < n; i++) pos[t[i]].push_back(i + 1);
  for (int i = 0; i < len; i++) pos[i].push_back(n + 1);

  vector<Pair> good, bad;
  for (int i = 0; i < len; i++) {
    int sz = pos[i].size();
    for (int j = 1; j < sz - 1; j++) {
      Pair ok = {pos[i][j - 1] + 1, pos[i][j + 1] - 1};
      Pair not_ok_left = {pos[i][j - 1] + 1, pos[i][j] - 1};
      Pair not_ok_right = {pos[i][j] + 1, pos[i][j + 1] - 1};
      good.push_back(ok);
      if (IsValid(not_ok_left)) bad.push_back(not_ok_left);
      if (IsValid(not_ok_right)) bad.push_back(not_ok_right);
    }
  }
  sort(good.begin(), good.end());
  sort(bad.begin(), bad.end());
  
  int q;
  cin >> q;
  vector<Student> st(q);
  for (int i = 0; i < q; i++) {
    cin >> st[i].l >> st[i].r;
    st[i].id = i;
  }
  sort(st.begin(), st.end());
  
  vector<int> ans(q);
  int good_size = good.size();
  int bad_size = bad.size();
  int good_pos, bad_pos;
  good_pos = bad_pos = 0;
  for (int i = 0; i < q; i++) {
    while (good_pos < good_size && good[good_pos].first <= st[i].l) {
      good_ft.Update(good[good_pos].first, 1);
      good_ft.Update(good[good_pos].second + 1, -1);
      good_pos++;
    }
    while (bad_pos < bad_size && bad[bad_pos].first <= st[i].l) {
      bad_ft.Update(bad[bad_pos].first, 1);
      bad_ft.Update(bad[bad_pos].second + 1, -1);
      bad_pos++;
    }
    int valid = good_ft.Query(st[i].r);
    int not_valid = bad_ft.Query(st[i].r);
    ans[st[i].id] = valid - not_valid;
  }
  for (int i = 0; i < q; i++) cout << ans[i] << '\n';
  return 0;
}
