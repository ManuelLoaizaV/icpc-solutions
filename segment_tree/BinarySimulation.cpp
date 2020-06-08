// Gracias, Rodolfo
// Gracias, MarcosK
// Gracias, Graphter
// Obrigado, Dilson
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = a; i < b; i++)
using namespace std;
const int N = 1e6;

struct SegmentTree {
    bool lazy[4 * N];
    void build(vector<bool> &a, int id, int tl, int tr) {
        if (tl == tr) {
            lazy[id] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * id, tl, tm);
            build(a, 2 * id + 1, tm + 1, tr);
            lazy[id] = 0;
        }
    }
    void push(int id) {
        lazy[2 * id] ^= lazy[id];
        lazy[2 * id + 1] ^= lazy[id];
        lazy[id] = 0;
    }
    void update(int l, int r, int add, int id, int tl, int tr) {
        if (tr < l or tl > r) return;
        if (l <= tl and tr <= r) {
            lazy[id] ^= add;
        } else {
            push(id);
            int tm = (tl + tr) / 2;
            update(l, r, add, 2 * id, tl, tm);
            update(l, r, add, 2 * id + 1, tm + 1, tr);
        }
    }
    int query(int pos, int id, int tl, int tr) {
        if (tl == tr) return lazy[id];
        push(id);
        int tm = (tl + tr) / 2;
        if (pos <= tm) return query(pos, 2 * id, tl, tm);
        else return query(pos, 2 * id + 1, tm + 1, tr);
    }
} st;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<bool> a(n, 0);
    For(i,0,n) a[i] = s[i] - '0';
    st.build(a, 1, 0, n - 1);
    int q;
    scanf("%d", &q);
    while (q--) {
        char c[2];
        scanf("%2s", c);
        if (c[0] == 'I') {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;
            r--;
            st.update(l, r, 1, 1, 0, n - 1);
        } else {
            int pos;
            scanf("%d", &pos);
            pos--;
            printf("%d\n", st.query(pos, 1, 0, n - 1));
        }
    }
}

int main() {
    int t = 1;
    scanf("%d", &t);
    For(i,1,t+1) {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}