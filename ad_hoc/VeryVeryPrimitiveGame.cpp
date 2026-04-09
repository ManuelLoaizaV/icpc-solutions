// https://atcoder.jp/contests/abc190/tasks/abc190_a
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    long long first, second;
    string first_name = "Takahashi";
    string second_name = "Aoki";
    long long starts;
    cin >> first >> second >> starts;
    if (starts == 1) {
        std::swap(first, second);
        std::swap(first_name, second_name);
    }

    if (first <= second) {
        cout << second_name << endl;
    } else {
        cout << first_name << endl;
    }
    return 0;
}