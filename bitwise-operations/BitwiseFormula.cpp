// https://codeforces.com/problemset/problem/778/B
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

const string UNKNOWN = "?";
const string ASSIGNMENT = ":=";
const string AND = "AND";
const string OR = "OR";
const string XOR = "XOR";

const char ZERO = '0';
const char ONE = '1';

const int UNKNOWN_INDEX = -1;
const int CONST_INDEX = -2;

bool IsNumeric(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int CharToInt(const char c) {
    return c - ZERO;
}

int GetTokenIndex(const string& s, unordered_map<string, int>& indexes) {
    if (s == UNKNOWN) return UNKNOWN_INDEX;
    if (IsNumeric(s)) return CONST_INDEX;
    return indexes[s];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_assignments, n_bits;
    cin >> n_assignments >> n_bits;

    vector<tuple<string, string>> expressions;
    unordered_map<string, int> indexes;
    vector<vector<string>> lines;

    // Parse the input
    for (int i = 0; i < n_assignments; i++) {
        string line;
        if (i == 0) getline(cin, line);
        getline(cin, line);
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        // Create the hash for the current variable being modified
        indexes[tokens[0]] = i;
        lines.push_back(tokens);
    }

    // Create a hashed version of the input
    // [left_id, right_id]
    vector<vector<int>> expression_indexes(n_assignments, vector<int>(2));
    for (int i = 0; i < n_assignments; i++) {
        expression_indexes[i][0] = GetTokenIndex(lines[i][2], indexes);
        if ((int)lines[i].size() > 3) {
            lines[i][1] = lines[i][3];
            expression_indexes[i][1] = GetTokenIndex(lines[i][4], indexes);
        }
    }

    // Solve the problem for each bit

    string min_for_min, min_for_max;

    for (int bit = 0; bit < n_bits; bit++) {
        vector<int> ones(2, 0);
        for (int value = 0; value < 2; value++) {
            vector<int> values(n_assignments, 0);
            for (int assignment = 0; assignment < n_assignments; assignment++) {
                if (expression_indexes[assignment][0] == UNKNOWN_INDEX) {
                    values[assignment] = value;
                } else if (expression_indexes[assignment][0] == CONST_INDEX) {
                    values[assignment] = CharToInt(lines[assignment][2][bit]);
                } else {
                    values[assignment] = CharToInt(values[expression_indexes[assignment][0]]);
                }
                if (lines[assignment][1] != ASSIGNMENT) {
                    int other_value;
                    if (expression_indexes[assignment][1] == UNKNOWN_INDEX) {
                        other_value = value;
                    } else if (expression_indexes[assignment][1] == CONST_INDEX) {
                        other_value = CharToInt(lines[assignment][4][bit]);
                    } else {
                        other_value = CharToInt(values[expression_indexes[assignment][1]]);
                    }
                    if (lines[assignment][1] == AND) {
                        values[assignment] &= other_value;
                    } else if (lines[assignment][1] == OR) {
                        values[assignment] |= other_value;
                    } else if (lines[assignment][1] == XOR) {
                        values[assignment] ^= other_value;
                    }
                }
                ones[value] += values[assignment];
            }
        }
        if (ones[0] < ones[1]) {
            min_for_min += ZERO;
            min_for_max += ONE;
        }
        if (ones[0] == ones[1]) {
            min_for_min += ZERO;
            min_for_max += ZERO;
        }
        if (ones[0] > ones[1]) {
            min_for_min += ONE;
            min_for_max += ZERO;
        }
    }

    cout << min_for_min << '\n';
    cout << min_for_max << '\n';
    return 0;
}