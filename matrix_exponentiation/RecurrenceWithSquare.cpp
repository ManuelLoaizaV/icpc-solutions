// https://codeforces.com/gym/102644/problem/G
#include <bits/stdc++.h>
using namespace std;

// Modular integer for automatic mod operations.
// This version of inv() requires the modulus M to be prime.
template<long long M>
struct Mint {
  long long v;
  Mint() { v = 0LL; }
  // Normalizes any value into range [0, M).
  Mint(long long _v) {
    v = (-M < _v && _v < M) ? _v : _v % M;
    if (v < 0) v += M; // Ensure non-negative value
  }
  explicit operator long long() const { return v; }
  friend bool operator==(const Mint &a, const Mint &b) { return a.v == b.v; }
  friend bool operator!=(const Mint &a, const Mint &b) { return !(a == b); }
  friend bool operator<(const Mint &a, const Mint &b) { return a.v < b.v; }
  Mint &operator+=(const Mint &m) { if ((v += m.v) >= M) v -= M; return *this; }
  Mint &operator-=(const Mint &m) { if ((v -= m.v) < 0) v += M; return *this; }
  Mint &operator*=(const Mint &m) { v = v * m.v % M; return *this; }
  Mint &operator/=(const Mint &m) { return (*this) *= inv(m); }
  Mint operator-() const { return Mint(-v); }
  Mint &operator++() { return *this += 1; }
  Mint &operator--() { return *this -= 1; }
  Mint operator++(int) { Mint old = *this; ++*this; return old; }
  Mint operator--(int) { Mint old = *this; --*this; return old; }
  friend Mint operator+(Mint a, const Mint &b) { return a += b; }
  friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
  friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
  friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
  // Returns a^n % M. Time complexity: O(lg n).
  friend Mint pow(Mint a, long long n) { Mint p = 1LL; for (; n > 0LL; n >>= 1LL, a *= a) if (n & 1LL) p *= a; return p; }
  // Returns modular inverse via Fermat's little theorem. Time complexity: O(lg M).
  // If M is composite, gcd(a.v,M)==1 and replace this with extended Euclidean algorithm.
  friend Mint inv(const Mint &a) { assert(a.v != 0LL); return pow(a, M - 2LL); }
  friend ostream &operator<<(ostream &os, const Mint &m) { return os << m.v; }
  friend istream &operator>>(istream &is, Mint &m) { long long x; is >> x; m = Mint(x); return is; }
};
using mint = Mint<1000000007LL>;
// using mint = Mint<998244353LL>;

template <typename T>
struct Matrix {
  size_t rows, columns;
  vector<vector<T>> matrix;

  // Initializes a new zero matrix M_{r x c}
  // or square identity matrix I_r if identity=true.
  Matrix(size_t r, size_t c, bool identity = false)
    : rows(r), columns(c), matrix(r, vector<T>(c, T(0))) {
    if (identity) {
      assert(r == c);
      for (int i = 0; i < r; i++) matrix[i][i] = T(1);
    }
  }
  vector<T>& operator[](size_t i) { return matrix[i]; }
  const vector<T>& operator[](size_t i) const { return matrix[i]; }

  // Returns matrix multiplication Q_{r x p} = M_{r x c} * N_{c x p}.
  // Time complexity: O(r*c*p).
  Matrix operator*(const Matrix& other) const {
    assert(columns == other.rows);
    Matrix result(rows, other.columns);
    for (int i = 0; i < rows; i++)
      for (int k = 0; k < columns; k++)
        for (int j = 0; j < other.columns; j++)
          result[i][j] += matrix[i][k] * other[k][j];
    return result;
  }

  // Returns matrix-vector multiplication v'=M*v.
  // Useful for applying transition matrix to recurrence states.
  // Time complexity: O(r*c).
  vector<T> operator*(const vector<T>& v) const {
    assert(columns == v.size());
    vector<T> result(rows, T(0));
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        result[i] += matrix[i][j] * v[j];
    return result;
  }

  // Computes M^n via binary exponentiation.
  // Time complexity: O(r^3 lg n).
  friend Matrix<T> pow(Matrix<T> M, long long n) {
    assert(M.rows == M.columns);
    Matrix<T> result(M.rows, M.rows, true);
    for (; n > 0; n >>= 1, M = M * M)
      if (n & 1) result = result * M;
    return result;
  }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long N, K;
    cin >> N >> K;
    
    vector<mint> a(N + 3);
    for (int i = 0; i < N; i++) {
        cin >> a[N - 1 - i];
    }
    a[N] = N * N;
    a[N + 1] = N;
    a[N + 2] = 1LL;

    Matrix<mint> t(N + 3, N + 3);
    for (int i = 0; i < N; i++) {
        cin >> t[0][i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> t[0][N + 2 - i];
    }

    for (int i = 0; i < N - 1; i++) {
        t[i + 1][i] = 1LL;
    }

    t[N][N] = 1LL; t[N][N + 1] = 2LL; t[N][N + 2] = 1LL;
    t[N + 1][N + 1] = 1LL; t[N + 1][N + 2] = 1LL;
    t[N + 2][N + 2] = 1LL;

    if (K < N) {
        cout << a[N - 1LL - K] << endl;
        return 0;
    }

    long long steps{K - (N - 1LL)};
    auto result = pow(t, steps) * a;
    cout << result[0] << endl;
    return 0;
}