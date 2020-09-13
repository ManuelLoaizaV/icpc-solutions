#include <iostream>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

typedef long long Long;

int main() {
	Long a, b, r;
	cin >> a >> b >> r;
	if (a >= 2 * r and b >= 2 * r) cout << "First" << '\n';
	else cout << "Second" << '\n';
	return 0;
}
