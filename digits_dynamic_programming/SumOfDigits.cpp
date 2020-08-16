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

const Long N = 19;
const Long INF = 1e18;
const Double EPS = 10e-9;

Pair dp[N][2];
bool used[N][2];

deque<Long> s;

Pair DP(Long pos, bool lower) {
	if (pos == s.size()) {
		return {1, 0};
	}
	if (used[pos][lower]) return dp[pos][lower];
	dp[pos][lower] = {0, 0};
	if (lower) {
		For(digit, 0, 10) {
			Pair next = DP(pos + 1, true);
			dp[pos][lower].first += next.first;
			dp[pos][lower].second += (digit * next.first + next.second);
		}
	} else {
		For(digit, 0, s[pos]) {
			Pair next = DP(pos + 1, true);
			dp[pos][lower].first += next.first;
			dp[pos][lower].second += (digit * next.first + next.second);
		}
		Pair next = DP(pos + 1, false);
		dp[pos][lower].first += next.first;
		dp[pos][lower].second += (s[pos] * next.first + next.second);
	}
	used[pos][lower] = true;
	return dp[pos][lower];
}

void clear() {
	For(i, 0, N) {
		For(j, 0, 2) {
			used[i][j] = false;
		}
	}
}

Long count(Long n) {
	if (n <= 0) return 0;
	s.clear();
	For(i, 0, N) {
		Long digit = n % 10;
		s.push_front(digit);
		n /= 10;
	}
	clear();
	return DP(0, false).second;
}

void solve(Long a, Long b) {
	Long ans = count(b) - count(a - 1);
	cout << ans << endl;
}

int main() {
	fastio;
	Long a, b;
	while (cin >> a >> b) {
		if (a == -1 and b == -1) break;
		solve(a, b);
	}
	return 0;
}