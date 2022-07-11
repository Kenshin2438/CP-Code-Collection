#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const int LIM = 1e6 + 10;
bitset<LIM> isPrime;
vec<int> eratosthenes() {
  const int S = (int)round(sqrt(LIM)), R = LIM / 2;
  vec<int> pr = {2}, sieve(S + 1);
  pr.reserve(int(LIM / log(LIM) * 1.1));
  vec<PII> cp;
  for (int i = 3; i <= S; i += 2)
    if (!sieve[i]) {
      cp.push_back({i, i * i / 2});
      for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
    }
  bitset<S> block;
  for (int L = 1; L <= R; L += S) {
    block.reset();
    for (auto &[p, idx] : cp)
      for (int i = idx; i < S + L; idx = (i += p)) block[i - L] = 1;
    for (int i = 0; i < min(S, R - L); i++)
      if (!block[i]) pr.push_back((L + i) * 2 + 1);
  }
  for (int i : pr) isPrime[i] = 1;
  return pr;
}

void SingleTest(__attribute__((unused)) int TestCase) {
  cout << "Case " << TestCase << ": ";

  int x, y; cin >> x >> y;
  int K, w; cin >> K >> w;

  if (x == K || y == K) {
    return cout << "Bob" << '\n', void();
  }
  if (isPrime[x] && isPrime[y]) {
    return cout << "Alice" << '\n', void();
  }

  auto check = [&](int X, int Y) -> bool {
    // check if "Alice" wins when "Bob" first
    if (X == K || Y == K) return false;
    while (X > K && Y > K) {
      if (isPrime[X] && isPrime[Y]) return true;
      --X, --Y;
    }
    return false;
  };

  if (w == 0) { // Alice first
    cout << (check(x - 1, y) || check(x, y - 1) ? "Alice" : "Bob") << '\n';
  } else { // Bob first
    cout << (check(x, y) ? "Alice" : "Bob") << '\n';
  }
}

void init() {
  auto P = eratosthenes();
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
