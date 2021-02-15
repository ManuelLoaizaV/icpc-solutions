#include <iostream>
#include <deque>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const int N = 2000;

Long m, d;
int len;
deque<int> num;
Long dp[N][N][2];

Long Sum(Long a, Long b) {
  return (a + b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Long DP(int pos, Long mod, bool is_lower) {
  if (pos == len) {
    if (mod == 0) return 1;
    return 0;
  }
  if (is_done[pos][mod][is_lower]) return dp[pos][mod][is_lower];
  Long& memo = dp[pos][mod][is_lower];
  if (is_lower) {
    for (int digit = 0; digit < 10; digit++) {
      if (cur_pos & 1) {
      } else {
      }
    }
  } else {
    for (int digit = 0; digit < num[pos]; digit++) {
      if (cur_pos & 1) {
      } else {
      }
    }
    if (cur_pos & 1) {
    } else {
    }
  }
  is_done[pos][mod][is_lower] = true;
  return memo;
}

void Clear(void) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 2; k++) {
        is_done[i][j][k] = false;
      }
    }
  }
}

Long Count(string n) {
  num.clear();
  for (int i = 0; i < len; i++) {
    int digit = n[len - 1 - i] - '0';
    num.push_front(digit);
  }
  Clear();
  return DP(0, 0, false);
}

int main(void) {
  FAST_IO;
  cin >> m >> d;
  string a, b;
  cin >> a >> b;

  len = a.size();
  power[len - 1] = 1LL;
  for (int i = 1; i < len; i++) {
    power[len - 1 - i] = (power[len - i] * 10LL) % m;
  }

  Long ans = Sum(Sub(Count(a), Count(b)), Check(b));
  cout << ans << '\n';
  return 0;
}
