#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string

#define all(x) (x).begin(), (x).end()

typedef long long ll;

const int N = (int) 1e3 + 10;

int n, m, k;

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  cin >> n >> m >> k;
  queue<int> q;
  for (int i = 1, x; i <= n; i++) {
    cin >> x; q.push(x);
  }
  vec<int> cur;
  stack<int> box;

  while (!q.empty()) {
    if (cur.empty()) {
      if (!box.empty()) {
        cur.emplace_back(box.top()), box.pop();
      } else {
        cur.emplace_back(q.front()), q.pop();
      }
    } else {
      if (!box.empty()) {
        if (box.top() <= cur.back()) {
          cur.emplace_back(box.top()), box.pop();
        } else {
          if (q.front() <= cur.back()) {
            cur.emplace_back(q.front()), q.pop();
          } else {
            if ((int) box.size() == m) {
              for (int i = 0; i < (int) cur.size(); i++) {
                cout << cur[i] << " \n"[i + 1 == (int) cur.size()];
              }
              cur.clear();
            } else {
              box.push(q.front()), q.pop();
            }
          }
        }
      } else {
        // cur.emplace_back(q.front()), q.pop();
        if (q.front() <= cur.back()) {
          cur.emplace_back(q.front()), q.pop();
        } else {
          if ((int) box.size() == m) {
            for (int i = 0; i < (int) cur.size(); i++) {
              cout << cur[i] << " \n"[i + 1 == (int) cur.size()];
            }
            cur.clear();
          } else {
            box.push(q.front()), q.pop();
          }
        }
      }
    }
    if ((int) cur.size() == k) {
      for (int i = 0; i < (int) cur.size(); i++) {
        cout << cur[i] << " \n"[i + 1 == (int) cur.size()];
      }
      cur.clear();
    }
  }
  while (!box.empty()) {
    if (cur.empty()) {
      cur.emplace_back(box.top()), box.pop();
    } else {
      if (box.top() <= cur.back()) {
        cur.emplace_back(box.top()), box.pop();
      } else {
        for (int i = 0; i < (int) cur.size(); i++) {
          cout << cur[i] << " \n"[i + 1 == (int) cur.size()];
        }
        cur.clear();
      }
    }
    if ((int) cur.size() == k) {
      for (int i = 0; i < (int) cur.size(); i++) {
        cout << cur[i] << " \n"[i + 1 == (int) cur.size()];
      }
      cur.clear();
    }
  }
  for (int i = 0; i < (int) cur.size(); i++) {
    cout << cur[i] << " \n"[i + 1 == (int) cur.size()];
  }
  cur.clear();
  return 0;
}
