#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
array<vi, 2> manacher(const string& s) {
	int n = sz(s);
	array<vi,2> p = {vi(n+1), vi(n)};
	rep(z,0,2) for (int i=0,l=0,r=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  for (int n; cin >> n; ) {
    string s; cin >> s;
    auto [p, q] = manacher(s);

    vector<int> d(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      d[i + 1] += 1, d[i + p[i] + 1] -= 1;
    }
    for (int i = 0; i < n; i++) {
      d[i + 1] += 1, d[i + 1 + q[i] + 1] -= 1;
    }

    for (int i = 1; i <= n; i++) {
      d[i] += d[i - 1];
    }
    ll k = 0, f = 0, c = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == 'k') k += d[i + 1];
      if (s[i] == 'f') f += d[i + 1];
      if (s[i] == 'c') c += d[i + 1];
    }
    cout << k << ' ' << f << ' ' << c << '\n';
  }

  return 0;
}
