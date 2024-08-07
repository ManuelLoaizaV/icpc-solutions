// https://open.kattis.com/problems/natjecanje
#include <iostream>
#include <vector>
using namespace std;

int GetCompetingTeams(int bitmask, int n_teams, vector<bool> is_damaged, vector<bool> has_backup) {
    for (int i = 0; i < n_teams; i++) {
        if (!has_backup[i]) continue;
        bool left = (bitmask >> i) & 1;
        if (left && i > 0) {
            is_damaged[i - 1] = false;
        }
        if (!left && i < n_teams - 1) {
            is_damaged[i + 1] = false;
        }
    }

    int competing_teams = 0;
    for (int i = 0; i < n_teams; i++) {
        if (!is_damaged[i]) {
            competing_teams++;
        }
    }
    return competing_teams;
}

int main(void) {
    int n_teams;
    int n_damaged_teams;
    int n_backups;
    cin >> n_teams >> n_damaged_teams >> n_backups;

    vector<bool> is_damaged(n_teams, false);
    for (int i = 0; i < n_damaged_teams; i++) {
        int j;
        cin >> j;
        is_damaged[j - 1] = true;
    }

    vector<bool> has_backup(n_teams, false);
    for (int i = 0; i < n_backups; i++) {
        int j;
        cin >> j;
        has_backup[j - 1] = true;
    }

    for (int i = 0; i < n_teams; i++) {
        if (is_damaged[i] && has_backup[i]) {
            has_backup[i] = false;
            is_damaged[i] = false;
        }
    }

    int max_competing_teams = 0;
    const int MASKS = 1 << n_teams;
    for (int mask = 0; mask < MASKS; mask++) {
        int competing_teams = GetCompetingTeams(mask, n_teams, is_damaged, has_backup);
        max_competing_teams = max(max_competing_teams, competing_teams);
    }

    cout << n_teams - max_competing_teams << endl;
    return 0;
}