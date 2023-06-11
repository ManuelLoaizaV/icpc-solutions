#include <iostream>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int total_xor = 0;
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        total_xor ^= x;
    }
    cout << total_xor << endl;
    return 0;
}