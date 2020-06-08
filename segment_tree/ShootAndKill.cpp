// Gracias, Rodolfo
// Gracias, MarcosK
// Gracias, Graphter
// Obrigado, Dilson
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define fastio ios::sync_with_stdio(0);cin.tie(0)
#define For(i,a,b) for (int i = a; i < b; i++)
#define roF(i,a,b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(v) (v).begin(),(v).end()
typedef pair<int, int> Pair;
const int N = 2e5;

struct SegmentTree {
	int t[4 * N], lazy[4 * N];
	int combine(int x, int y) { return max(x, y); }
	void build(int id, int tl, int tr) {
		lazy[id] = 0;
		if (tl == tr) {
			t[id] = 0;
		} else {
			int tm = (tl + tr) / 2;
			build(2 * id, tl, tm);
			build(2 * id + 1, tm + 1, tr);
			t[id] = combine(t[2 * id], t[2 * id + 1]);
		}
	}
	void push(int id) {
		t[2 * id] += lazy[id];
		t[2 * id + 1] += lazy[id];
		lazy[2 * id] += lazy[id];
		lazy[2 * id + 1] += lazy[id];
		lazy[id] = 0;
	}
	void update(int l, int r, int add, int id, int tl, int tr) {
		if (tr < l or tl > r) return;
		if (l <= tl and tr <= r) {
			t[id] += add;
			lazy[id] += add;
		} else {
			int tm = (tl + tr) / 2;
			push(id);
			update(l, r, add, 2 * id, tl, tm);
			update(l, r, add, 2 * id + 1, tm + 1, tr);
			t[id] = combine(t[2 * id], t[2 * id + 1]);
		}
	}
	int query(int l, int r, int id, int tl, int tr) {
		if (l <= tl and tr <= r) return t[id];
		int tm = (tl + tr) / 2;
		push(id);
		if (r <= tm) return query(l, r, 2 * id, tl, tm);
		if (tm < l) return query(l, r, 2 * id + 1, tm + 1, tr);
		return combine(query(l, r, 2 * id, tl, tm), query(l, r, 2 * id + 1, tm + 1, tr));
	}
} st;

void solve() {
	int n;
	cin >> n;
	set<int> Graphter;
	Pair Int[n];
	For(i, 0, n) {
		cin >> Int[i].first >> Int[i].second;
		Graphter.insert(Int[i].first);
		Graphter.insert(Int[i].second);
	}
	int q;
	cin >> q;
	Pair Query[q];
	For(i, 0, q) {
		cin >> Query[i].first >> Query[i].second;
		Graphter.insert(Query[i].first);
		Graphter.insert(Query[i].second);
	}
	map<int, int> Cohr;
	int sz = 0;
	for (auto it = Graphter.begin(); it != Graphter.end(); it++) {
		Cohr[*it] = sz;
		sz++;
	}
	st.build(1, 0, sz - 1);
	For(i, 0, n) {
		int l = Cohr[Int[i].first];
		int r = Cohr[Int[i].second];
		st.update(l, r, 1LL, 1, 0, sz - 1);
	}
	For(i, 0 , q) {
		int l = Cohr[Query[i].first];
		int r = Cohr[Query[i].second];
		cout << st.query(l, r, 1, 0, sz - 1) << endl;
	}
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}