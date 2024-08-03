// https://open.kattis.com/problems/babelfish
#include <iostream>
#include <map>
#include <sstream>
using namespace std;

int main(void) {
    map<string, string> dict;
    string line;
    while (getline(cin, line)) {
        if (line == "") break;
        stringstream ss(line);
        string to, from;
        ss >> to >> from;
        dict[from] = to;
    }
    while (getline(cin, line)) {
        if (!dict.contains(line)) {
            cout << "eh" << endl;
        } else {
            cout << dict[line] << endl;
        }
    }
    return 0;
}