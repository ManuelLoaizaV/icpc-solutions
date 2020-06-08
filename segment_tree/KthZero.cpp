#include <bits/stdc++.h>
using namespace std;
typedef long long Long;

const int N = 1e5;
Long t[4 * N];

void build(vector<Long> &a, Long id, Long tl, Long tr) {
    if (tl == tr) {
        if (a[tl] == 0) t[id] = 1LL;
    } else {
        Long tm = (tl + tr) / 2;
        build(a, 2 * id, tl, tm);
        build(a, 2 * id + 1, tm + 1, tr);
        t[id] = t[2 * id] + t[2 * id + 1];
    }
}

void update(vector<Long> &a, Long pos, Long val, Long id, Long tl, Long tr) {
    if (tl == tr) {
        if (a[pos] == 0) t[id]--;
        a[pos] = val;
        if (a[pos] == 0) t[id]++;
    } else {
        Long tm = (tl + tr) / 2;
        if (pos <= tm) update(a, pos, val, 2 * id, tl, tm);
        else update(a, pos, val, 2 * id + 1, tm + 1, tr);
        t[id] = t[2 * id] + t[2 * id + 1];
    }
}

Long query(Long k, Long id, Long tl, Long tr) {
    if (t[id] < k) return -1;
    if (tl == tr) return tl;
    Long tm = (tl + tr) / 2;
    if (t[2 * id] >= k) return query(k, 2 * id, tl, tm);
    return query(k - t[2 * id], 2 * id + 1, tm + 1, tr);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Long n, q;
    cin >> n >> q;
    vector<Long> a;
    for (int i = 0; i < n; i++) {
        Long x;
        cin >> x;
        a.push_back(x);
    }
    build(a, 1, 0, n - 1);
    while (q--) {
        Long t;
        cin >> t;
        if (t == 1) {
            Long k;
            cin >> k;
            Long pos = query(k, 1, 0, n - 1);
            if (pos == -1) cout << "NO" << endl;
            else cout << pos << endl;
        } else {
            Long p, x;
            cin >> p >> x;
            update(a, p, x, 1, 0, n - 1);
        }
    }
    return 0;
}