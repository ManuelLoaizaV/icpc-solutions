// https://codeforces.com/contest/1902/problem/E
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const Long INF = 1e18;
const char ENDL = '\n';

const int N = 1e6 + 1;  // total de caracteres + 1
const int ALPHABET = 26;
const int C = (int)'a';
map<char, int> trie[N];
Long terminals[N];
Long lenghts_sums[N];
Long terminals_in_subtree[N];
Long lengths_sums_in_subtree[N];

int nodes = 1;

void AddWord(const string& s) {
  Long n = s.size();
  int u = 0;
  for (int i = 0; i < n; i++) {
    if (trie[u].count(s[i]) == 0) trie[u][s[i]] = nodes++;
    u = trie[u][s[i]];
  }
  terminals[u]++;
  lenghts_sums[u] += n;
}

void DFS(int u) {
  terminals_in_subtree[u] += terminals[u];
  lengths_sums_in_subtree[u] += lenghts_sums[u];
  for (pair<char, int> p : trie[u]) {
    int v = p.second;
    DFS(v);
    terminals_in_subtree[u] += terminals_in_subtree[v];
    lengths_sums_in_subtree[u] += lengths_sums_in_subtree[v];
  }
}

Long NotChildCollapse(const int node, const char child, const Long prefix_size, const Long word_size) {
  // C(word, words end in here)
  Long collapse = (word_size - prefix_size) * terminals[node];

  // C(word, divergent words)
  Long n_divergent_words = terminals_in_subtree[node] - terminals[node];
  Long divergent_words_lengths_sum = lengths_sums_in_subtree[node] - lenghts_sums[node];
  if (trie[node].count(child) > 0) {
    n_divergent_words -= terminals_in_subtree[trie[node][child]];
    divergent_words_lengths_sum -= lengths_sums_in_subtree[trie[node][child]];
  }
  collapse += divergent_words_lengths_sum - n_divergent_words * prefix_size + n_divergent_words * (word_size - prefix_size);

  return collapse;
}

Long Collapse(const string& s) {
  Long collapse = 0LL;
  Long n = (Long)s.size();
  int u = 0;
  for (Long i = 0; i < n; i++) {
    collapse += NotChildCollapse(u, s[i], i, n);
    if (trie[u].count(s[i]) == 0) return collapse;
    u = trie[u][s[i]];
  }
  collapse += NotChildCollapse(u, '#', n, n);
  return collapse;
}

void Solve(void) {
  Long n;
  cin >> n;
  vector<string> words(n);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
    AddWord(words[i]);
    reverse(words[i].begin(), words[i].end());
  }
  DFS(0);
  Long ans = 0LL;
  for (int i = 0; i < n; i++) {
    ans += Collapse(words[i]);
  }
  cout << ans << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}