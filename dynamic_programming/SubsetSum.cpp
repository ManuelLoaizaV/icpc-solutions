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

const int N = 1e2;
const int SUM = 1e5;
const Long INF = 1e18;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

bool done[SUM + 1][N + 1];
bool dp[SUM + 1][N + 1];
Long a[N], n;

Long DP(Long sum, Long pos) {
    if (sum < 0) return false;
    if (sum == 0) return true;
    if (pos == n) {
        if (sum == 0) return true;
        else return false;
    }
    if (done[sum][pos]) return dp[sum][pos];
    dp[sum][pos] = DP(sum, pos + 1) or DP(sum - a[pos], pos + 1);
    done[sum][pos] = true;
    return dp[sum][pos];
}

void solve() {
    Long sum;
    cin >> n;
    For(i, 0, n) cin >> a[i];
    sum = 0;
    For(i, 0, n) sum += a[i];
    For(i, 0, sum + 1) For(j, 0, n) done[i][j] = dp[i][j] = false;
    Long ans = 0;
    For(i, 0, sum + 1) if (DP(i, 0)) ans += i;
    cout << ans << endl;
    /*
    // Solucion iterativa
    roF(pos, n - 1, 0) {
        For(suma, 0, sum + 1) {
            if (suma >= a[pos]) {
                dp[sum][pos] = dp[sum][pos + 1] or dp[sum - a[pos]][pos + 1];
            } else {
                dp[sum][pos] = dp[sum][pos + 1];
            }
        }
    }
    */
}

int main() {
	fastio;
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}