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

const int N = 1e5;
const Long INF = 99824435300001LL;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long n;
string s;
Long cost[N], dp[N][4];
bool done[N][4];

// DP(i, j) : minimo costo de eliminar [i ... n - 1] acumulando el prefijo hasta j
Long DP(Long pos, Long acc) {
	if (acc == 4) return INF;
	if (pos == n) return 0;
	if (done[pos][acc]) return dp[pos][acc];
	if (s[pos] != 'h' and s[pos] != 'a' and s[pos] != 'r' and s[pos] != 'd') {
		dp[pos][acc] = DP(pos + 1, acc);
	} else {
		if (s[pos] == 'h') {
			if (acc == 0) dp[pos][acc] = min(DP(pos + 1, 1), cost[pos] + DP(pos + 1, 0));
			else dp[pos][acc] = DP(pos + 1, acc);
		}
		if (s[pos] == 'a') {
			if (acc == 1) dp[pos][acc] = min(DP(pos + 1, 2), cost[pos] + DP(pos + 1, 1));
			else dp[pos][acc] = DP(pos + 1, acc);
		}
		if (s[pos] == 'r') {
			if (acc == 2) dp[pos][acc] = min(DP(pos + 1, 3), cost[pos] + DP(pos + 1, 2));
			else dp[pos][acc] = DP(pos + 1, acc);
		}
		if (s[pos] == 'd') {
			if (acc == 3) dp[pos][acc] = min(DP(pos + 1, 4), cost[pos] + DP(pos + 1, 3));
			else dp[pos][acc] = DP(pos + 1, acc);
		}
		dp[pos][acc] = min(dp[pos][acc], INF);
	}
	done[pos][acc] = true;
	return dp[pos][acc];
}

void solve() {	
	cin >> n;
	cin >> s;
	for (int i = 0; i < n; i++) cin >> cost[i];
	cout << DP(0, 0) << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}