#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;
const Long N = 1e5;

struct Data {
    Pair max1, max2;
    Data(){}
    Data(Long val, Long pos) {
        max1.first = val;
        max1.second = pos;
        max2.first = 0;
        max2.second = -1;
    }
} t[4 * N];

Data combine(Data x, Data y) {
    vector<Pair> aux;
    aux.push_back(x.max1);
    aux.push_back(x.max2);
    aux.push_back(y.max1);
    aux.push_back(y.max2);
    sort(aux.begin(), aux.end());
    Data ans;
    ans.max1 = aux[3];
    ans.max2 = aux[2];
    return ans;
}

void build(vector<Long> &a, Long id, Long tl, Long tr) {
    if (tl == tr) {
        t[id] = Data(a[tl], tl);
    } else {
        Long tm = (tl + tr) / 2;
        build(a, 2 * id, tl, tm);
        build(a, 2 * id + 1, tm + 1, tr);
        t[id] = combine(t[2 * id], t[2 * id + 1]);
    }
}

Data query(Long l, Long r, Long id, Long tl, Long tr) {
    if (l <= tl and tr <= r) return t[id];
    Long tm = (tl + tr) / 2;
    if (tm < l) return query(l, r, 2 * id + 1, tm + 1, tr);
    if (r < tm + 1) return query(l, r, 2 * id, tl, tm);
    return combine(query(l, r, 2 * id, tl, tm), query(l, r, 2 * id + 1, tm + 1, tr));
}

void update(Long pos, Long val, Long id, Long tl, Long tr) {
    if (tl == tr) {
        t[id] = Data(val, pos);
    } else {
        Long tm = (tl + tr) / 2;
        if (pos <= tm) update(pos, val, 2 * id, tl, tm);
        else update(pos, val, 2 * id + 1, tm + 1, tr);
        t[id] = combine(t[2 * id], t[2 * id + 1]);
    }
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
    Long q;
    cin >> q;
    while (q--) {
        char t;
        Long l, r;
        cin >> t >> l >> r;
        if (t == 'U') update(l - 1, r, 1, 0, n - 1);
        else {
            Data ans = query(l - 1, r - 1, 1, 0, n - 1);
            Long res = ans.max1.first + ans.max2.first;
            cout << res << endl;
        }
    }
    return 0;
}