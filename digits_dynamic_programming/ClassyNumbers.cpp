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

const int N = 19;
const Long INF = 1e18;
const Double EPS = 10e-9;

Long dp[N][2][3];
bool used[N][2][4];
deque<Long> s;

Long DP(Long pos, bool lower, Long acc) {
	if (acc == 4) return 0LL;
	if (pos == s.size()) return 1LL;
	if (used[pos][lower][acc]) return dp[pos][lower][acc];
	Long& ans = dp[pos][lower][acc];
	ans = 0;
	if (lower) {
		For(digit, 0, 10) ans += DP(pos + 1, true, (digit == 0) ? acc : (acc + 1));
	} else {
		For(digit, 0, s[pos]) ans += DP(pos + 1, true, (digit == 0) ? acc : (acc + 1));
		ans += DP(pos + 1, false, (s[pos] == 0) ? acc : (acc + 1));
	}
	used[pos][lower][acc] = true;
	return ans;
}

void clear() {
	For(i, 0, N) {
		For(j, 0, 2) {
			For(k, 0, 4) {
				used[i][j][k] = false;
			}
		}
	}
}

Long count(Long n) {
	if (n < 0) return 0;
	s.clear();
	For(i, 0, N) {
		Long digit = n % 10;
		s.push_front(digit);
		n /= 10;
	}
	clear();
	return DP(0, false, 0);
}

void solve() {
	Long left, right;
	cin >> left >> right;
	Long ans = count(right) - count(left - 1);
	cout << ans << endl;
}

int main() {
	fastio;
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}