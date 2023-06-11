// https://codeforces.com/problemset/problem/371/C
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long Long;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string recipe;
  cin >> recipe;

  map<char, int> indexes = {
    {'B', 0},
    {'S', 1},
    {'C', 2}
  };

  vector<Long> quantities(3, 0LL);
  for (char ingredient: recipe) {
    quantities[indexes[ingredient]]++;
  }

  vector<Long> kitchen(3);
  for (int i = 0; i < 3; i++) {
    cin >> kitchen[i];
  }

  vector<Long> prices(3);
  for (int i = 0; i < 3; i++) {
    cin >> prices[i];
  }

  Long money;
  cin >> money;
  Long l = 0;
  Long r = 10000000000000LL;
  while (r - l > 1) {
    Long m = (l + r) / 2;
    Long cost = 0;
    for (int i = 0; i < 3; i++) {
      cost += max(0LL, m * quantities[i] - kitchen[i]) * prices[i];
    }
    if (cost <= money) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << '\n';
  return 0;
}