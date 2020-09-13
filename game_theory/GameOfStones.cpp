#include <iostream>
#include <vector>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
using namespace std;

typedef long long Long;

const Long N = 1e2;

bool done[N + 1], dp[N + 1];

bool is_winning(Long n) {
	if (n == 0) return false;
	if (done[n]) return dp[n];
	vector<Long> moves = {n - 2, n - 3, n - 5};
	done[n] = true;
	for (int next_pos : moves)
		if (next_pos >= 0 and not is_winning(next_pos)) return dp[n] = true;
	return dp[n] = false;
}

void solve() {
	Long n;
	cin >> n;
	if (is_winning(n)) cout << "First" << '\n';
	else cout << "Second" << '\n';
}

int main() {
	fastio;
	Long t;
	cin >> t;
	while (t--) solve();
	return 0;
}
