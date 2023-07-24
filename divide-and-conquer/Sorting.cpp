// https://www.spoj.com/problems/SART/en/
#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int>& v, int l, int m, int r) {
    vector<int> left_half;
    vector<int> right_half;
    for (int i = l; i <= m; i++) left_half.push_back(v[i]);
    for (int i = m + 1; i <= r; i++) right_half.push_back(v[i]);

    int left_ptr, right_ptr;
    left_ptr = right_ptr = 0;

    for (int i = l; i <= r; i++) {
        if (left_ptr == left_half.size()) {
            v[i] = right_half[right_ptr];
            right_ptr++;
        } else if (right_ptr == right_half.size()) {
            v[i] = left_half[left_ptr];
            left_ptr++;
        } else if (left_half[left_ptr] < right_half[right_ptr]) {
            v[i] = left_half[left_ptr];
            left_ptr++;
        } else {
            v[i] = right_half[right_ptr];
            right_ptr++;
        }
    }
}

void MergeSort(vector<int>& v, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    MergeSort(v, l, m);
    MergeSort(v, m + 1, r);
    Merge(v, l, m, r);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    MergeSort(v, 0, n - 1);
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }
    cout << '\n';
    return 0;
}