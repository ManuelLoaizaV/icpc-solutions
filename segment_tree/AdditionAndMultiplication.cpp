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

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 10e-9;
const Long MOD = 1e9 + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long mul(Long a, Long b) { return (a * b) % MOD; }
Long add(Long a, Long b) { return (a + b) % MOD; }

struct SegmentTree {
	Long t[4 * N];
	Pair lazy[4 * N];
	Long combine(Long x, Long y) { return add(x, y); }
	void build(vector<Long> &a, Long id, Long tl, Long tr) {
		t[id] = 0;
		lazy[id] = {1, 0};
		if (tl == tr) {
			t[id] = a[tl]; 
		} else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			build(a, left, tl, tm);
			build(a, right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	void push(Long id, Long tl, Long tr) {
		// ai = m * ai + b
		Long m, b, block;
		m = lazy[id].first;
		b = lazy[id].second;
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1;
		Long left_size = tm - tl + 1;
		Long right_size = tr - tm;
		// Aplico
		t[left] = mul(t[left], m);
		block = mul(left_size, b);
		t[left] = add(t[left], block);
		
		t[right] = mul(t[right], m);
		block = mul(right_size, b);
		t[right] = add(t[right], block);
		// Propago
		lazy[left].first = mul(lazy[left].first, m);
		lazy[left].second = mul(lazy[left].second, m);
		lazy[left].second = add(lazy[left].second, b);
		
		lazy[right].first = mul(lazy[right].first, m);
		lazy[right].second = mul(lazy[right].second, m);
		lazy[right].second = add(lazy[right].second, b);
		// Reinicio
		lazy[id].first = 1;
		lazy[id].second = 0;
	}
	void update(Long l, Long r, Long val, Long typ, Long id, Long tl, Long tr) {
		if (r < tl or l > tr) return;
		if (l <= tl and tr <= r) {
			Long sz = tr - tl + 1;
			Long block = mul(sz, val);
			if (typ == 1) {
				t[id] = add(t[id], block);
				lazy[id].second = add(lazy[id].second, val);
			}
			if (typ == 2) {
				t[id] = mul(t[id], val);
				lazy[id].first = mul(lazy[id].first, val);
				lazy[id].second = mul(lazy[id].second, val);
			}
			if (typ == 3) {
				t[id] = block;
				lazy[id].first = 0;
				lazy[id].second = val;
			}
		} else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			push(id, tl, tr);
			update(l, r, val, typ, left, tl, tm);
			update(l, r, val, typ, right, tm + 1, tr);
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
	Long n, q;
	cin >> n >> q;
	vector<Long> a(n, 0);
	For(i, 0, n) cin >> a[i];
	st.build(a, 1, 0, n - 1);
	while (q--) {
		Long t, x, y;
		cin >> t >> x >> y;
		x--;
		y--;
		if (t <= 3) {
			Long val;
			cin >> val;
			st.update(x, y, val, t, 1, 0, n - 1);
		} else cout << st.query(x, y, 1, 0, n - 1) << endl;
	}
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}