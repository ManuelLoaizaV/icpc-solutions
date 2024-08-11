// https://open.kattis.com/problems/closestsums
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void Solve(int n, int n_test_cases) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int n_queries;
    cin >> n_queries;
    cout << "Case " << n_test_cases << ":" << endl;
    while (n_queries--) {
        int target_sum;
        cin >> target_sum;
        int closest_sum = 1e8;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int current_sum = v[i] + v[j];
                if (abs(target_sum - current_sum) < abs(target_sum - closest_sum)) {
                    closest_sum = current_sum;
                }
            }
        }
        cout << "Closest sum to " << target_sum << " is " << closest_sum << "." << endl;
    }
}

int main(void) {
    int n_test_cases = 0;
    int n;
    while (cin >> n) {
        n_test_cases++;
        Solve(n, n_test_cases);
    }
    return 0;
}