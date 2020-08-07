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

const int N = 5e3;
const Long INF = 1e18;
const Double EPS = 10e-9;

Long n, k;
Long skill[N], value[N];
Long dp[N + 5][N + 5];
bool done[N + 5][N + 5];

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long search(Long l, Long r, Long target) {
	if (skill[r] <= target) return r;
	while (r - l > 1) {
		Long mid = (l + r) / 2;
		if (skill[mid] <= target) l = mid;
		else r = mid;
	}
	if (skill[r] <= target) return r;
	return l;
}

// DP(i, j) : maxima cantidad de personas que se pueden obtener 
// en el intervalo [i ... n - 1] con j equipos restantes
Long DP(Long pos, Long left) {
	if (left == 0) return 0;
	if (pos == n) return 0;
	if (done[pos][left]) return dp[pos][left];
	dp[pos][left] = max(value[pos] + DP(pos + value[pos], left - 1), DP(pos + 1, left));
	done[pos][left] = true;
	return dp[pos][left];
}

void solve() {
	cin >> n >> k;
	For(i, 0, n) cin >> skill[i];
	sort(skill, skill + n);
	For(i, 0, n) {
		Long pos = search(i, n - 1, skill[i] + 5);
		value[i] = pos - i + 1;
	}
	cout << DP(0, k) << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}