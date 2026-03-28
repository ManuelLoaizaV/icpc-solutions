#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int ROWS = 10;
const int COLS = 12;
const int COUPLES = 4;
const int MASKS = 1<<12;
const long long MOD = 1000000007LL;

namespace Mask {
    using Long = int;
    bool Get(Long& m, int b) { return (m >> b) & 1LL; }
    void On(Long &m, int b) { m |= (1LL << b); }
    void Off(Long& m, int b) { m &= ~(1LL << b); }
    void Set(Long& m, int b, bool v) { v ? On(m, b) : Off(m, b); }
    void Flip(Long& m, int b) { m ^= (1LL << b); }
    int Highest(unsigned m) { return m == 0 ? -1 : 31 - __builtin_clz(m); }
  }

struct Mint {
    using Long = long long;
    Long v; // Holds the value of the modular integer
    explicit operator Long() const { return v; }
    // Constructors
    Mint() { v = 0; }
    Mint(Long _v) {
      // Modulo operation to keep value in range [-MOD, MOD)
      v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
      if (v < 0) v += MOD; // Ensure non-negative value
    }
    // Comparison operators
    friend bool operator==(const Mint &a, const Mint &b) { return a.v == b.v; }
    friend bool operator!=(const Mint &a, const Mint &b) { return !(a == b); }
    friend bool operator<(const Mint &a, const Mint &b) { return a.v < b.v; }
    // Arithmetic operators
    Mint &operator+=(const Mint &m) {
      if ((v += m.v) >= MOD) v -= MOD;
      return *this;
    }
    Mint &operator-=(const Mint &m) {
      if ((v -= m.v) < 0) v += MOD;
      return *this;
    }
    Mint &operator*=(const Mint &m) {
      v = v * m.v % MOD;
      return *this;
    }
    Mint &operator/=(const Mint &m) { return (*this) *= inv(m); }
    // Utility functions
    friend Mint pow(Mint a, Long p) {
      Mint ans = 1;
      assert(p >= 0);
      for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
      return ans;
    }
    friend Mint inv(const Mint &a) {
      assert(a.v != 0);
      return pow(a, MOD - 2);
    }
    Mint operator-() const { return Mint(-v); }
    Mint &operator++() { return *this += 1; }
    Mint &operator--() { return *this -= 1; }
    Mint operator++(int) {
      v++;
      if (v == MOD) v = 0;
      return Mint(v);
    }
    Mint operator--(int) {
      v--;
      if (v < 0) v = MOD - 1;
      return Mint(v);
    }
    // Binary arithmetic operators
    friend Mint operator+(Mint a, const Mint &b) { return a += b; }
    friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
    // Stream insertion and extraction operators
    friend std::ostream &operator<<(std::ostream &os, const Mint &m) {
      os << m.v;
      return os;
    }
    friend std::istream &operator>>(std::istream &is, Mint &m) {
      Long x;
      is >> x;
      m.v = x;
      return is;
    }
};

int rows, cols;
bool free_seats[ROWS][COLS];
Mint memo[ROWS][COLS][MASKS][COUPLES + 1][COUPLES + 1];
bool done[ROWS][COLS][MASKS][COUPLES + 1][COUPLES + 1];

Mint DP(int i, int j, int p, long long k, long long r) {
    std::cout << "[" << i << " " << j << " " << p << " " << k << " " << r << "]" << std::endl;
    if (i == rows) {
        if (k == 0LL && r == 0LL) {
            std::cout << "BASED" << std::endl;
            return Mint(1LL);
        }
        return Mint(0LL);
    }
    if (done[i][j][p][k][r]) return memo[i][j][p][k][r];
    
    int next_i = i;
    int next_j = j + 1;
    if (next_j == cols) {
        ++next_i;
        next_j = 0;
    }

    int p_on = p;
    Mask::On(p_on, j);
    int p_off = p;
    Mask::Off(p_off, j);

    // Case skip current seat
    memo[i][j][p][k][r] = DP(next_i, next_j, p_off, k, r);

    if (free_seats[i][j]) {
        // Case using someone from a new couple
        if (k > 0) {
            memo[i][j][p][k][r] += k * DP(next_i, next_j, p_on, k - 1, r + 1);
        }
        // Case using someone whose couple has already been used
        if (r > 0) {
            long long cnt{0LL};
            if (Mask::Get(p, j)) ++cnt;
            if (j > 0 && Mask::Get(p, j - 1)) ++cnt;
            memo[i][j][p][k][r] += std::max(0LL, r - cnt) * DP(next_i, next_j, p_off, k, r - 1);
        }
    }

    done[i][j][p][k][r] = true;
    return memo[i][j][p][k][r];
}

void Initialize(int K) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int P = 1<<j;
            for (int p = 0; p < P; ++p) {
                for (int k = 0; k <= K; ++k) {
                    for (int r = 0; r <= K; ++r) {
                        done[i][j][p][k][r] = false;
                        memo[i][j][p][k][r] = Mint(0LL);
                    }
                }
            }
        }
    }
}

void Solve(void) {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::string> seats(n);
    for (auto& seat: seats) std::cin >> seat;

    rows = std::max(n, m);
    cols = std::min(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool is_free = seats[i][j] == '.';
            if (n < m) {
                free_seats[j][i] = is_free;
            } else {
                free_seats[i][j] = is_free;
            }
        }
    }
    seats.clear();
    Initialize(k);
    Mint ways = DP(0, 0, 0, k, 0) * pow(Mint(2LL), k);
    std::cout << ways << std::endl;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) Solve();
    return 0;
}
