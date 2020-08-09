// Gracias, Rodolfo
// Gracias, MarcosK
// Gracias, Graphter
// Obrigado, Dilson
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define fastio ios::sync_with_stdio(0);cin.tie(0)
#define For(i,a,b) for (Long i = a; i < b; i++)
#define roF(i,a,b) for (Long i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(v) (v).begin(),(v).end()

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;
typedef vector<Long> Vector;
typedef vector<Pair> PairVector;

const Long N = 2e3;
const Long MASK = 1 << 9;
const Long INF = 1e18;
const Double EPS = 10e-9;
const Long MOD = 1e9 + 7LL;
Long dp[N][MASK];
bool done[N][MASK];
bool banned[N][N];
Long n, e, k;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long add(Long a, Long b) {
	return (a + b) % MOD;
}

Long get_bit(Long mask, Long bit) {
	return (mask >> bit) & 1LL;
}

void turn_on(Long& mask, Long bit) {
	mask = mask | (1LL << bit);
}

void turn_off(Long& mask, Long bit) {
	mask = mask & (~(1 << bit));
}

Long DP(Long pos, Long mask) {
	if (pos == n) return 1LL;
	if (done[pos][mask]) return dp[pos][mask];
	Long l = max(0LL, pos - e);
	Long r = min(n - 1, pos + e);
	dp[pos][mask] = 0LL;
	For(to, l, r + 1) {
		Long bit = to - (pos - e);
		if ((not banned[pos][to]) and (get_bit(mask, bit) == 0)) {
			Long new_mask = mask;
			turn_on(new_mask, bit);
			new_mask >>= 1;
			dp[pos][mask] = add(dp[pos][mask], DP(pos + 1, new_mask));
		}
	}
	done[pos][mask] = true;
	return dp[pos][mask];
}

void solve() {
	cin >> n >> e >> k;
	while (k--) {
		Long x, y;
		cin >> x >> y;
		x--;
		y--;
		banned[x][y] = true;
	}
	cout << DP(0, 0) << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}