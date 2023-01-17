#include <iostream>
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  long long a, b, n; 
  cin >> a >> b >> n;
  long long ans = n / (5 * a + 2 * b) * 7;
  n %= (5 * a + 2 * b);

  if (n >= 5 * a) {
    ans += 5;
    n -= 5 * a;
    ans += (n + b - 1) / b; 
  } else {
    ans += (n + a - 1) / a; // 上取整的一种写法
  }

  cout << ans << '\n';  
  return 0;
}