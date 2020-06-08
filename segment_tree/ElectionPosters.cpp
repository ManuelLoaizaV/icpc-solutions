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
#define For(i,a,b) for (Long i = a; i < b; i++)
#define roF(i,a,b) for (Long i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(v) (v).begin(),(v).end()

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;
typedef vector<Long> Vector;
typedef vector<Pair> PairVector;

const int N = 2e5;
const Long INF = 1e18;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct SegmentTree {
	Long lazy[4 * N];
	bool marked[4 * N];
	void build(Long id, Long tl, Long tr) {
		marked[id] = false;
		if (tl == tr) {
			lazy[id] = 0;
		} else {
			Long tm = (tl + tr) / 2;
			build(2 * id, tl, tm);
			build(2 * id + 1, tm + 1, tr);
		}
	}
	void push(Long id) {
		if (marked[id]) {
			lazy[2 * id] = lazy[2 * id + 1] = lazy[id];
			marked[2 * id] = marked[2 * id + 1] = true;
			marked[id] = false;
		}
	}
	void update(Long l, Long r, Long val, Long id, Long tl, Long tr) {
		if (tr < l or tl > r) return;
		if (l <= tl and tr <= r) {
			lazy[id] = val;
			marked[id] = true;
		} else {
			Long tm = (tl + tr) / 2;
			push(id);
			update(l, r, val, 2 * id, tl, tm);
			update(l, r, val, 2 * id + 1, tm + 1, tr);
		}
	}
	Long query(Long pos, Long id, Long tl, Long tr) {
		if (tl == tr) return lazy[id];
		Long tm = (tl + tr) / 2;
		push(id);
		if (pos <= tm) return query(pos, 2 * id, tl, tm);
		else return query(pos, 2 * id + 1, tm + 1, tr);
	}
} st;

void solve() {
	Long q;
	cin >> q;
	Pair queries[q];
	map<Long, Long> Hantroid;
	set<Long> Graphter;
	For(i,0,q) {
		Long u, v;
		cin >> u >> v;
		queries[i].first = u;
		queries[i].second = v;
		Graphter.insert(u);
		if (u > 1) Graphter.insert(u - 1);
		Graphter.insert(v);
		if (v > 1) Graphter.insert(v - 1);
	}
	Long sz = 0;
	std::set<Long>::iterator it;
	for (it = Graphter.begin(); it != Graphter.end(); it++) {
		Hantroid[(*it)] = sz;
		sz++;
	}
	st.build(1, 0, sz - 1);
	For(i, 1, q + 1) {
		Long l = Hantroid[queries[i - 1].first];
		Long r = Hantroid[queries[i - 1].second];
		st.update(l, r, i, 1, 0, sz - 1);
	}
	set<Long> Hymsly;
	For(i, 0, sz) {
		Long Rodolfo = st.query(i, 1, 0, sz - 1);
		if (Rodolfo > 0) Hymsly.insert(Rodolfo);
	}
	cout << Hymsly.size() << endl;
}

int main() {
	fastio;
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}