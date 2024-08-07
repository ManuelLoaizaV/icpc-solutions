// https://open.kattis.com/problems/guessthedatastructure
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

void Solve(int n) {
    stack<int> s;
    bool might_be_stack = true;

    queue<int> q;
    bool might_be_queue = true;

    priority_queue<int> p;
    bool might_be_priority_queue = true;

    while (n--) {
        int command, element;
        cin >> command >> element;
        if (command == 1) {
            s.push(element);
            q.push(element);
            p.push(element);
        } else {
            if (might_be_queue) {
                if (!q.empty()) {
                    if (q.front() == element) {
                        q.pop();
                    } else {
                        might_be_queue = false;
                    }
                } else {
                    might_be_queue = false;
                }
            }
            if (might_be_stack) {
                if (!s.empty()) {
                    if (s.top() == element) {
                        s.pop();
                    } else {
                        might_be_stack = false;
                    }
                } else {
                    might_be_stack = false;
                }
            }
            if (might_be_priority_queue) {
                if (!p.empty()) {
                    if (p.top() == element) {
                        p.pop();
                    } else {
                        might_be_priority_queue = false;
                    }
                } else {
                    might_be_priority_queue = false;
                }
            }
        }
    }

    int cnt = might_be_queue + might_be_stack + might_be_priority_queue;
    if (cnt == 0) {
        cout << "impossible" << endl;
    } else if (cnt > 1) {
        cout << "not sure" << endl;
    } else if (might_be_queue) {
        cout << "queue" << endl;
    } else if (might_be_stack) {
        cout << "stack" << endl;
    } else {
        cout << "priority queue" << endl;
    }
}

int main(void) {
    int n;
    while (cin >> n) Solve(n);
    return 0;
}