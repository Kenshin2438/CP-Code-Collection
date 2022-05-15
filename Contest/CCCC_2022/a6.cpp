#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);
  str a, b; cin >> a >> b;
  str s1 = "", s2 = "";
  for (int i = 1; i < (int) a.size(); i++) {
    if (a[i] % 2 == a[i - 1] % 2) {
      s1 += max(a[i], a[i - 1]);
    }
  }
  for (int i = 1; i < (int) b.size(); i++) {
    if (b[i] % 2 == b[i - 1] % 2) {
      s2 += max(b[i], b[i - 1]);
    }
  }
  if (s1 == s2) cout << s1 << '\n';
  else cout << s1 << '\n' << s2 << '\n';
  return 0;
}
