#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 4e6;
const Long B[2] = {29LL, 31LL};
const Long MOD = 1e9 + 7;
Long P[N][2];

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

struct Hash {
  Long h[N][2];
  void Initialize(const string& s) {
    int n = s.size();
    h[0][0] = h[0][1] = s[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        h[i][j] = Add(Mul(h[i - 1][j], B[j]), s[i] - 'a' + 1);
      }
    }
  }
  Pair Query(int l, int r) {
    vector<Long> ans(2);
    for (int j = 0; j < 2; j++) {
      if (l == 0) {
        ans[j] = h[r][j];
      } else {
        ans[j] = Sub(h[r][j], Mul(h[l - 1][j], P[r - l + 1][j]));
      }
    }
    return {ans[0], ans[1]};
  }
};

void Precalculate(int n) {
  P[0][0] = P[0][1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      P[i][j] = Mul(P[i - 1][j], B[j]);
    }
  }
}

Pair GetHash(const string& s) {
  vector<Long> ans(2);
  int n = s.size();
  ans[0] = ans[1] = s[0] - 'a' + 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      ans[j] = Add(Mul(ans[j], B[j]), s[i] - 'a' + 1);
    }
  }
  return {ans[0], ans[1]};
}

int main(void) {
  FAST_IO;
  Long n, k;
  cin >> n >> k;
  string cd;
  cin >> cd;

  Precalculate(2 * n * k);
  cd += cd;
  Hash hash_cd;
  hash_cd.Initialize(cd);

  int g;
  cin >> g;
  map<Pair, int> popular;
  for (int i = 0; i < g; i++) {
    string game;
    cin >> game;
    popular[GetHash(game)] = i + 1;
  }

  for (int i = 0; i < k; i++) {
    Long cnt = 0;
    map<Pair, int> freq;
    multiset<int> mx;
    queue<Pair> tmp;

    for (int j = 0; j < 2 * n; j++) {
      if (j >= n) {
        Pair cur = tmp.front();
        tmp.pop();
        if (popular.count(cur) > 0) {
          auto it = mx.find(freq[cur]);
          mx.erase(it);
          int new_freq = --freq[cur];
          mx.insert(new_freq);
          
          if (new_freq == 1) {
            cnt++;
          } else if (new_freq == 0) {
            cnt--;
          }
        }
      }
      
      int ini = j * k + i;
      int fin = ini + k - 1;
      Pair cur = hash_cd.Query(ini, fin);
      tmp.push(cur);

      if (popular.count(cur) > 0) {
        if (freq.count(cur) == 0) {
          freq[cur] = 0;
          mx.insert(0);
        }
        
        auto it = mx.find(freq[cur]);
        mx.erase(it);
        int new_freq = ++freq[cur];
        mx.insert(new_freq);

        if (new_freq == 1) {
          cnt++;
        } else if (new_freq == 2) {
          cnt--;
        }
      }
      
      if (cnt == n) {
        cout << "YES" << '\n';
        for (int l = 0; l < n; l++) {
          int pos = l * k + i;
          cout << popular[hash_cd.Query(pos, pos + k - 1)] << " ";
        }
        cout << '\n';
        return 0;
      }
    }
  }
  cout << "NO" << '\n';
  return 0;
}
