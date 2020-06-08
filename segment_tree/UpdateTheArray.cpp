// Gracias, Rodolfo
// Gracias, MarcosK
// Gracias, Graphter
// Obrigado, Dilson
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef long long Long;
const int N = 1e4;

struct SegmentTree {
    Long lazy[4 * N];
    void build(Long id, Long tl, Long tr) {
        if (tl == tr) {
            lazy[id] = 0;
        } else {
            Long tm = (tl + tr) / 2;
            build(2 * id, tl, tm);
            build(2 * id + 1, tm + 1, tr);
            lazy[id] = 0;
        }
    }
    void push(Long id) {
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
        lazy[id] = 0;
    }
    void update(Long l, Long r, Long add, Long id, Long tl, Long tr) {
        if (tr < l or tl > r) return;
        if (l <= tl and tr <= r) {
            lazy[id] += add;
        } else {
            push(id);
            Long tm = (tl + tr) / 2;
            update(l, r, add, 2 * id, tl, tm);
            update(l, r, add, 2 * id + 1, tm + 1, tr);
        }
    }
    Long query(Long pos, Long id, Long tl, Long tr) {
        if (tl == tr) return lazy[id];
        push(id);
        Long tm = (tl + tr) / 2;
        if (pos <= tm) return query(pos, 2 * id, tl, tm);
        else return query(pos, 2 * id + 1, tm + 1, tr);
    }
} st;

void solve() {
    Long n, q;
    cin >> n >> q;
    st.build(1, 0, n - 1);
    while (q--) {
        Long l, r, add;
        cin >> l >> r >> add;
        st.update(l, r, add, 1, 0, n - 1);
    }
    cin >> q;
    while (q--) {
        Long pos;
        cin >> pos;
        cout << st.query(pos, 1, 0, n - 1) << endl;
    }
}

int main() {
    fastio;
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}