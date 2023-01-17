#include <iostream>
#include <vector>
using namespace std;

const int mod = 1000000007;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int N; cin >> N;
  int na; cin >> na;
  vector<int> A(na);
  for (int i = na - 1; i >= 0; i--) {
    cin >> A[i];
  }
  int nb; cin >> nb;
  vector<int> B(max(na, nb));
  for (int i = nb - 1; i >= 0; i--) {
    cin >> B[i];
  }
  long long ans = 0, pre = 1;
  for (int i = 0; i < na; i++) {
    int base = max(2, max(A[i], B[i]) + 1);
    ans = (ans + (A[i] - B[i]) * pre % mod + mod) % mod;
    pre = pre * base % mod;
  }
  cout << ans << '\n';
  return 0;
}