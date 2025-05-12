// https://open.kattis.com/problems/settlers2
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <utility>
#include <vector>

const int N = 10000;

std::vector<int> resources;
std::map<std::pair<int, int>, int> grid;
std::vector<int> frequencies(6, 0);
std::vector<std::pair<int, int>> movements{
    {1, 1}, {0, 2}, {-1, 1},
    {-1, -1}, {0, -2}, {1, -1}
};

std::pair<int, int> Move(
    std::pair<int, int> cur,
    std::pair<int, int> move,
    int steps
) {
    for (int i = 0; i < steps; ++i) {
        cur.first += move.first;
        cur.second += move.second;

        std::set<int> candidates{1, 2, 3, 4, 5};
        for (const auto& m : movements) {
            std::pair<int, int> neighbor{cur.first + m.first, cur.second + m.second};
            if (!grid.contains(neighbor)) continue;
            if (candidates.contains(grid[neighbor])) candidates.erase(grid[neighbor]);
        }
        
        if (candidates.size() > 1) {
            int mn = std::numeric_limits<int>::max();
            for (const auto& candidate : candidates) {
                mn = std::min(mn, frequencies[candidate]);
            }
            for (int candidate = 1; candidate <= 5; ++candidate) {
                if (candidates.contains(candidate) && frequencies[candidate] > mn) {
                    candidates.erase(candidate);
                }
            }
        }

        int value = *candidates.begin();
        grid[cur] = value;
        frequencies[value]++;
        resources.push_back(value);
    }
    return cur;
}

int main(void) {
    std::pair<int, int> position{0, 0};

    grid[position] = 1;
    frequencies[0] = std::numeric_limits<int>::max();
    frequencies[1] = 1;
    resources.push_back(1);

    int len = 1;
    while (grid.size() < N) {
        position = Move(position, movements[0], len);
        position = Move(position, movements[1], len - 1);
        position = Move(position, movements[2], len);
        position = Move(position, movements[3], len);
        position = Move(position, movements[4], len);
        position = Move(position, movements[5], len);
        ++len;
    }

    int T;
    std::cin >> T;
    for (int t = 0; t < T; ++t) {
        int i;
        std::cin >> i;
        --i;
        std::cout << resources[i] << std::endl;
    }
    return 0;
}