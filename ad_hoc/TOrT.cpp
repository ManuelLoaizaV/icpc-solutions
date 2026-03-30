#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int n, a, privado;
    cin >> n >> a >> privado;
    int tren = n * a;
    if (tren < privado) {
        cout << tren << endl;
    } else {
        cout << privado << endl;
    }
    return 0;   
}