// https://codeforces.com/contest/1916/problem/E
#include <bits/stdc++.h>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;

const char ENDL = '\n';

struct SegmentChange {
  int to_add;
  // Make sure the default constructor is the identity SegmentChange
  SegmentChange(int _to_add = 0) : to_add(_to_add) {}
  bool HasChange(void) const { return to_add != 0; }
  void Merge(const SegmentChange &other) {
    to_add += other.to_add;
  }
};
struct Segment {
  int maximum;
  Segment(int _maximum = 0) : maximum(_maximum) {}
  void Merge(const Segment &other) {
    maximum = max(maximum, other.maximum);
  }
  void Merge(const Segment &left, const Segment &right) {
    *this = left;
    Merge(right);
  }
  void Apply(int start, int end, const SegmentChange &change) {
    maximum += change.to_add;
  }
};
struct SegmentTree {
  int initial_n = 0;
  int tree_n = 0;
  vector<Segment> tree;
  vector<SegmentChange> changes;
  SegmentTree(int n = -1) { if (n >= 0) Init(n); }
  void Init(int n) {
    initial_n = n;
    tree_n = 2 * initial_n;
    tree.assign(tree_n, Segment());
    changes.assign(tree_n, SegmentChange());
  }
  void Build(const vector<Segment> &initial, int segment_id, int start, int end) {
    if (start == end) {
      tree[segment_id].Merge(initial[start]);
      return;
    }
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Build(initial, left_segment_id, start, mid);
    Build(initial, right_segment_id, mid + 1, end);
    tree[segment_id].Merge(tree[left_segment_id], tree[right_segment_id]);
  }
  void Build(const vector<Segment> &initial) { // O(n)
    int n = (int)initial.size();
    Init(n);
    Build(initial, 1, 0, n - 1);
  }
  void ApplyAndMerge(int segment_id, int start, int end, const SegmentChange &change) {
    tree[segment_id].Apply(start, end, change);
    changes[segment_id].Merge(change);
  }
  void Push(int segment_id, int start, int end) {
    if (!changes[segment_id].HasChange()) return;
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    ApplyAndMerge(left_segment_id, start, mid, changes[segment_id]);
    ApplyAndMerge(right_segment_id, mid + 1, end, changes[segment_id]);
    changes[segment_id] = SegmentChange();
  }
  Segment Query(int query_start, int query_end, int segment_id, int start, int end) {
    if (query_start <= start && end <= query_end) return tree[segment_id];
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Push(segment_id, start, end);
    if (query_end <= mid) return Query(query_start, query_end, left_segment_id, start, mid);
    if (mid < query_start) return Query(query_start, query_end, right_segment_id, mid + 1, end);
    Segment response = Query(query_start, query_end, left_segment_id, start, mid);
    response.Merge(Query(query_start, query_end, right_segment_id, mid + 1, end));
    return response;
  }
  Segment Query(int query_start, int query_end) { return Query(query_start, query_end, 1, 0, initial_n - 1); }
  Segment QueryFull(void) { return tree[1]; }
  void Update(int update_start, int update_end, const SegmentChange &change, int segment_id, int start, int end) {
    if (end < update_start || update_end < start) return;
    if (update_start <= start && end <= update_end) {
      ApplyAndMerge(segment_id, start, end, change);
      return;
    }
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Push(segment_id, start, end);
    Update(update_start, update_end, change, left_segment_id, start, mid);
    Update(update_start, update_end, change, right_segment_id, mid + 1, end);
    tree[segment_id].Merge(tree[left_segment_id], tree[right_segment_id]);
  }
  void Update(int update_start, int update_end, const SegmentChange &change) { Update(update_start, update_end, change, 1, 0, initial_n - 1); }
};

typedef long long Long;

struct Graph {
  SegmentTree st;
  vector<vector<int>> adj;
  vector<set<pair<int, int>>> roots;
  vector<int> in;
  vector<int> out;
  int n_vertices;
  Graph(int n) {
    n_vertices = n;
    adj.resize(n);
    roots.resize(n);
    in.resize(n);
    out.resize(n);
    st.Init(2 * n);
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
  }
  void DFS(int u, int& tick) {
    in[u] = tick++;
    for (int v : adj[u]) {
      DFS(v, tick);
    }
    out[u] = tick++;
  }
  void f(int u, Long& max_f, const vector<int>& a) {
    // If u is leaf, then then its chain has one activity
    if (adj[u].empty()) {
      st.Update(in[u], in[u], {1});
      roots[a[u]].insert(make_pair(in[u], out[u]));
      max_f = max(max_f, 1LL);
      return;
    }

    // Compute chains in subtree without u
    for (int v : adj[u]) f(v, max_f, a);
    
    // Add one activity to all chains in current subtree
    st.Update(in[u], out[u], {1});

    // Remove one activity to all chains in current subtree that have current activity
    auto it = lower_bound(roots[a[u]].begin(), roots[a[u]].end(), make_pair(in[u], -1));
    while (it != roots[a[u]].end() && it->first < out[u]) {
      st.Update(it->first, it->second, {-1});
      it = roots[a[u]].erase(it);
    }

    // Remember current node as the last appearance of the activity
    roots[a[u]].insert(make_pair(in[u], out[u]));

    // Calculate the max product of at most two chains
    Long max_product = 1LL;
    Long max_chain = 1LL;
    for (int v : adj[u]) {
      Long max_chain_subtree = (Long)st.Query(in[v], out[v]).maximum;
      max_product = max(max_product, max_chain * max_chain_subtree);
      max_chain = max(max_chain, max_chain_subtree);
    }
    max_f = max(max_f, max_product);
  }
};

void Solve(void) {
  int n;
  cin >> n;
  Graph graph(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    p--;
    graph.AddEdge(p, i);
  }
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
  }

  int first_tick = 0;
  graph.DFS(0, first_tick);
  Long max_f = 0LL;
  graph.f(0, max_f, a);
  cout << max_f << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}

