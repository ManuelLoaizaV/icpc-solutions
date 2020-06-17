// Gracias, Rodolfo
// Gracias, MarcosK
// Gracias, Graphter
// Obrigado, Dilson
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
const int N = 1e9;

struct Node {
	int sum;
	bool marked;
	Node* left;
	Node* right;
	Node() : sum(0), marked(false), left(nullptr), right(nullptr) {}
	void push(int tl, int tr) {
		left = new Node();
		right = new Node();
		if (marked) {
			int tm = (tl + tr) / 2;
			left->sum = tm - tl + 1;
			right->sum = tr - tm;
			left->marked = right->marked = true;
		}
	}
};

struct SegmentTree {
	Node* root;
	SegmentTree() { root = new Node(); }
	void update(int l, int r, Node* node, int tl, int tr) {
		if (r < tl or l > tr) return;
		if (node->marked) return;
		if (l <= tl and tr <= r) {
			// Aplico
			node->sum = tr - tl + 1;
			// Acumulo
			node->marked = true;
		} else {
			int tm = (tl + tr) / 2;
			if (node->left == nullptr) node->push(tl ,tr);
			update(l, r, node->left, tl, tm);
			update(l, r, node->right, tm + 1, tr);
			node->sum = node->left->sum + node->right->sum;
		}
	}
	int query(int l, int r, Node* node, int tl, int tr) {
		if (l <= tl and tr <= r) return node->sum;
		if (node->marked) {
			int _l = max(l, tl);
			int _r = min(r, tr);
			return _r - _l + 1;
		}
		int tm = (tl + tr) / 2;
		if (node->left == nullptr) node->push(tl, tr);
		if (r <= tm) return query(l, r, node->left, tl, tm);
		if (tm < l) return query(l, r, node->right, tm + 1, tr);
		return query(l, r, node->left, tl, tm) + query(l, r, node->right, tm + 1, tr);
	}
};

void solve() {
	int m, c;
	c = 0;
	scanf("%d", &m);
	SegmentTree st;
	while (m--) {
		int t, x, y;
		scanf("%d %d %d", &t, &x, &y);
		x--;
		y--;
		if (t == 1) {
			int cur = st.query(x + c, y + c, st.root, 0, N - 1);
			printf("%d\n", cur);
			c = cur;
		} else {
			st.update(x + c, y + c, st.root, 0, N - 1);
		}
	}
}

int main() {
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}