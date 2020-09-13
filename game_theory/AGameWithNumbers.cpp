#include <iostream>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

typedef long long Long;

int main() {
	fastio;
	Long n;
	cin >> n;
	Long digit = n % 10;
	if (digit == 0) cout << 2 << endl;
	else {
		cout << 1 << endl;
		cout << digit << endl;
	}
	return 0;
}
