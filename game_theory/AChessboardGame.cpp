#include <iostream>
#include <vector>
#define fastio ios::sync_with_stdio(0);cin.tie(0)
#define x first
#define y second
using namespace std;
typedef long long Long;
typedef pair<Long, Long> Pair;
const Long N = 15;
bool done[N][N], dp[N][N];

bool ok(Pair p) {
	if (0 <= p.x and p.x < N and 0 <= p.y and p.y < N) return true;
	return false;
}

bool is_winning(Pair current) {
	int row = current.x;
	int col = current.y;
	if (done[row][col]) return dp[row][col];
	done[row][col] = true;
	vector<Pair> moves = {{row - 2, col + 1}, {row - 2, col - 1}, {row + 1, col - 2}, {row - 1, col - 2}};
	for (Pair next_state : moves)
		if (ok(next_state) and not is_winning(next_state)) return dp[row][col] = true;
	return dp[row][col] = false;
}

void solve() {
	Pair start;
	cin >> start.x >> start.y;
	start.x--;
	start.y--;
	if (is_winning(start)) cout << "First" << endl;
	else cout << "Second" << endl;
}

int main() {
	fastio;
	Long t;
	cin >> t;
	while (t--) solve();
	return 0;
}
