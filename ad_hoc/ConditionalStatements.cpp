// https://www.hackerrank.com/challenges/c-tutorial-conditional-if-else/problem
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    long long n;
    cin >> n;
    string message;
    if (n == 1) {
        message = "one";
    } else if (n == 2) {
        message = "two";
    } else if (n == 3) {
        message = "three";
    } else if (n == 4) {
        message = "four";
    } else if (n == 5) {
        message = "five";
    } else if (n == 6) {
        message = "six";
    } else if (n == 7) {
        message = "seven";
    } else if (n == 8) {
        message = "eight";
    } else if (n == 9) {
        message = "nine";
    } else {
        message = "Greater than 9";
    }
    cout << message << endl;
    return 0;
}