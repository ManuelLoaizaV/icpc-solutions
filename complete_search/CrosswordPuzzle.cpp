//https://www.hackerrank.com/challenges/crossword-puzzle/problem
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 10;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

string crossword[N];
vector<string> words;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool IsInside(const int& i, const int& j, const int& k, const int& len) {
  int x, y;
  x = i;
  y = j;
  if (k < 2) {
    x += dx[k] * len;
    if (k == 0) {
      x--;
    } else {
      x++;
    }
  } else {
    y += dy[k] * len;
    if (k == 2) {
      y--;
    } else {
      y++;
    }
  }
  return 0 <= x && x < N && 0 <= y && y < N;
}

void Backtracking(int pos) {
  if (pos == words.size()) {
    for (int i = 0; i < N; i++) cout << crossword[i] << '\n';
    exit(0);
  } else {
    // Longitud de la palabra actual
    int len = words[pos].size();
    // Busco los casilleros con '-'
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        // Si es que el casillero actual esta disponible
        if (crossword[i][j] == '-' || crossword[i][j] == words[pos][0]) {
          // Intento moverme en las cuatro direcciones
          for (int k = 0; k < 4; k++) {
            // Chequeo de que no me vaya a salir en dicha direccion
            if (IsInside(i, j, k, len)) {
              // Voy colocando las fichas en esa direccion y guardo quienes use
              vector<pair<int, int>> used;
              bool is_valid = true;
              for (int l = 0; l < len; l++) {
                int x = i + l * dx[k];
                int y = j + l * dy[k];
                if (crossword[x][y] == '-') {
                  crossword[x][y] = words[pos][l];
                  used.push_back({x, y});
                } else if (crossword[x][y] == '+' || crossword[x][y] != words[pos][l]) {
                    is_valid = false;
                    break;
                }
              }
              if (is_valid) Backtracking(pos + 1);
              // Limpio lo que he utilizado
              for (auto p : used) crossword[p.first][p.second] = '-';
            }
          }
        }
      }
    }
  }
}

void Solve(void) {
  for (int i = 0; i < N; i++) cin >> crossword[i];
  string line;
  getline(cin, line);
  getline(cin, line);
  for (int i = 0; i < line.size(); i++) if (line[i] == ';') line[i] = ' ';
  stringstream ss(line);
  string word;
  while (ss >> word) words.push_back(word);
  Backtracking(0);
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}

