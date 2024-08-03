#include <bits/stdc++.h>
using namespace std;

int main(void) {
	int a;
	int b;
	cin >> a;
	cin >> b;
	int cnt = 0;
	while (a <= b) {
		cnt++;
		a *= 3;
		b *= 2;
	}
	cout << cnt << endl;
	return 0;
}

