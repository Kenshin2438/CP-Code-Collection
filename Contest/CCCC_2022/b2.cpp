#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string

#define all(x) (x).begin(), (x).end()

typedef long long ll;

const int N = (int) 1e3 + 10;

int n;

void out(int sh, int sm, int ss, int th, int tm, int ts) {
  if (sh == th && sm == tm && ss == ts) return;
  printf("%02d:%02d:%02d - ", sh, sm, ss);
  printf("%02d:%02d:%02d\n" , th, tm, ts);
}

int main() {
  // ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  vec<array<int, 6>> tim;
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    int sh, sm, ss, th, tm, ts;
    scanf("%d:%d:%d - %d:%d:%d", &sh, &sm, &ss, &th, &tm, &ts);
    tim.push_back({sh, sm, ss, th, tm, ts});
  }
  tim.push_back({0, 0, 0, 0, 0, 0});
  tim.push_back({23, 59, 59, 23, 59, 59});
  sort(all(tim));

  // for (auto a : tim) {
  //   for (auto x : a) cout << x << ' ';
  //   cout << '\n';
  // }

  n = tim.size();
  for (int i = 1; i < n; i++) {
    out(tim[i - 1][3],
        tim[i - 1][4],
        tim[i - 1][5],
        tim[i][0],
        tim[i][1],
        tim[i][2]
    );
  }
  return 0;
}
