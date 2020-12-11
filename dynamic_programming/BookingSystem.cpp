#include <algorithm>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef pair<int, int> Pair;

const int N = 1e3;

struct Client {
  int cnt, p, ind;
  bool operator < (const Client& other) const {
    return (cnt > other.cnt);
  }
} client[N];

struct Table {
  int cnt, ind;
  bool operator < (const Table& other) const {
    return (cnt > other.cnt);
  }
} table[N];

int n, k;
bool is_done[N][N];
int dp[N][N];

int DP(int pos_client, int pos_table) {
  if (pos_client == n) return 0;
  if (pos_table == k) return 0;
  if (is_done[pos_client][pos_table]) return dp[pos_client][pos_table];
  dp[pos_client][pos_table] = DP(pos_client + 1, pos_table);
  if (client[pos_client].cnt <= table[pos_table].cnt)
    dp[pos_client][pos_table] = max(dp[pos_client][pos_table], client[pos_client].p + DP(pos_client + 1, pos_table + 1));
  is_done[pos_client][pos_table] = true;
  return dp[pos_client][pos_table];
}

vector<Pair> ans;

void Reconstruct(int pos_client, int pos_table) {
  if (pos_client == n) return;
  if (pos_table == k) return;
  if (client[pos_client].cnt <= table[pos_table].cnt &&
      client[pos_client].p + DP(pos_client + 1, pos_table + 1) == DP(pos_client, pos_table)) {
    ans.push_back({client[pos_client].ind + 1, table[pos_table].ind + 1});
    Reconstruct(pos_client + 1, pos_table + 1);
    return;
  }
  Reconstruct(pos_client + 1, pos_table);
}

int main(void) {
  FAST_IO;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> client[i].cnt >> client[i].p;
    client[i].ind = i;
  }
  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> table[i].cnt;
    table[i].ind = i;
  }
  sort(client, client + n);
  sort(table, table + k);
  int sum = DP(0, 0);
  if (sum == 0) {
    cout << "0 0" << '\n';
    return 0;
  }
  Reconstruct(0, 0);
  int len = ans.size();
  cout << len << " " << sum << '\n';
  for (int i = 0; i < len; i++) cout << ans[i].first << " " << ans[i].second << '\n';
  return 0;
}
