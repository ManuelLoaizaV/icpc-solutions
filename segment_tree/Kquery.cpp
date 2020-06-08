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

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;
typedef vector<Long> Vector;
typedef vector<Pair> PairVector;

const int N = 3e4;
const Long INF = 1e18;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct SegmentTree {
    vector<Long> t[4  * N];
    vector<Long> combine(vector<Long> &L, vector<Long> &R) {
        int sz_L = L.size();
        int sz_R = R.size();
        int n = sz_L + sz_R;
        vector<Long> ans;
        int pos_L = 0;
        int pos_R = 0;
        for (int i = 0; i < n; i++) {
            if (pos_L == sz_L) {
                ans.push_back(R[pos_R]);
                pos_R++;
            } else {
                if (pos_R == sz_R) {
                    ans.push_back(L[pos_L]);
                    pos_L++;
                } else {
                    if (L[pos_L] < R[pos_R]) {
                        ans.push_back(L[pos_L]);
                        pos_L++;
                    } else {
                        ans.push_back(R[pos_R]);
                        pos_R++;
                    }
                }
            }
        }
        return ans;
    }
    void build(vector<Long> &a, Long id, Long tl, Long tr) {
        if (tl == tr) {
            t[id] = {a[tl]};
        } else {
            Long tm = (tl + tr) / 2;
            build(a, 2 * id, tl, tm);
            build(a, 2 * id + 1, tm + 1, tr);
            t[id] = combine(t[2 * id], t[2 * id + 1]);
        }
    }
    Long query(Long l, Long r, Long x, Long id, Long tl, Long tr) {
        if (l <= tl and tr <= r) {
            Long pos = lower_bound(t[id].begin(), t[id].end(), x) - t[id].begin();
            return tr - tl + 1 - pos;
        } else {
            Long tm = (tl + tr) / 2;
            if (r <= tm) return query(l, r, x, 2 * id, tl, tm);
            if (tm < l) return query(l, r, x, 2 * id + 1, tm + 1, tr);
            return query(l, r, x, 2 * id, tl, tm) + query(l, r, x, 2 * id + 1, tm + 1, tr);
        }
    }
} st;

void solve() {
    Long n;
    cin >> n;
    vector<Long> a(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    st.build(a, 1, 0, n - 1);
    Long q;
    cin >> q;
    while (q--) {
        Long i, j, k;
        cin >> i >> j >> k;
        i--;
        j--;
        cout << st.query(i, j, k + 1, 1, 0, n - 1) << endl;
    }
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}