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
	Pair t[4 * N];//{off, on}
	bool lazy[4 * N], marked[4 * N];
	Pair combine(Pair x, Pair y) { return {x.first + y.first, x.second + y.second}; }
	void build(Long id, Long tl, Long tr) {
		lazy[id] = marked[id] = false;
		if (tl == tr) {
			t[id] = {1, 0};
		} else {
			Long tm = (tl + tr) / 2;
			build(2 * id, tl, tm);
			build(2 * id + 1, tm + 1, tr);
			t[id] = combine(t[2 * id], t[2 * id + 1]);
		}
	}
	void push(Long id) {
		int left = 2 * id;
		int right = 2 * id + 1;
		if (marked[id]) {
			// Aplicar
			if (lazy[id]) {
				swap(t[left].first, t[left].second);
				swap(t[right].first, t[right].second);
			}
			// Propago
			lazy[left] ^= lazy[id];
			lazy[right] ^= lazy[id];
			marked[left] = marked[right] = true;
			// Reinicio
			marked[id] = 0;
			lazy[id] = 0;
		}
	}
	void update(Long l, Long r, Long id, Long tl, Long tr) {
		if (r < tl or l > tr) return;
		if (l <= tl and tr <= r) {
			// Aplicar
			swap(t[id].first, t[id].second);
			// Acumular
			lazy[id] ^= 1;
			marked[id] = true;
		} else {
			Long tm = (tl + tr) / 2;
			push(id);
			update(l, r, 2 * id, tl, tm);
			update(l, r, 2 * id + 1, tm + 1, tr);
			t[id] = combine(t[2 * id], t[2 * id + 1]);
		}
	}
	Long query(Long l, Long r, Long id, Long tl, Long tr) {
		if (l <= tl and tr <= r) return t[id].second;
		Long tm = (tl + tr) / 2;
		push(id);
		if (r <= tm) return query(l, r, 2 * id, tl, tm);
		if (tm < l) return query(l, r, 2 * id + 1, tm + 1, tr);
		return query(l, r, 2 * id, tl, tm) + query(l, r, 2 * id + 1, tm + 1, tr);
	}
} st;

void solve() {
	Long n, m;
	cin >> n >> m;
	st.build(1, 0, n - 1);
	For(i, 0, m) {
		Long t, l, r;
		cin >> t >> l >> r;
		l--;
		r--;
		if (t == 0) st.update(l, r, 1, 0, n - 1);
		else cout << st.query(l, r, 1, 0, n - 1) << endl;
	}
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}