//https://codeforces.com/problemset/problem/669/E
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 1e5 + 5;

struct Operation {
  int a, t, x, id;
};

struct FenwickTree {
  int tree[N + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0;
  }

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
} ft;

int CompressValue(vector<Operation>& op) {
  int n = op.size();
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({op[i].x, i});
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    op[pairs[i].second].x = nxt;
  }
  return nxt + 1;
}

int CompressTime(vector<Operation>& op) {
  int n = op.size();
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({op[i].t, i});
  sort(pairs.begin(), pairs.end());
  int nxt = 1;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    op[pairs[i].second].t = nxt;
  }
  return nxt;
}

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  vector<Operation> op(n);
  for (int i = 0; i < n; i++) {
    cin >> op[i].a >> op[i].t >> op[i].x;
    op[i].id = i;
  }
  
  int cnt_x = CompressValue(op);
  vector<Operation> op_x[cnt_x];
  for (int i = 0; i < n; i++) op_x[op[i].x].push_back(op[i]);
  
  vector<pair<int, int>> ans;
  for (int i = 0; i < cnt_x; i++) {
    int cnt_t = CompressTime(op_x[i]);
    ft.Build(cnt_t);
    for (int j = 0; j < op_x[i].size(); j++) {
      if (op_x[i][j].a == 1) ft.Update(op_x[i][j].t, 1);
      if (op_x[i][j].a == 2) ft.Update(op_x[i][j].t, -1);
      if (op_x[i][j].a == 3) ans.push_back({op_x[i][j].id, ft.Query(op_x[i][j].t)});
    }
  }
  sort(ans.begin(), ans.end());
  int len = ans.size();
  for (int i = 0; i < len; i++) cout << ans[i].second << '\n';
  return 0;
}
