// https://codeforces.com/problemset/problem/1818/B
#include <iostream>
#include <vector>
using namespace std;

void Solve(void) {
	int n;
	cin >> n;
	if (n == 1) {
		cout << 1 << endl;
		return;
	}
	if (n & 1) {
		cout << -1 << endl;
		return;
	}
	vector<int> v(n);
	for (int i = 1; i <= n; i++) {
		if (i & 1) {
			v[n - i - 1] = i;
		} else {
			v[n - i + 1] = i;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << v[i] << ' ';
	}
	cout << endl;
}

int main(void) {
	int t;
	cin >> t;
	while (t--) Solve();
 	return 0;
}
