//https://www.spoj.com/problems/DQUERY/
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
  int GetVersion(void) { return roots.size() - 1; }
};

int Compress(vector<int>& a) {
  int n = a.size();
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({a[i], i});
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return nxt + 1;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<deque<int>> pos(Compress(a));
  for (int i = 0; i < n; i++) pos[a[i]].push_back(i);
  // Contruyo el arreglo con las posiciones iniciales de cada valor unico
  vector<int> init(n, 0);
  for (int i = 0; i < pos.size(); i++) if (pos[i].size() > 0) init[pos[i][0]] = 1;
  // Para cada tiempo, hago la modificacion correspondiente
  SegmentTree st(init);
  vector<int> timer(n);
  timer[0] = 0;
  for (int i = 1; i < n; i++) {
    // Remuevo el anterior
    st.Update(i - 1, -1);
    pos[a[i - 1]].pop_front();
    // Anado su sigueinte aparicion en caso exista
    if (pos[a[i - 1]].size() > 0) st.Update(pos[a[i - 1]][0], 1);
    // Guardo el tiempo para el extremo izquierdo i
    timer[i] = st.GetVersion();
  }
  // Respondo las queries
  int q;
  cin >> q;
  while (q--) {
    int i, j;
    cin >> i >> j;
    i--;
    j--;
    cout << st.Query(i, j, timer[i]) << '\n';
  }
  return 0;
}
