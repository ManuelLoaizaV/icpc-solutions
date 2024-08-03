// https://open.kattis.com/problems/securedoors
#include <iostream>
#include <set>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    set<string> people;
    while (n--) {
        string action, who;
        cin >> action >> who;
        cout << who;
        bool ok = true;
        if (action == "entry") {
            cout << " entered";
            if (people.contains(who)) {
                ok = false;
            } else {
                people.insert(who);
            }
        } else {
            cout << " exited";
            if (people.contains(who)) {
                people.erase(who);
            } else {
                ok = false;
            }
        }
        if (!ok) {
            cout << " (ANOMALY)";
        }
        cout << endl;
    }
    return 0;
}