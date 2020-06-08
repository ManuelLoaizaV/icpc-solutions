#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 2e3;
Long t[4 * (N + 1)];
Long freq[N + 1];

void init() {
    int sz = 4  * (N + 1);
    for (int i = 0; i < sz; i++) t[i] = 0LL;
    for (int i = 0; i <= N; i++) freq[i] = 0LL;
}

void update(Long pos, Long val, Long id, Long tl, Long tr) {
    if (tl == tr) {
        t[id] += val;
        freq[pos] += val;
    } else {
        Long tm = (tl + tr) / 2;
        if (pos <= tm) update(pos, val, 2 * id, tl, tm);
        else update(pos, val, 2 * id + 1, tm + 1, tr);
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

void solve() {
    Long n, k;
    scanf("%ld %ld", &n, &k);
    Long a[n];
    for (int i = 0; i < n; i++) scanf("%ld", &a[i]);
    int l, r;
    l = r = 0;
    Long ans = 0LL;
    init();
    update(a[0], 1, 1, 0, N);
    while (r < n) {
        while (((r & 1) == 0 and l <= r) or ((r & 1) == 1 and l >= 0)) {
            Long m = (k + r - l) / (r - l + 1);
            Long pos = k / m;
            if (pos * m == k) pos--;
            pos++;
            Long target = query(pos, 1, 0, N);
            Long cnt = freq[target];
            if (freq[cnt] > 0) ans++;
            if ((r & 1) == 0) {
                update(a[l], -1, 1, 0, N);
                l++;
            } else {
                l--;
                if (l >= 0) update(a[l], 1, 1, 0, N);
            }
        }
        if (l < 0) l++;
        r++;
        if (r < n) update(a[r], 1, 1, 0, N);
    }
    printf("%d\n", ans);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    scanf("%d", &t);
    while (t--) solve();
    return 0;
}