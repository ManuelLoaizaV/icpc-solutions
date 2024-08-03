#include <iostream>
using namespace std;

int main(void) {
	int n;
	cin >> n;
	int missing_number = n;
	for (int i = 1; i < n; i++) {
		int x;
		cin >> x;
		missing_number ^= x ^ i;
	}
	cout << missing_number << endl;
	return 0;
}
