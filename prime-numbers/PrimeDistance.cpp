// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1081
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 463040;
const int RANGE_SIZE = 1000002;
const pair<int, int> EMPTY = make_pair(-1, -1);
bool is_prime[RANGE_SIZE + 1];
vector<Long> primes;

void Sieve(Long n) {
  for (int i = 0; i <= n; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;
  for (Long i = 2; i * i <= n; i++) {
    for (Long j = i * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }
  for (int i = 0; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
}

bool EqualSign(Long a, Long b) { return a > 0 && b > 0 || a < 0 && b < 0; }

Long FloorDiv(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (EqualSign(a, b)) return abs(a) / abs(b);
  return (-1LL) * (1LL + (abs(a) - 1) / abs(b));
}

Long CeilDiv(Long a, Long b) {
  assert(b != 0);
  if (a == 0) return 0;
  if (a % b == 0) return a / b;
  if (!EqualSign(a, b)) return (-1LL) * (abs(a) / abs(b));
  return 1LL + (abs(a) - 1LL) / abs(b);
}

void SegmentedSieve(Long l, Long r) {
  int len = r - l + 1;
  for (int i = 0; i < len; i++) is_prime[i] = true;
  if (l == 1) is_prime[0] = false;
  for (Long prime : primes) {
    const Long square = prime * prime;
    if (square > r) break;
    for (Long composite = max(square, CeilDiv(l, prime) * prime);
         composite <= r; composite += prime) {
      is_prime[composite - l] = false;
    }
  }
}

int Distance(pair<int, int> ordered_pair) {
  return ordered_pair.second - ordered_pair.first;
}

void Solve(int l, int r) {
  SegmentedSieve(l, r);
  pair<int, int> last_two_primes = EMPTY;
  pair<int, int> closest_adjacent_primes = EMPTY;
  pair<int, int> farthest_adjacent_primes = EMPTY;
  for (Long i = l; i <= r; i++) {
    if (is_prime[i - l]) {
      last_two_primes.first = last_two_primes.second;
      last_two_primes.second = i;
      if (last_two_primes.first != -1) {
        if (Distance(closest_adjacent_primes) == 0) {
          closest_adjacent_primes = last_two_primes;
          farthest_adjacent_primes = last_two_primes;
        } else {
          int last_distance = Distance(last_two_primes);
          if (last_distance < Distance(closest_adjacent_primes)) {
            closest_adjacent_primes = last_two_primes;
          }
          if (last_distance > Distance(farthest_adjacent_primes)) {
            farthest_adjacent_primes = last_two_primes;
          }
        }
      }
    }
  }
  if (last_two_primes.first == -1) {
    cout << "There are no adjacent primes." << endl;
  } else {
    cout << closest_adjacent_primes.first << ","
         << closest_adjacent_primes.second << " are closest, "
         << farthest_adjacent_primes.first << ","
         << farthest_adjacent_primes.second << " are most distant." << endl;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(N);
  Long l, r;
  while (cin >> l >> r) Solve(l, r);
  return 0;
}