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

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

void solve() {
	Long n;
	cin >> n;
	Long a[n];
	For(i, 0, n) cin >> a[i];
	Long pref[n], suff[n];
	pref[0] = suff[n - 1] = 1;
	For(i, 1, n) {
		if (a[i] > a[i - 1]) pref[i] = pref[i - 1] + 1;
		else pref[i] = 1;
	}
	roF(i, n - 2, 0) {
		if (a[i] < a[i + 1]) suff[i] = suff[i + 1] + 1;
		else suff[i] = 1;
	}
	Long maxi = 0;
	For(i, 0, n) maxi = max(maxi, pref[i]);
	For(i, 0, n) maxi = max(maxi, suff[i]);
	For(i, 1, n - 1) {
		if (a[i - 1] < a[i + 1]) {
			Long temp = pref[i - 1] + suff[i + 1];
			maxi = max(maxi, temp);
		}
	}
	cout << maxi << endl;
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}