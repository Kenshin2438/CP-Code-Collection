```cpp
constexpr int B = 350;  // approx. n/sqrt(q)

std::vector<int> Qid(std::size(Q));
std::iota(all(Qid), 0);
std::sort(all(Qid), [&](const int &pa, const int &pb) -> bool {
#define K(x) std::make_pair((x).first / B, (x).second ^ -((x).first / B & 1))
  return K(Q[pa]) < K(Q[pb]);
#undef K
});

int L = 0, R = 0;  // [L, R)
const auto add  = [&](int p) { };
const auto del  = [&](int p) { };
const auto calc = [&]() { };

std::vector<i64> ans(std::size(Q));
for (const int &id : Qid) {
  const auto &[l, r] = Q[id];
  while (L > l) add(--L);
  while (R < r) add(R++);
  while (L < l) del(L++);
  while (R > r) del(--R);
  ans[id] = calc();
}

for (const auto &x : ans) std::cout << x << "\n";
```