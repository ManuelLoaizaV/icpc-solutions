// https://open.kattis.com/problems/faktor
#include <iostream>
using namespace std;

typedef long long Long;

int main(void) {
    Long n_articles, target_factor;
    cin >> n_articles >> target_factor;
    Long n_citations = 1;
    while (true) {
        Long factor = (n_citations + n_articles - 1) / n_articles;
        if (factor == target_factor) {
            cout << n_citations << endl;
            break;
        }
        n_citations++;
    }
    return 0;
}