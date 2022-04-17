// https://open.kattis.com/problems/pathtracing
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

struct Punto {
  int x, y;
  Punto(void) {}
  Punto(int _x, int _y) : x(_x), y(_y) {}
  Punto operator+(const Punto& other) {
    return Punto(x + other.x, y + other.y);
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  map<string, Punto> maps;
  maps["up"] = Punto(-1, 0);
  maps["down"] = Punto(1, 0);
  maps["left"] = Punto(0, -1);
  maps["right"] = Punto(0, 1);
  vector<Punto> directions;
  string aux;
  while (cin >> aux) directions.push_back(maps[aux]);
  Punto cur(0, 0);
  int n = (int)directions.size();
  int lower_row, upper_row, lower_col, upper_col;
  lower_row = upper_row = lower_col = upper_col = 0;
  for (int i = 0; i < n; i++) {
    cur = cur + directions[i];
    lower_row = min(lower_row, cur.x);
    upper_row = max(upper_row, cur.x);
    lower_col = min(lower_col, cur.y);
    upper_col = max(upper_col, cur.y);
  }
  int w = upper_col - lower_col + 1;
  int h = upper_row - lower_row + 1;
  vector<vector<char>> grid(h + 2, vector<char>(w + 2, ' '));
  for (int i = 0; i < w + 2; i++) {
    grid[0][i] = grid[h + 1][i] = '#';
  }
  for (int i = 0; i < h + 2; i++) {
    grid[i][0] = grid[i][w + 1] = '#';
  }
  Punto mark(1 - lower_row, 1 - lower_col);
  Punto start, end;
  start = mark;
  for (int i = 0; i < n; i++) {
    mark = mark + directions[i];
    grid[mark.x][mark.y] = '*';
    if (i == n - 1) {
      end = mark;
    }
  }
  grid[start.x][start.y] = 'S';
  grid[end.x][end.y] = 'E';
  for (int i = 0; i < h + 2; i++) {
    for (int j = 0; j < w + 2; j++) {
      cout << grid[i][j];
    }
    cout << '\n';
  }
  return 0;
}