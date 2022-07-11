#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  string s;
  cin >> s;

  vector<int> cnt(3, 0);
  for (const char &c : s) {
    if (c == '0') continue;
    cnt[(c & 15) % 3] ++;
  }

  int now = (cnt[1] + 2 * cnt[2]) % 3;
  if (cnt[0] + cnt[1] + cnt[2] == 1 || cnt[now] == 0) {
    return cout << "yukari\n", 0;
  }

  cnt[now] --;
  
  bool ans = false;

  if (cnt[0] == 0) {
    if (cnt[1] + cnt[2] == 1) ans = true;
    else {
      ans = false;
    }
  } else {
    if (cnt[1] == cnt[2]) ans = true;
    else ans = false;
  }

  cout << (ans ? "kou" : "yukari") << '\n';
  return 0;
}