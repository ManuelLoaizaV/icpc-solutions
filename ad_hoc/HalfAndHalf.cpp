// https://atcoder.jp/contests/arc096/tasks/arc096_a
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    long long a_cost, b_cost, ab_cost;
    long long a_target, b_target;
    cin >> a_cost >> b_cost >> ab_cost >> a_target >> b_target;

    long long min_cost{0LL};

    long long common_target = std::min(a_target, b_target);
    min_cost = common_target * std::min(a_cost + b_cost, 2LL * ab_cost);
    a_target -= common_target;
    b_target -= common_target;

    if (a_target > 0) {
        min_cost += a_target * std::min(a_cost, 2LL * ab_cost);
    } else if (b_target > 0) {
        min_cost += b_target * std::min(b_cost, 2LL * ab_cost);
    }
    cout << min_cost << endl;
    return 0;
}