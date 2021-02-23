//https://www.spoj.com/problems/PSEGTREE/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e5;

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
  Node* Update(int pos, Long add, Node* node, int tl, int tr) {
    if (tl == tr) return new Node(node->sum + add);
    int tm = (tl + tr) / 2;
    Node* left = node->left;
    Node* right = node->right;
    if (pos <= tm) {
      left = Update(pos, add, left, tl, tm);
    } else {
      right = Update(pos, add, right, tm + 1, tr);
    }
    return Merge(left, right);
  }
  void Update(int pos, Long add, int version = -1) {
    if (version == -1) version = roots.size() - 1;
    roots.push_back(Update(pos, add, roots[version], 0, n - 1));
  }
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  SegmentTree st(a);
  int q;
  cin >> q;
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int id, pos;
      Long add;
      cin >> id >> pos >> add;
      pos--;
      st.Update(pos, add, id);
    } else {
      int id, l, r;
      cin >> id >> l >> r;
      l--;
      r--;
      cout << st.Query(l, r, id) << '\n';
    }
  }
  return 0;
}
