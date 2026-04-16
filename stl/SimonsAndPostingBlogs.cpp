// https://codeforces.com/contest/2205/problem/C
#include <bits/stdc++.h>
using namespace std;

void Solve(void) {
    int n;
    cin >> n;
    vector<vector<int>> blogs;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        stack<int> s;
        for (int i = 0; i < m; i++) {
            int a;
            cin >> a;
            s.push(a);
        }
        set<int> found;
        vector<int> blog;
        while (!s.empty()) {
            int a = s.top();
            s.pop();
            if (!found.contains(a)) {
                blog.push_back(a);
                found.insert(a);
            }
        }
        blogs.push_back(blog);
    }

    unordered_set<int> printed;
    while (!blogs.empty()) {
        sort(blogs.begin(), blogs.end());
        for (int e : blogs[0]) {
            cout << e << " ";
            printed.insert(e);
        }

        vector<vector<int>> new_blogs;
        for (int i = 1; i < blogs.size(); i++) {
            vector<int> new_blog;
            for (int e : blogs[i]) {
                if (!printed.contains(e)) {
                    new_blog.push_back(e);
                }
            }
            if (!new_blog.empty()) {
                new_blogs.push_back(new_blog);
            }
        }
        blogs = new_blogs;
    }
    cout << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) Solve();
    return 0;
}