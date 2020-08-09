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

const int N = 55;
const int T = 1005;
const Long INF = 1e15;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long total, n;
Long t[N];
bool done[N][T];
Long dp[N][T];
vector<Long> sequence;

void clear(Long n, Long total) {
	For(i, 0, n) {
		For(j, 0, total + 1) {
			done[i][j] = false;
		}
	}
	sequence.clear();
}

Long DP(Long pos, Long sobra) {
	if (sobra < 0) return -INF;
	if (pos == n) return 0;
	if (done[pos][sobra]) return dp[pos][sobra];
	dp[pos][sobra] = max(DP(pos + 1, sobra), t[pos] + DP(pos + 1, sobra - t[pos]));
	done[pos][sobra] = true;
	return dp[pos][sobra];
}

void rec(Long pos, Long sobra) {
	if (sobra < 0) return;
	if (pos == n) return;
	sequence.push_back(pos);
	For(next, pos + 1, n) {
		if (t[next] + DP(next + 1, sobra - t[next]) == DP(next, sobra)) {
			rec(next, sobra - t[next]);
			return;
		}
	}
}

void solve() {
	while (cin >> total) {
		if (total == 0) break;
		cin >> n;
		clear(n, total);
		For(i, 0, n) cin >> t[i];
		Long maxi = DP(0, total);
		For(i, 0, n) {
			if (t[i] + DP(i + 1, total - t[i]) == maxi) {
				rec(i, total - t[i]);
				break;
			}
		}
		Long sz = sequence.size();
		For(i, 0, sz) {
			if (i > 0) cout << " ";
			cout << t[sequence[i]];
		}
		cout << " " << maxi << endl;
	}
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}