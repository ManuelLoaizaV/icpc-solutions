#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
const Long N = 5e4 + 5;

struct Data {
    Long sum, maxPref, maxSuff, ans;
    Data(){}
    Data(Long x) {
        sum = x;
        maxPref = x;
        maxSuff = x;
        ans = x;
    }
}t[4 * N];

Data combine(Data left, Data right) {
    Data cur;
    cur.sum = left.sum + right.sum;
    cur.maxPref = max(left.maxPref, left.sum + right.maxPref);
    cur.maxSuff = max(right.maxSuff, right.sum + left.maxSuff);
    cur.ans = max(left.ans, max(right.ans, left.maxSuff + right.maxPref));
    return cur;
}

void build(vector<Long> &a, Long id, Long tl, Long tr) {
    if (tl == tr) {
        t[id] = Data(a[tl]);
    } else {
        int tm = (tl + tr) / 2;
        build(a, 2 * id, tl, tm);
        build(a, 2 * id + 1, tm + 1, tr);
        t[id] = combine(t[2 * id], t[2 * id + 1]);
    }
}

Data query(Long l, Long r, Long id, Long tl, Long tr) {
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
    return combine(query(l, r, 2 * id, tl, tm), query(l, r, 2 * id + 1, tm + 1, tr));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Long n;
    cin >> n;
    vector<Long> a;
    for (int i = 0; i < n; i++) {
        Long x;
        cin >> x;
        a.push_back(x);
    }
    build(a, 1, 0, n - 1);
    Long m;
    cin >> m;
    while (m--) {
        Long l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << query(l, r, 1LL, 0LL, n - 1LL).ans << endl;
    }
    return 0;
}