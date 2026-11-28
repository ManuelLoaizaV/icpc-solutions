// https://coj.157-180-26-18.sslip.io/24h/problems/3091
// 3091 - Harry Potter contra los brujos
#include <bits/stdc++.h>
#include <cassert>

#ifndef ONLINE_JUDGE
#define debug(x) cerr << "[" << #x << "]: " << x << endl
#else
#define debug(x) 69
#endif

using namespace std;

typedef long long Long;
typedef long double Double;

const Double PI = acos(-1);
const Double EPS = 1e-9;
const string YES = "YES";
const string NO = "NO";
const char ENDL = '\n';

void Solve(void) {
    int N;
    Long P;
    cin >> N >> P;
    vector<Long> poderes(N);
    for (auto& e : poderes) cin >> e;

    int n_izquierda = N / 2;
    int n_derecha = N - N / 2;

    vector<Long> sumas_derecha;
    for (int mask = 0; mask < (1 << n_derecha); mask++) {
        Long suma = 0LL;
        for (int i = 0; i < n_derecha; i++) {
            if ((mask >> i) & 1) {
                suma += poderes[n_izquierda + i];
            }
        }
        sumas_derecha.push_back(suma);
    }
    sort(sumas_derecha.begin(), sumas_derecha.end());

    Long cnt = 0LL;
    for (int mask = 0; mask < (1 << n_izquierda); mask++) {
        Long suma = 0LL;
        for (int i = 0; i < n_izquierda; i++) {
            if ((mask >> i) & 1) {
                suma += poderes[i];
            }
        }
        Long max_restante = P - suma;
        Long cumplen = upper_bound(sumas_derecha.begin(), sumas_derecha.end(), max_restante) - sumas_derecha.begin();
        cnt += cumplen;
    }
    cnt--;  // quitamos el conjunto con cero brujos ya que siempre cumple pero es inválido
    cout << cnt << endl;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}