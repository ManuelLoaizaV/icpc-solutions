// https://codeforces.com/enter?back=%2Fgym%2F382700%2Fproblem%2FJ
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

struct Item {
    Long v;
    Long w;
};

// MaxValue(i, W, items):
// Maximum value we can get from a knapsack of weight W
// choosing items from [i .. |items| - 1].
Long MaxValue(Long i, Long W, const vector<Item>& items) {
    int n_items = (int)items.size();
    if (i == n_items) return 0;
    Long max_value = MaxValue(i + 1, W, items);
    if (items[i].w <= W) {
        max_value = max(max_value, items[i].v + MaxValue(i + 1, W - items[i].w, items));
    }
    return max_value;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long n, W;
    cin >> n >> W;
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].w >> items[i].v;
    }
    cout << MaxValue(0, W, items) << '\n';
    return 0;
}