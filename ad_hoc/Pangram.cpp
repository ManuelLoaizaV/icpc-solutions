// https://codeforces.com/contest/520/problem/A
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26;
const int A = (int)'a';

int main(void) {
	int n;
	cin >> n;
	string s;
	cin >> s;
	vector<bool> found(ALPHABET_SIZE, false);
	for (char c : s) {
		found[tolower(c) - A] = true;
	}

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (!found[i]) {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0;
}
