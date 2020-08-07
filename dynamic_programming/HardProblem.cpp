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
const Long INF = 1e15;
const Double EPS = 10e-9;

Long n;
Long cost[N];
string s[N][2]; // s[i][0] : i-esima cadena no revertida, s[i][1] : i-esima cadena revertida
Long dp[N][2];
bool done[N][2];

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

// DP(i, j) : minimo costo de ordenar lexicograficamente [i ... n - 1]
// habiendo j revertido la cadena s[i - 1]
Long DP(Long pos, Long rev) {
	if (pos == n) return 0;
	if (done[pos][rev]) return dp[pos][rev];
	done[pos][rev] = true;
	dp[pos][rev] = INF;
	if (pos == 0) {
		dp[pos][rev] = min(DP(pos + 1, 0), cost[pos] + DP(pos + 1, 1));
	} else {
		Long comp_no_rev = s[pos - 1][rev].compare(s[pos][0]);
		Long comp_rev = s[pos - 1][rev].compare(s[pos][1]);
		if (comp_no_rev > 0 and comp_rev > 0) return dp[pos][rev];
		if (comp_no_rev <= 0) dp[pos][rev] = min(dp[pos][rev], DP(pos + 1, 0));
		if (comp_rev <= 0) dp[pos][rev] = min(dp[pos][rev], cost[pos] + DP(pos + 1, 1));
	}
	return dp[pos][rev];
}

void solve() {
	cin >> n;
	For(i, 0, n) cin >> cost[i];
	For(i, 0 , n) {
		string aux;
		cin >> aux;
		s[i][0] = aux;
		reverse(all(aux));
		s[i][1] = aux;
	}
	Long ans = DP(0, 0);
	if (ans >= INF) cout << "-1" << endl;
	else cout << ans << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}