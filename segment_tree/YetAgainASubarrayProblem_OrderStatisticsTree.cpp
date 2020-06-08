//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

typedef long long Long;
typedef pair<Long, Long> Pair;
typedef tree<Pair, null_type, less<Pair>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    Long n, k;
    scanf("%ld %ld", &n, &k);
    Long a[n];
    for (int i = 0; i < n; i++) scanf("%ld", &a[i]);
    int l, r;
    l = r = 0;
    ordered_set ward;
    Long ans = 0LL;
    ward.insert({a[0], 0});
    while (r < n) {
        while (((r & 1) == 0 and l <= r) or ((r & 1) == 1 and l >= 0)) {
            Long m = (k + r - l) / (r - l + 1);
            Long pos = k / m;
            if (pos * m == k) pos--;
            Long target = (*ward.find_by_order(pos)).first;
            Long cnt = ward.order_of_key({target + 1, -1}) - ward.order_of_key({target, -1});
            Long new_pos = ward.order_of_key({cnt, -1});
            Long sz = ward.size();
            cout << target << " " << cnt << endl;
            if (new_pos < sz and (*ward.find_by_order(new_pos)).first == cnt) ans++;
            if ((r & 1) == 0) {
                ward.erase({a[l], l});
                l++;
            } else {
                l--;
                if (l >= 0) ward.insert({a[l], l});
            }
        }
        if (l < 0) l++;
        r++;
        if (r < n) ward.insert({a[r], r});
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