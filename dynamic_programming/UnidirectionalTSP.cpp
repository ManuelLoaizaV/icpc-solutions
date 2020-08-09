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

const int N = 105;
const Long INF = 1e12;
const Double EPS = 10e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long weight[N][N];
bool done[N][N];
Long dp[N][N];
Long n, m;
vector<Long> sequence;

void clear(Long n, Long m) {
    For(i, 0, n) {
        For(j, 0, m) {
            done[i][j] = false;
        }
    }
    sequence.clear();
}

Long DP(Long row, Long col) {
    if (col == m) return 0;
    if (done[row][col]) return dp[row][col];
    dp[row][col] = INF;
    For(i, -1, 2) {
        Long to = (row + i + n) % n;
        dp[row][col] = min(dp[row][col], weight[row][col] + DP(to, col + 1));
    }
    done[row][col] = true;
    return dp[row][col];
}

void rec(Long row, Long col) {
    if (col == m) return;
    sequence.push_back(row + 1);
    vector<Long> options = {(row - 1 + n) % n, row, (row + 1) % n};
    sort(all(options));
    For(i, 0, 3) {
        if (weight[row][col] + DP(options[i], col + 1) == DP(row, col)) {
            rec(options[i], col + 1);
            return;
        }
    }
}

void solve() {
    while (cin >> n >> m) {
        clear(n, m);
        For(i, 0, n) For(j, 0, m) cin >> weight[i][j];
        Long mini = INF;
        For(i, 0, n) mini = min(mini, DP(i, 0));
        For(i, 0, n) {
            if (DP(i, 0) == mini) {
                rec(i, 0);
                break;
            }
        }
        For(i, 0, m) {
            if (i > 0) cout << " ";
            cout << sequence[i];
        }
        cout << endl;
        cout << mini << endl;
    }
}

int main() {
	fastio;
	int t = 1;
	//cin >> t;
	while (t--) solve();
	return 0;
}