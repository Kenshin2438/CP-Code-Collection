#include <bits/stdc++.h>
using namespace std;

#define vec vector
typedef long long ll;

int main() {
  vec<int> a(6);
  for (int &x : a) cin >> x;
  int n; cin >> n;
  for (int i = 0; i < 6; i++) {
    int b = 6;
    if (6 - n + 1 > a[i]) b = 6 - n + 1;
    else b = 6 - n;
    cout << b << " \n"[i + 1 == 6];
  }
  return 0;
}
