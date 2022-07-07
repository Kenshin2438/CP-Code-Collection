#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  while (cin >> n) {
    if (n == 0) break;

    vector<ll> h(n), l(n), r(n);
    for (ll &x : h) cin >> x;

    {
      stack<ll> stk;
      for (int i = 0; i < n; i++) {
        while (!stk.empty() && h[stk.top()] >= h[i]) {
          stk.pop();
        }
        if (stk.empty()) {
          l[i] = 0;
        } else {
          l[i] = stk.top() + 1;
        }
        stk.push(i);
      }
    }
    {
      stack<ll> stk;
      for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && h[stk.top()] >= h[i]) {
          stk.pop();
        }
        if (stk.empty()) {
          r[i] = n - 1;
        } else {
          r[i] = stk.top() - 1;
        }
        stk.push(i);
      }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans = max(ans, h[i] * (r[i] - l[i] + 1));
    }
    cout << ans << '\n'; 
  }  
  return 0;
}