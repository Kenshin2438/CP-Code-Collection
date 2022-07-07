#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  ll ans = 0LL;
  priority_queue<int, vector<int>, greater<int> > pq;
  for (const int &x : a) {
    pq.push(x);
    if (not pq.empty() and pq.top() < x) {
      ans += x - pq.top();
      pq.pop(), pq.push(x);
    }
  }
  cout << ans << '\n';
  return 0;
}