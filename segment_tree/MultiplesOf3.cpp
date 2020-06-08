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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct SegmentTree {
	vector<Long> t[4 * N];
	Long lazy[4 * N];
	vector<Long> combine(vector<Long> x, vector<Long> y) {
		vector<Long> ans;
		For(i, 0, 3) ans.push_back(x[i] + y[i]);
		return ans;
	}
	void build(Long id, Long tl, Long tr) {
		lazy[id] = 0;
		if (tl == tr) {
			t[id] = {1, 0, 0};
		} else {
			Long tm = (tl + tr) / 2;
			build(2 * id, tl, tm);
			build(2 * id + 1, tm + 1, tr);
			t[id] = combine(t[2 * id], t[2 * id + 1]);
		}
	}
	void rot(vector<Long> &a, Long steps) {
		if (steps == 0) return;
		if (steps == 1) {
			swap(a[0], a[1]);
			swap(a[0], a[2]);
		} else {
			swap(a[0], a[2]);
			swap(a[0], a[1]);
		}
	}
	void push(Long id) {
		Long left = 2 * id;
		Long right = 2 * id + 1;
		rot(t[left], lazy[id]);
		rot(t[right], lazy[id]);
		lazy[left] = (lazy[left] + lazy[id]) % 3;
		lazy[right] = (lazy[right] + lazy[id]) % 3;
		lazy[id] = 0;
	}
	void update(Long l, Long r, Long id, Long tl, Long tr) {
		if (r < tl or l > tr) return;
		if (l <= tl and tr <= r) {
			rot(t[id], 1);
			lazy[id] = (lazy[id] + 1) % 3;
		} else {
			Long tm = (tl + tr) / 2;
			Long left = 2 * id;
			Long right = 2 * id + 1;
			push(id);
			update(l, r, left, tl, tm);
			update(l, r, right, tm + 1, tr);
			t[id] = combine(t[left], t[right]);
		}
	}
	Long query(Long l, Long r, Long id, Long tl, Long tr) {
		if (l <= tl and tr <= r) return t[id][0];
		Long tm = (tl + tr) / 2;
		Long left = 2 * id;
		Long right = 2 * id + 1;
		push(id);
		if (r <= tm) return query(l, r, left, tl, tm);
		if (tm < l) return query(l, r, right, tm + 1, tr);
		return query(l, r, left, tl, tm) + query(l, r, right, tm + 1, tr);
	}
} st;

void solve() {
	Long n, q;
	cin >> n >> q;
	st.build(1, 0, n - 1);
	while (q--) {
		Long t, l, r;
		cin >> t >> l >> r;
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