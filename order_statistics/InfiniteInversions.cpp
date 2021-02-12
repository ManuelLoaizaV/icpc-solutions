//https://codeforces.com/problemset/problem/540/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long Long;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;
// find_by_order(k): Returns an iterator to the k-th largest element (0 indexed).
// order_of_key(k): Returns the number of items that are stricly smaller than k.

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long n;
  cin >> n;
  vector<pair<int, int>> q;
  set<int> uni;
  for (int i = 0; i < n; i++) {
    int l, r;
    cin >> l >> r;
    q.push_back({l, r});
    uni.insert(l);
    uni.insert(r);
  }
  int sz = 0;
  map<int, int> pos_to_ind;
  map<int, int> ind_to_pos;
  for (auto it : uni) {
    pos_to_ind[it] = sz;
    ind_to_pos[sz] = it;
    sz++;
  }
  vector<int> a(sz);
  for (int i = 0; i < sz; i++) a[i] = ind_to_pos[i];
  for (int i = 0; i < n; i++) {
    swap(a[pos_to_ind[q[i].first]], a[pos_to_ind[q[i].second]]);
  }
  Long ans = 0;
  // I want to count three things
  // 1. How many untouched numbers to my right are less than me
  // 2. How many untouched numbers to my left are greater than me
  // 3. How many used numbers to my left are greater than me
  OST touched_right, touched_left;
  for (int i = 0; i < sz - 1; i++) touched_left.insert(a[i]);
  for (int i = sz - 1; i >= 0; i--) {
    int pos = ind_to_pos[i];
    if (a[i] != pos) {
      // Sumo todos los elementos originales que deberian estar en el rango
      ans += abs(a[i] - pos) - 1;
      if (a[i] > pos) {
        // Si es que estoy en una posicion mas baja
        // Resto cuandos son menores que yo que estan tocados
        ans -= touched_right.order_of_key(a[i]);
        ans -= touched_left.order_of_key(a[i]);
        ans += touched_right.order_of_key(pos + 1);
        ans += touched_left.order_of_key(pos + 1);
      } else {
        // Si es que estoy en una posicion mas alta
        // Resto cuantos son menores que mi posicion actual que estan tocados
        ans -= touched_right.order_of_key(pos);
        ans -= touched_left.order_of_key(pos);
        ans += touched_right.order_of_key(a[i] + 1);
        ans += touched_left.order_of_key(a[i] + 1);
      }
    }
    // Analizo los tocados a mi izquierda
    ans += ((int)(touched_left.size()) - touched_left.order_of_key(a[i] + 1));
    // Actualizo los elementos tocados
    touched_left.erase(a[i]);
    touched_right.insert(a[i]);
  }
  cout << ans << '\n';
  return 0;
}
