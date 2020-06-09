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

const int N = 1e5;
const Long INF = 1e18;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct SegmentTree {
	Long t[4 * N], lazy[4 * N];
	Long combine(Long x, Long y) { return x + y; }
	void build(Long id, Long tl, Long tr) {
		lazy[id] = 0;
		if (tl == tr) {
			t[id] = 0;
		} else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			build(left, tl, tm);
			build(right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	void push(Long id, Long tl, Long tr) {
		Long left = 2 * id;
		Long right = 2 * id + 1;
		Long tm = (tl + tr) / 2;
		// Aplico
		t[left] += lazy[id] * (tm - tl + 1);
		t[right] += lazy[id] * (tr - tm);
		// Acumulo
		lazy[left] += lazy[id];
		lazy[right] += lazy[id];
		// Reinicio
		lazy[id] = 0;
	}
	void update(Long l, Long r, Long val, Long id, Long tl, Long tr) {
		if (r < tl or l > tr) return;
		if (l <= tl and tr <= r) {
			// Aplico
			t[id] += val * (tr - tl + 1);
			// Acumulo
			lazy[id] += val;
		} else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			push(id, tl, tr);
			update(l, r, val, left, tl, tm);
			update(l, r, val, right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	Long query(Long l, Long r, Long id, Long tl, Long tr) {
		if (l <= tl and tr <= r) return t[id];
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1;
		push(id, tl, tr);
		if (r <= tm) return query(l, r, left, tl, tm);
		if (tm < l) return query(l, r, right, tm + 1, tr);
		return combine(query(l, r, left, tl, tm), query(l, r, right, tm + 1, tr));
	}
} st;

void solve() {
	Long n, c;
	cin >> n >> c;
	st.build(1, 0, n - 1);
	while (c--) {
		Long t, u, v;
		cin >> t >> u >> v;
		u--;
		v--;
		if (t == 0) {
			Long val;
			cin >> val;
			st.update(u, v, val, 1, 0, n - 1);
		} else {
			cout << st.query(u, v, 1, 0, n - 1) << endl;
		}
	}
}

int main() {
	fastio;
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}