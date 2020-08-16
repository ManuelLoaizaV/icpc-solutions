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

const int N = 54;
const Long INF = 1e18;
const Double EPS = 10e-9;

Pair dp[N][2];
bool used[N][2];
deque<Long> s;

Pair DP(Long pos, Long lower) {
	if (pos == s.size()) return {1LL, 0LL};
	if (used[pos][lower]) return dp[pos][lower];
	Pair& ans = dp[pos][lower];
	ans = {0, 0};
	if (lower) {
		For(digit, 0, 2) {
			Pair next = DP(pos + 1, true);
			ans.first += next.first;
			ans.second += (digit * next.first + next.second);
		}
	} else {
		For(digit, 0, s[pos]) {
			Pair next = DP(pos + 1, true);
			ans.first += next.first;
			ans.second += (digit * next.first + next.second);
		}
		Pair next = DP(pos + 1, false);
		ans.first += next.first;
		ans.second += (s[pos] * next.first + next.second);
	}
	used[pos][lower] = true;
	return ans;
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
		Long digit = n & 1LL;
		s.push_front(digit);
		n >>= 1LL;
	}
	clear();
	return DP(0, false).second;
}

void solve(Long left, Long right) {
	Long ans = count(right) - count(left - 1);
	cout << ans << endl;
}

int main() {
	fastio;
	Long left, right;
	while (cin >> left >> right) solve(left, right);
	return 0;
}