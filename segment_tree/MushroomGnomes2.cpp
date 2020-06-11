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

const int N = 5e5;
const Long INF = 1e18;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct Tree {
	Long a, h, pl, pr;
} tree[N];

struct SegmentTree {
	Double lazy[4 * N];
	void build(vector<Long> &a, Long id, Long tl, Long tr) {
		lazy[id] = 1.0;
		if (tl == tr) {
			lazy[id] = (Double) a[tl];
		} else {
			Long tm = (tl + tr) / 2;
			build(a, 2 * id, tl, tm);
			build(a, 2 * id + 1, tm + 1, tr);
		}
	}
	void push(Long id) {
		lazy[2 * id] *= lazy[id];
		lazy[2 * id + 1] *= lazy[id];
		lazy[id] = 1.0;
	}
	void update(Long l, Long r, Double val, Long id, Long tl, Long tr) {
		if (r < tl or l > tr) return;
		if (l <= tl and tr <= r) {
			lazy[id] *= val;
		} else {
			Long tm = (tl + tr) / 2;
			push(id);
			update(l, r, val, 2 * id, tl, tm);
			update(l, r, val, 2 * id + 1, tm + 1, tr);
		}
	}
	Double query(Long pos, Long id, Long tl, Long tr) {
		if (tl == tr) return lazy[id];
		Long tm = (tl + tr) / 2;
		push(id);
		if (pos <= tm) return query(pos, 2 * id, tl, tm);
		else return query(pos, 2 * id + 1, tm + 1, tr);
	}
} st;

void solve() {
	Long n, m;
	cin >> n >> m;
	For(i, 0, n) cin >> tree[i].a >> tree[i].h >> tree[i].pl >> tree[i].pr;
	Pair mush[m];//{pos, power}
	For(i, 0, m) cin >> mush[i].first >> mush[i].second;
	set<Long> UNI;
	For(i, 0, n) {
		Long a = tree[i].a;
		Long h = tree[i].h;
		UNI.insert(a - h);
		UNI.insert(a - 1);
		UNI.insert(a + 1);
		UNI.insert(a + h);
	}
	For(i, 0, m) UNI.insert(mush[i].first);
	map<Long, Long> trans;
	Long sz = 0;
	for (auto it = UNI.begin(); it != UNI.end(); it++) {
		trans[*it] = sz;
		sz++;
	}
	vector<Long> a(sz, 0);
	For(i, 0, m) a[trans[mush[i].first]] += mush[i].second;
	st.build(a, 1, 0, sz - 1);
	For(i, 0, n) {
		Long a = tree[i].a;
		Long h = tree[i].h;
		Double notLeft = (Double) (100 - tree[i].pl) / 100.0;
		Double notRight = (Double) (100 - tree[i].pr) / 100.0;
		st.update(trans[a - h], trans[a - 1], notLeft, 1, 0, sz - 1);
		st.update(trans[a + 1], trans[a + h], notRight, 1, 0, sz - 1);
	}
	Double ans = 0.0;
	set<Long> PUCP;
	For(i, 0, m) PUCP.insert(mush[i].first);
	for (auto it = PUCP.begin(); it != PUCP.end(); it++) ans += st.query(trans[*it], 1, 0, sz - 1);
	cout << fixed << setprecision(10) << ans << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}