// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=515
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

vector<pair<int, int>> Compress(const vector<int>& numbers) {
  vector<int> copy = numbers;
  int n = (int)copy.size();
  sort(copy.begin(), copy.end());
  reverse(copy.begin(), copy.end());
  int freq = 1;
  vector<pair<int, int>> result;
  for (int i = 1; i <= n; i++) {
    if (i == n || copy[i - 1] != copy[i]) {
      result.push_back({copy[i - 1], freq});
      freq = 1;
    } else {
      freq++;
    }
  }
  return result;
}

bool found;
vector<pair<int, int>> numbers_frequencies;
vector<int> solution;

void Backtrack(int i, int n, int target) {
  if (target == 0) {
    int len = (int)solution.size();
    for (int j = 0; j < len; j++) {
      if (j > 0) cout << "+";
      cout << solution[j];
    }
    cout << '\n';
    found = true;
    return;
  }
  if (target < 0 || i == n) return;
  int num = numbers_frequencies[i].first;
  int freq = numbers_frequencies[i].second;
  for (int j = 0; j < freq; j++) {
    solution.push_back(num);
    target -= num;
  }
  for (int j = 0; j < freq; j++) {
    Backtrack(i + 1, n, target);
    solution.pop_back();
    target += num;
  }
  Backtrack(i + 1, n, target);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int target, n;
  while (cin >> target >> n) {
    if (target == 0 && n == 0) break;
    
    found = false;
    
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) cin >> numbers[i];

    numbers_frequencies = Compress(numbers);
    int len = (int)numbers_frequencies.size();
    cout << "Sums of " << target << ":" << '\n';
    Backtrack(0, len, target);
    if (!found) cout << "NONE" << '\n';
  }
  return 0;
}
