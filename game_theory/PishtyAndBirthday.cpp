#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int N = 1e5;
const int M = 1 << 16;
bool done[M];
int dp[M];

struct SegmentTree {
  int tree[4 * N];
  void build(int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = 0;
    } else {
      int tm = (tl + tr) / 2;
      build(2 * id, tl, tm);
      build(2 * id + 1, tm + 1, tr);
      tree[id] = tree[2 * id] ^ tree[2 * id + 1];
    }
  }
  void update(int pos, int val, int id, int tl, int tr) {
    if (tl == tr) {
      tree[id] = val;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) update(pos, val, 2 * id, tl, tm);
      else update(pos, val, 2 * id + 1, tm + 1, tr);
      tree[id] = tree[2 * id] ^ tree[2 * id + 1];
    }
  }
  int query(int l, int r, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id];
    int tm = (tl + tr) / 2;
    if (r <= tm) return query(l, r, 2 * id, tl, tm);
    if (tm < l) return query(l, r, 2 * id + 1, tm + 1, tr);
    return query(l, r, 2 * id, tl, tm) ^ query(l, r, 2 * id + 1, tm + 1, tr);
  }
} st;

int get_bit(int mask, int bit) {
  return ((mask >> bit) & 1);
}

void turn_on(int& mask, int bit) {
  mask = mask | (1 << bit);
}

void turn_off(int& mask, int bit) {
  mask = mask & (~(1 << bit));
}

int Mex(vector<int>& v) {
  int n = v.size();
  vector<bool> marked(n, false);
  for (int x : v) if (x < n) marked[x] = true;
  for (int x = 0; x < n; x++) if (!marked[x]) return x;
  return n;
}

vector<vector<int>> IntToMatrix(int n) {
  vector<vector<int>> m(4, vector<int> (4));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int bit = 15 - (4 * i + j);
      m[i][j] = get_bit(n, bit);
    }
  }
  return m;
}

int MatrixToInt(vector<vector<int>>& m) {
  int n = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int bit = 15 - (4 * i + j);
      if (m[i][j]) turn_on(n, bit);
    }
  }
  return n;
}

vector<vector<int>> StringToMatrix(string s[4]) {
  vector<vector<int>> m(4, vector<int> (4));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m[i][j] = s[i][j] - '0';
    }
  }
  return m;
}

int Grundy(int pos) {
  if (pos == 0) return 0;
  if (done[pos]) return dp[pos];
  vector<vector<int>> m = IntToMatrix(pos);
  vector<vector<int>> aux;
  vector<int> moves;
  // Para cada esquina superior izquierda
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // Para cada esquina inferior derecha
      for (int k = i; k < 4; k++) {
        for (int l = j; l < 4; l++) {
          // Contabilizo unos
          int cnt = 0;
          for (int x = i; x <= k; x++) {
            for (int y = j; y <= l; y++) {
              if (m[x][y]) cnt++;
            }
          }
          // Analizo existencia
          int area = (k - i + 1) * (l - j + 1);
          if (area == cnt) {
            aux = m;
            // Apago las velas en el nuevo rectangulo
            for (int x = i; x <= k; x++) {
              for (int y = j; y <= l; y++) {
                aux[x][y] = 0;
              }
            }
            // Nueva posicion
            int next_pos = MatrixToInt(aux);
            moves.push_back(next_pos);
          }
        }
      }
    }
  }
  vector<int> g;
  for (int move : moves) g.push_back(Grundy(move));
  done[pos] = true;
  return dp[pos] = Mex(g);
}

void Solve() {
  int n, q;
  cin >> n >> q;
  st.build(1, 0, n - 1);
  vector<vector<int>> m(4, vector<int> (4));
  string s[4];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 4; j++) cin >> s[j];
    m = StringToMatrix(s);
    int h = MatrixToInt(m);
    st.update(i, Grundy(h), 1, 0, n - 1);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      if (st.query(l, r, 1, 0, n - 1)) cout << "Pishty" << '\n';
      else cout << "Lotsy" << '\n';
    } else {
      int pos;
      cin >> pos;
      pos--;
      for (int j = 0; j < 4; j++) cin >> s[j];
      m = StringToMatrix(s);
      int h = MatrixToInt(m);
      st.update(pos, Grundy(h), 1, 0, n - 1);
    }
  }
}

int main() {
  FAST_IO;
  for (int i = 0; i < M; i++) Grundy(i);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
