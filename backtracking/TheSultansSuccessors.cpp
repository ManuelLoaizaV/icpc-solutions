// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=103
#include <bits/stdc++.h>
using namespace std;

const int N = 8;

int mx;
int sum;
int board[N][N];
bool used_cols[N];
bool used_r_d_diags[2 * N - 1];
bool used_r_u_diags[2 * N - 1];

void Backtrack(int i, int n) {
  if (i == n) {
    mx = max(mx, sum);
    return;
  }
  for (int j = 0; j < n; j++) {
    int r_d_diag = i + j;
    int r_u_diag = i - j + n - 1;
    if (used_cols[j] || used_r_d_diags[r_d_diag] || used_r_u_diags[r_u_diag]) continue;

    used_cols[j] = true;
    used_r_d_diags[r_d_diag] = true;
    used_r_u_diags[r_u_diag] = true;
    sum += board[i][j];

    Backtrack(i + 1, n);

    used_cols[j] = false;
    used_r_d_diags[r_d_diag] = false;
    used_r_u_diags[r_u_diag] = false;
    sum -= board[i][j];
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> board[i][j];
      }
    }
    mx = 0;
    Backtrack(0, N);
    cout << setw(5) << mx << '\n';
  }
  return 0;
}
