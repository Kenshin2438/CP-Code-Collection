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

/**
1
9
2 8 4 1 1 4 4 4 4

rrrlllrrr

2 8 4 1 1 4 4 4 4

2
2 8
2 8 4
1 2 8 4
1 1 2 8 4 -> 2 2 8 4 -> 4 8 4
4 4 8 4 -> 8 8 4 -> 16 4
16 4 4 -> 16 8
16 8 4
16 8 4 4 -> 16 8 8 -> 16 16 -> 32
**/

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<int> b(n);
  for (int &x : b) cin >> x;

  bool ans = true;
  deque<int> q;
  str s = "";
  for (int x : b) {
    if (q.empty()) {
      s += "r";
      q.push_back(x);
    } else {
      if (q.front() == x) {
        s += "l";
        int cur = x;
        while (not q.empty() and q.front() == cur) {
          q.pop_front(), cur *= 2;
        }
        q.push_front(cur);
      } else if (q.back() == x) {
        s += "r";
        int cur = x;
        while (not q.empty() and q.back() == cur) {
          q.pop_back(), cur *= 2;
        }
        q.push_back(cur);
      } else {
        int dl = q.front() - x;
        int dr = q.back()  - x;
        if (dl < 0 && dr < 0) {
          if (is_sorted(all(q))) {
            s += "r";
            q.push_back(x);
          } else {
            ans = false; break;
          }
        }
        if (dl < 0 && dr > 0) {
          s += "r";
          int cur = x;
          while (not q.empty() and q.back() == cur) {
            q.pop_back(), cur *= 2;
          }
          q.push_back(cur);
        }
        if (dr < 0 && dl > 0) {
          s += "l";
          int cur = x;
          while (not q.empty() and q.front() == cur) {
            q.pop_front(), cur *= 2;
          }
          q.push_front(cur);
        }
        if (dl > 0 && dr > 0) {
          if (dl < dr) {
            s += "l";
            int cur = x;
            while (not q.empty() and q.front() == cur) {
              q.pop_front(), cur *= 2;
            }
            q.push_front(cur);
          } else {
            s += "r";
            int cur = x;
            while (not q.empty() and q.back() == cur) {
              q.pop_back(), cur *= 2;
            }
            q.push_back(cur);
          }
        }
      }
    }
  }
  if (ans and q.size() == 1) cout << s << '\n';
  else cout << "no\n";
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
