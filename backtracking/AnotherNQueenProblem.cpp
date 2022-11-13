// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2136
#include <bits/stdc++.h>
using namespace std;

const int N = 15;

int cnt;
string board[N];
bool used_cols[N];
bool used_r_d_diags[2 * N - 1];
bool used_r_u_diags[2 * N - 1];

void Backtrack(int i, int n) {
  if (i == n) {
    cnt++;
    return;
  }
  for (int j = 0; j < n; j++) {
    int r_d_diag = i + j;
    int r_u_diag = i - j + n - 1;
    if (board[i][j] == '*' || used_cols[j] || used_r_d_diags[r_d_diag] || used_r_u_diags[r_u_diag]) continue;

    used_cols[j] = true;
    used_r_d_diags[r_d_diag] = true;
    used_r_u_diags[r_u_diag] = true;

    Backtrack(i + 1, n);

    used_cols[j] = false;
    used_r_d_diags[r_d_diag] = false;
    used_r_u_diags[r_u_diag] = false;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  int test_case = 0;
  while (cin >> n) {
    if (n == 0) break;
    test_case++;
    cout << "Case " << test_case << ": ";
    cnt = 0;
    for (int i = 0; i < n; i++) cin >> board[i];
    Backtrack(0, n);
    cout << cnt << '\n';
  }
  return 0;
}
