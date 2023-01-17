#include <iostream>
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    cout << max(2 * (n - i), 2 * (i - 1)) << '\n';
  }
  return 0;
}