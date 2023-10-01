## Operations

+ `split(p, val, &lt, &rt)`
  + 左子树`lt`所有值`<= val`
  + 左子树`rt`所有值` > val`
+ `merge(&p, lt, rt)` 保持`heap`性质
+ 虽然使用`split`和`merge`组合可以**比较方便地**实现如下的操作，但是为了保证效率应当减少它们的使用（毕竟对Treap进行了递归修改）。

---

1. `insert(val)` 插入
2. `remove(val)` 如若有多个，仅删除其中一个
3. `nth_element(n)` 第`n`大的元素，下标从1开始
4. `order_of_val(val)` 返回比`val`小的数的个数
5. `prev(val)` 小于`val`,且最大的数
6. `next(val)` 大于`val`,且最小的数

## Code

```cpp
std::mt19937 rng(std::random_device{}());

template <typename T>
class FhqTreap {
 private:
  struct TreapBase {
    int l = 0, r = 0, siz = 1;
    uint32_t prio = rng();
    T val;
    explicit TreapBase(const T& _val) : val{_val} {}
  };
  std::vector<TreapBase> data{TreapBase(2438)};
  int root = 0;
  constexpr inline auto newNode(const T& val) {
    auto idx = static_cast<int>(data.size());
    data.emplace_back(val);
    return idx;
  }

 private:
  auto size(const int& p) { return p == 0 ? 0 : data[p].siz; }
  auto pushUp(const int& p) {
    if (p == 0) return;
    data[p].siz = 1 + size(data[p].l) + size(data[p].r);
  }
  auto split(int p, int val, int& lt, int& rt) {
    if (p == 0) return lt = rt = 0, void();
    if (data[p].val <= val) {
      split(data[lt = p].r, val, data[p].r, rt);
    } else {
      split(data[rt = p].l, val, lt, data[p].l);
    }
    return pushUp(p);
  }
  auto merge(int& p, int lt, int rt) {
    if (lt == 0 or rt == 0) return p = lt | rt, void();
    if (data[lt].prio <= data[rt].prio) {
      merge(data[p = lt].r, data[lt].r, rt);
    } else {
      merge(data[p = rt].l, lt, data[rt].l);
    }
    return pushUp(p);
  }

 private:
  auto _insert(int& p, int q) {
    if (p == 0) return p = q, void();
    if (data[q].prio <= data[p].prio) {
      split(p, data[q].val, data[q].l, data[q].r);
      return pushUp(p = q);
    }
    if (data[q].val <= data[p].val) {
      _insert(data[p].l, q);
    } else {
      _insert(data[p].r, q);
    }
    return pushUp(p);
  }
  auto _remove(int& p, int val) {
    if (p == 0) return;
    if (data[p].val == val) return merge(p, data[p].l, data[p].r);
    if (val < data[p].val) {
      _remove(data[p].l, val);
    } else {
      _remove(data[p].r, val);
    }
    return pushUp(p);
  }
  auto _find_by_order(int k, int p) {
    if (size(p) < k) return -1;
    while (true) {
      if (size(data[p].l) >= k) {
        p = data[p].l;
      } else if (size(data[p].l) + 1 == k) {
        return data[p].val;
      } else {
        k -= size(data[p].l) + 1;
        p = data[p].r;
      }
    }
    assert(false);
  }

 public:
  FhqTreap() = default;
  auto insert(const T& val) { _insert(root, newNode(val)); }
  auto remove(const T& val) { _remove(root, val); }
  auto nth_element(const int& rank) { return _find_by_order(rank, root); }
  auto order_of_val(const int& val) {
    int p = root, rank = 0;
    while (p != 0) {
      if (val <= data[p].val) {
        p = data[p].l;
      } else {
        rank += size(data[p].l) + 1;
        p = data[p].r;
      }
    }
    return rank;
  }
  auto prev(const T& val) {
    int p = root, res = -1;
    while (p != 0) {
      if (val <= data[p].val) {
        p = data[p].l;
      } else {
        res = data[p].val;
        p = data[p].r;
      }
    }
    return res;
  }
  auto next(const T& val) {
    int p = root, res = -1;
    while (p != 0) {
      if (val >= data[p].val) {
        p = data[p].r;
      } else {
        res = data[p].val;
        p = data[p].l;
      }
    }
    return res;
  }
};
```