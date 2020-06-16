// Gracias, Rodolfo
// Gracias, MarcosK
// Gracias, Graphter
// Obrigado, Dilson
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

const Long N = 1e9;
const Long INF = 1e18;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct Node {
	Long sum;
	bool marked;
	Node* left;
	Node* right;
	Node() : sum(0), marked(false), left(nullptr), right(nullptr) {}
	void push(Long tl, Long tr) {
		if (left == nullptr) {
			left = new Node();
			right = new Node();
		}
		if (marked) {
			// Aplico
			Long tm = (tl + tr) / 2;
			left->sum = tm - tl + 1;
			right->sum = tr - tm;
			// Propago
			left->marked = true;
			right->marked = true;
			// Reinicio
			marked = false;
		}
	}
};

struct SegmentTree {
	Node* root;
	SegmentTree() { root = new Node(); }
	void update(Long l, Long r, Node* node, Long tl, Long tr) {
		if (r < tl or l > tr) return;
		if (l <= tl and tr <= r) {
			// Aplico
			node->sum = tr - tl + 1;
			// Acumulo
			node->marked = true;
		} else {
			Long tm = (tl + tr) / 2;
			node->push(tl, tr);
			update(l, r, node->left, tl, tm);
			update(l, r, node->right, tm + 1, tr);
			node->sum = node->left->sum + node->right->sum;
		}
	}
	Long query(Long l, Long r, Node* node, Long tl, Long tr) {
		if (l <= tl and tr <= r) return node->sum;
		Long tm = (tl + tr) / 2;
		node->push(tl, tr);
		if (r <= tm) return query(l, r, node->left, tl, tm);
		if (tm < l) return query(l, r, node->right, tm + 1, tr);
		return query(l, r, node->left, tl, tm) + query(l, r, node->right, tm + 1, tr);
	}
};

void solve() {
	Long m, c;
	c = 0;
	cin >> m;
	SegmentTree st;
	while (m--) {
		Long t, x, y;
		cin >> t >> x >> y;
		x--;
		y--;
		if (t == 1) {
			Long cur = st.query(x + c, y + c, st.root, 0, N - 1);
			cout << cur << endl;
			c = cur;
		} else {
			st.update(x + c, y + c, st.root, 0, N - 1);
		}
	}
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}