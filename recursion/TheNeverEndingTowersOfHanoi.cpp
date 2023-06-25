// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=958
#include <iostream>
#include <vector>
using namespace std;

const int N_TOWERS = 3;
const int INDEXES_SUM = 3;
const char A = 'A';

vector<vector<int>> towers(N_TOWERS);
int max_n_moves;
int n_moves;

void PrintTowers(void) {
    for (int i = 0; i < N_TOWERS; i++) {
        char tower = (char)(A + i);
        cout << tower << "=>";
        if (!towers[i].empty()) cout << "  ";
        for (int disk : towers[i]) cout << " " << disk;
        cout << '\n';
    }
    cout << '\n';
}

void Move(int n_disks, int from, int to) {
    if (n_disks == 0) return;
    if (n_moves == max_n_moves) return;
    int aux = INDEXES_SUM - (from + to);
    Move(n_disks - 1, from, aux);
    if (n_moves == max_n_moves) return;
    int base = towers[from].back();
    towers[from].pop_back();
    towers[to].push_back(base);
    n_moves++;
    PrintTowers();
    if (n_moves == max_n_moves) return;
    Move(n_disks - 1, aux, to);
    if (n_moves == max_n_moves) return;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_disks;
    int n_problems = 0;
    while (cin >> n_disks >> max_n_moves) {
        if (n_disks == 0 && max_n_moves == 0) break;
        n_problems++;
        n_moves = 0;
        for (int i = 0; i < N_TOWERS; i++) towers[i].clear();
        for (int i = n_disks; i >= 1; i--) towers[0].push_back(i);
        cout << "Problem #" << n_problems << '\n';
        cout << '\n';
        PrintTowers();
        Move(n_disks, 0, N_TOWERS - 1);
    }
    return 0;
}