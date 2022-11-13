// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=227
#include <bits/stdc++.h>
using namespace std;

const int N = 5;
bool edges[N + 1][N + 1];
bool used[N + 1][N + 1];

const int E = 8;
int solution[E + 1];

void Backtrack(int last_node, int n_edges) {
  solution[n_edges] = last_node;
  if (n_edges == E) {
    for (int i = 0; i <= E; i++) {
      cout << solution[i];
    }
    cout << '\n';
    return;
  }
  for (int next_node = 1; next_node <= N; next_node++) {
    if (used[last_node][next_node] || !edges[last_node][next_node]) continue;
    
    used[last_node][next_node] = true;
    used[next_node][last_node] = true;
    
    Backtrack(next_node, n_edges + 1);
    
    used[last_node][next_node] = false;
    used[next_node][last_node] = false;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  edges[2][3] = edges[3][2] = true;
  edges[3][5] = edges[5][3] = true;
  edges[2][5] = edges[5][2] = true;
  edges[1][2] = edges[2][1] = true;
  edges[1][3] = edges[3][1] = true;
  edges[3][4] = edges[4][3] = true;
  edges[4][5] = edges[5][4] = true;
  edges[1][5] = edges[5][1] = true;

  Backtrack(1, 0);
  return 0;
}
