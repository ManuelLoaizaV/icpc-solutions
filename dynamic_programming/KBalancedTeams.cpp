//https://codeforces.com/problemset/problem/1133/E
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int C = 5;
const int N = 5e3;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

vector<Long> a;
vector<Long> cost;
Long dp[N][N + 1];
bool done[N][N + 1];

bool Check(int l, int r) {
	return ((a[r] - a[l]) <= C);
}

Long GetCost(int i) {
	int l = i;
	int r = (int) a.size() - 1;
	if (Check(i, r)) return r - i + 1;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (Check(i, m)) {
			l = m;
		} else {
			r = m;
		}
	}
	return l - i + 1;
}

Long DP(int pos, int rem) {
	if (rem == 0) return 0;
	if (pos == (int) a.size()) return 0;
	if (done[pos][rem]) return dp[pos][rem];
	dp[pos][rem] = max(DP(pos + 1, rem), cost[pos] + DP(pos + cost[pos], rem - 1));
	done[pos][rem] = true;
	return dp[pos][rem];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
	int n, k;
	cin >> n >> k;
	a = vector<Long>(n);
	cost = vector<Long>(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	sort(a.begin(), a.end());
	for (int i = 0; i < n; i++) {
		cost[i] = GetCost(i);
	}
	cout << DP(0, k) << '\n';
  return 0;
}
