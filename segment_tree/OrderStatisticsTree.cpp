#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
typedef long long Long;
typedef tree<Long, null_type, less<Long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Long q;
    cin >> q;
    ordered_set ward;
    while (q--) {
        char c;
        Long x;
        cin >> c >> x;
        if (c == 'I') ward.insert(x);
        if (c == 'K') {
            x--;
            if (x >= ward.size()) cout << "invalid" << endl;
            else cout << *ward.find_by_order(x) << endl;
        }
        if (c == 'C') cout << ward.order_of_key(x) << endl;
        if (c == 'D') ward.erase(x);
    }
    return 0;
}