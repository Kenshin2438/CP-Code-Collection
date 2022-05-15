#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  if (c >= a && d >= a) {
    cout << c << "-Y " << d << "-Y\n";
    cout << "huan ying ru guan\n";
    return 0;
  }
  if (c < a && d < a) {
    cout << c << "-N " << d << "-N\n";
    cout << "zhang da zai lai ba\n";
    return 0;
  }
  if (c < a && d >= b) {
    cout << c << "-Y " << d << "-Y\n";
    cout << "qing " << 2 << " zhao gu hao " << 1 << "\n";
    return 0;
  }
  if (d < a && c >= b) {
    cout << c << "-Y " << d << "-Y\n";
    cout << "qing " << 1 << " zhao gu hao " << 2 << "\n";
    return 0;
  }
  if (c < a && d >= a && d < b) {
    cout << c << "-N " << d << "-Y\n";
    cout << 2 << ": huan ying ru guan\n";
    return 0;
  }
  if (d < a && c >= a && c < b) {
    cout << c << "-Y " << d << "-N\n";
    cout << 1 << ": huan ying ru guan\n";
    return 0;
  }
  cout << c << "-N " << d << "-N\n";
  cout << "zhang da zai lai ba\n";
  return 0;
}
