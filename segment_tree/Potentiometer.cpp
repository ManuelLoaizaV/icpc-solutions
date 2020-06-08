#include <bits/stdc++.h>
using namespace std;
typedef long long Long;
const Long N = 2e5;
Long t[4 * N];

void build(vector<Long> &a, Long id, Long tl, Long tr) {
    if (tl == tr) {
        t[id] = a[tl];
    } else {
        Long tm = (tl + tr) / 2;
        build(a, 2 * id, tl, tm);
        build(a, 2 * id + 1, tm + 1, tr);
        t[id] = t[2 * id] + t[2 * id + 1];
    }
}

Long query(Long l, Long r, Long id, Long tl, Long tr) {
    if (l <= tl and tr <= r) {
        return t[id];
    }
    Long tm = (tl + tr) / 2;
    if (tm < l) {
        return query(l, r, 2 * id + 1, tm + 1, tr);
    }
    if (r < tm + 1) {
        return query(l, r, 2 * id, tl, tm);
    }
    return query(l, r, 2 * id, tl, tm) + query(l, r, 2 * id + 1, tm + 1, tr);
}

void update(Long pos, Long val, Long id, Long tl, Long tr) {
    if (tl == tr) {
        t[id] = val;
    } else {
        Long tm = (tl + tr) / 2;
        if (pos <= tm) update(pos, val, 2 * id, tl, tm);
        else update(pos, val, 2 * id + 1, tm + 1, tr);
        t[id] = t[2 * id] + t[2 * id + 1];
    }
}

void solve(int n, int t) {
    vector<Long> a;
    for (int i = 0; i < n; i++) {
        Long x;
        cin >> x;
        a.push_back(x);
    }
    build(a, 1, 0, n - 1);
    cout << "Case " << t << ":" << endl;
    while (true) {
        string s;
        cin >> s;
        if (s.size() == 3) break;
        Long l, r;
        cin >> l >> r;
        if (s[0] == 'M') cout << query(l - 1, r - 1, 1, 0, n - 1) << endl;
        else update(l - 1, r, 1, 0, n - 1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int t = 1;
    while (cin >> n) {
        if (n == 0) break;
        if (t > 1) cout << endl;
        solve(n, t);
        t++;
    }
    return 0;
}