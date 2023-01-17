#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n; cin >> n;
  int ans = 0;

  vector<long long> pre;
  for (int i = 0; i < n; i++) {
    long long H; cin >> H;
    vector<long long> now;
    for (bool has = false; H != 1; ) {
      now.push_back(H);
      has |= binary_search(pre.rbegin(), pre.rend(), H);
      ans += (has == false);
      H = sqrt(H / 2 + 1);
    }
    pre = move(now);
  }
  
  cout << ans << '\n';
  return 0;
}