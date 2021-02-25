//https://codeforces.com/problemset/problem/813/E
#include <bits/stdc++.h>
using namespace std;

typedef int Long;

struct Node {
  Long sum;
  Node* left;
  Node* right;
  Node(Long sum = 0, Node* left = nullptr, Node* right = nullptr) :
    sum(sum), left(left), right(right) {}
};

struct SegmentTree {
  int n;
  vector<Node*> roots;
  Long Merge(const Long& x, const Long& y) { return x + y; }
  Node* Merge(Node* left, Node* right) { return new Node(Merge(left->sum, right->sum), left, right); }
  Node* Build(const vector<Long>& a, int tl, int tr) {
    if (tl == tr) {
      return new Node(a[tl]);
    } else {
      int tm = (tl + tr) / 2;
      return Merge(Build(a, tl, tm), Build(a, tm + 1, tr));
    }
  }
  SegmentTree(void) {}
  SegmentTree(const vector<Long>& a) {
    n = a.size();
    roots = {Build(a, 0, n - 1)};
  }
  Long Query(int l, int r, Node* node, int tl, int tr) {
    if (l <= tl && tr <= r) return node->sum;
    int tm = (tl + tr) / 2;
    if (r <= tm) return Query(l, r, node->left, tl, tm);
    if (tm < l) return Query(l, r, node->right, tm + 1, tr);
    return Merge(Query(l, r, node->left, tl, tm), Query(l, r, node->right, tm + 1, tr));
  }
  Long Query(int l, int r, int version = -1) {
    if (version == -1) version = roots.size() - 1;
    return Query(l, r, roots[version], 0, n - 1);
  }
  Node* Update(int pos, Long val, Node* node, int tl, int tr) {
    if (tl == tr) return new Node(val);
    int tm = (tl + tr) / 2;
    Node* left = node->left;
    Node* right = node->right;
    if (pos <= tm) {
      left = Update(pos, val, left, tl, tm);
    } else {
      right = Update(pos, val, right, tm + 1, tr);
    }
    return Merge(left, right);
  }
  void Update(int pos, Long val, int version = -1) {
    if (version == -1) version = roots.size() - 1;
    roots.push_back(Update(pos, val, roots[version], 0, n - 1));
  }
  int GetVersion(void) { return roots.size() - 1; }
};

int Compress(vector<int>& a) {
  int n = a.size();
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({a[i], i});
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i - 1].first != pairs[i].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return nxt + 1;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<deque<int>> pos(Compress(a));
  for (int i = 0; i < n; i++) pos[a[i]].push_back(i);
  vector<Long> init(n, 0);
  for (int i = 0; i < pos.size(); i++) {
    if (pos[i].size() == 0) continue;
    int len = min((int) pos[i].size(), k);
    for (int j = 0; j < len; j++) init[pos[i][j]] = 1;
    if (pos[i].size() > k) init[pos[i][k]] = 0;
  }
  SegmentTree st(init);
  vector<int> timer(n);
  timer[0] = 0;
  for (int i = 1; i < n; i++) {
    st.Update(pos[a[i - 1]][0], 0);
    pos[a[i - 1]].pop_front();
    if (pos[a[i - 1]].size() >= k) st.Update(pos[a[i - 1]][k - 1], 1);
    if (pos[a[i - 1]].size() > k) st.Update(pos[a[i - 1]][k], 0);
    timer[i] = st.GetVersion();
  }
  int q;
  cin >> q;
  int last = 0;
  while (q--) {
    int x, y;
    cin >> x >> y;
    int l = ((x + last) % n) + 1;
    int r = ((y + last) % n) + 1;
    if (l > r) swap(l, r);
    l--;
    r--;
    last = st.Query(l, r, timer[l]);
    cout << last << '\n';
  }
  return 0;
}
