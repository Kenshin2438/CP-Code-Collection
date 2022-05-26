#define PROBLEM "http://oj.daimayuan.top/course/10/problem/497"

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
  #include "debug.hpp"
#else
  #define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()

using db = long double;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using tree = __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>,
                  __gnu_pbds::rb_tree_tag,
                  __gnu_pbds::tree_order_statistics_node_update>;
// // ordered_set
// // 操作如下：
// tr.insert(val);     //插入元素
// tr.erase(iterator); //删除元素
// tr.order_of_key();  //求k在树中是第几大
// tr.find_by_order(); //求树中的第k大
// tr.lower_bound();   //求前驱
// tr.upper_bound();   //求后继

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }

void SingleTest(int TestCase) {
  int n; cin >> n;
  // int n = 3e5;
  vec<ll> a(n);
  for (ll &x : a) cin >> x;
  // for (ll &x : a) x = randint(0, 1e9);
  int ans = 0; ll num = 0;
  for (int b = 31; b >= 0; b--) {
    int p1 = ans | (1 << b);
    ll c1  = 0;
    tree t;
    for (int i = 0; i < n; i++) {
      ll v = ((a[i] ^ p1) << 20) + i;
      t.insert(v);
      c1 += i - t.order_of_key(v);
    }
    tree s;
    int p0 = ans;
    ll c0  = 0;
    for (int i = 0; i < n; i++) {
      ll v = ((a[i] ^ p0) << 20) + i;
      s.insert(v);
      c0 += i - s.order_of_key(v);
    }
    if (c0 > c1) ans = p1;
    num = min(c0, c1);
  }
  cout << num << " " << ans;
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
