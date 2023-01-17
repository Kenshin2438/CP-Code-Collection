#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int N = 5e4 + 10;

struct Bomb {
  long long x, y;
  int r, cnt;
} Bomb[N];

unordered_map<long long, int> idx;
inline long long myHash(long long x, long long y) {
  return x * 1e9 + y;
} // std::pair<long long, long long> 没有Hash

int ans = 0;
inline void dfs(long long X, long long Y, int R) {
  for (long long x = X - R; x <= X + R; x++) {
    if (x < 0 || x > 1e9) continue;
    for (long long y = Y - R; y <= Y + R; y++) {
      if (y < 0 || y > 1e9) continue;
      if (idx.find(myHash(x, y)) != idx.end()) {
        int nex = idx[myHash(x, y)];
        long long dx = Bomb[nex].x - X;
        long long dy = Bomb[nex].y - Y;
        long long dis2 = dx * dx + dy * dy;
        if (dis2 > R * 1LL * R) continue;
        if (Bomb[nex].cnt != 0) {
          ans += Bomb[nex].cnt;
          Bomb[nex].cnt = 0;
          dfs(Bomb[nex].x, Bomb[nex].y, Bomb[nex].r);
        }
      }
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m; cin >> n >> m;
  int num = 0;
  for (int i = 0; i < n; i++) {
    long long x, y; int r;
    cin >> x >> y >> r;
    if (idx.find(myHash(x ,y)) == idx.end()) {
      idx[myHash(x, y)] = ++num;
      Bomb[num].x = x;
      Bomb[num].y = y;
      Bomb[num].r = r;
      Bomb[num].cnt = 1;
    } else { // 同一中心的只需要知道最大爆炸半径
      int id = idx[myHash(x, y)];
      Bomb[id].r = max(Bomb[id].r, r);
      Bomb[id].cnt += 1;
    }
  }
  while (m--) {
    long long X, Y; int R;
    cin >> X >> Y >> R;
    dfs(X, Y, R);
  }
  cout << ans << '\n';
  return 0;
}