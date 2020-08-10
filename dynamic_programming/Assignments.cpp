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

const int N = 20;
const int MASK = 1 << 20;
const Long INF = 1e18;
const Double EPS = 10e-9;

Long n;
bool likes[N][N];
Long dp[N][MASK];
bool done[N][MASK];

Long get_bit(Long mask, Long bit) {
	return (mask >> bit) & 1LL;
}

void turn_on(Long& mask, Long bit) {
	mask = mask | (1LL << bit);
}

void turn_off(Long& mask, Long bit) {
	mask = mask & (~(1 << bit));
}

void clear(Long n) {
	Long lim = 1 << n;
	For(i, 0, n) For(j, 0, lim) done[i][j] = false;
}

// DP(pos, mask) : cantidad de maneras de distribuir las asignaturas
// entre los alumnos [pos ... n - 1] habiendo utilizado los cursos con 1 en mask
Long DP(Long pos, Long mask) {
	if (pos == n) return 1LL;
	if (done[pos][mask]) return dp[pos][mask];
	dp[pos][mask] = 0;
	For(bit, 0, n) {
		if (get_bit(mask, bit) == 0 and likes[pos][bit]) {
			Long new_mask = mask;
			turn_on(new_mask, bit);
			dp[pos][mask] += DP(pos + 1, new_mask);
		}
	}
	done[pos][mask] = true;
	return dp[pos][mask];
}

void solve() {
	cin >> n;
	clear(n);
	For(i, 0, n) For(j, 0, n) cin >> likes[i][j];
	cout << DP(0, 0) << endl;
}

int main() {
	fastio;
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}