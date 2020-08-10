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

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;
typedef vector<Long> Vector;
typedef vector<Pair> PairVector;

const int N = 1e4 + 5;
const Long INF = 1e18;
const Double EPS = 10e-9;

Long n;
Long acc[N];
Pair trips[N];
bool done[N][6];
Long dp[N][6];
vector<Long> desc = {1, 2, 4, 4, 4, 4};

// DP(pos, prev) : minima costo de realizar un trip con los
// eventos [pos ... n] sabiendo que el anterior es el
// prev-esimo de una oferta
Long DP(Long pos, Long prev) {
	if (pos > n) return 0;
	if (done[pos][prev]) return dp[pos][prev];
	Long current = ((prev == 0) ? 0 : (acc[pos - 1] - acc[pos - prev - 1]));
	if (current >= 120LL) {
		dp[pos][prev] = trips[pos].second + DP(pos + 1, 1);
	} else {
		// Reinicio el descuento
		dp[pos][prev] = trips[pos].second + DP(pos + 1, 1);
		// Si no reinicio
		dp[pos][prev] = min(dp[pos][prev], trips[pos].second / desc[prev] + DP(pos + 1, ((prev == 5) ? 0 : prev + 1)));
	}
	done[pos][prev] = true;
	return dp[pos][prev];
}

void solve() {
	cin >> n;
	trips[0] = {0, 0};
	For(i, 1, n + 1) cin >> trips[i].first >> trips[i].second;
	For(i, 1, n + 1) trips[i].second *= 4;
	acc[0] = 0;
	For(i, 1, n + 1) acc[i] = acc[i - 1] + trips[i].first;
	Long ans = DP(1, 0);
	Double min_cost = ((Double) ans) / 4;
	cout << fixed << setprecision(2) << min_cost << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}