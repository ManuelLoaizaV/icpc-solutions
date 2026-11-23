// https://codeforces.com/contest/2/problem/A
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;



int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;

    map<string, int> name_to_id;
    vector<int> standings;
    vector<string> names;
    vector<vector<pair<int, int>>> history;
    for (int i = 0; i < n; i++) {
        string name;
        int points;
        cin >> name >> points;
        if (name_to_id.count(name) == 0) {
            name_to_id[name] = (int)standings.size();
            standings.push_back(0);
            names.push_back(name);
            history.push_back({});
        }
        standings[name_to_id[name]] += points;
        history[name_to_id[name]].emplace_back(i, standings[name_to_id[name]]);
    }

    int max_score = INT_MIN;
    for (int score : standings) {
        max_score = max(max_score, score);
    }

    vector<int> max_ids;
    for (int i = 0; i < standings.size(); i++) {
        if (standings[i] == max_score) {
            max_ids.push_back(i);
        }
    }

    if (max_ids.size() == 1) {
        cout << names[max_ids.back()] << endl;
        return 0;
    }

    int oldest_round = n + 1;
    int winner_id = -1;
    for (int candidate_id : max_ids) {
        for (auto [round, score] : history[candidate_id]) {
            if (score >= max_score && round < oldest_round) {
                oldest_round = round;
                winner_id = candidate_id;
                break;
            }
        }
    }

    cout << names[winner_id] << endl;
    return 0;
}