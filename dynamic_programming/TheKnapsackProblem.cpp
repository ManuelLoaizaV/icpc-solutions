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

const int N = 2e3;
const Long INF = 1e15;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long dp[N + 1][N];
bool done[N + 1][N];
Pair a[N];
Long n, capacity;

Long DP(Long cap, Long pos) {
	if (cap < 0) return -INF;
	if (cap == 0) return 0;
	if (pos == n) return 0;
	if (done[cap][pos]) return dp[cap][pos];
	dp[cap][pos] = max(DP(cap, pos + 1), a[pos].second + DP(cap - a[pos].first, pos + 1));
	done[cap][pos] = true;
	return dp[cap][pos];
}

void solve() {
	cin >> capacity >> n;
	For(i, 0, n) cin >> a[i].first >> a[i].second;
	Long ans = 0LL;
	ans = max(ans, DP(capacity, 0));
	cout << ans << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}