// tr.insert(val);     //插入元素
// tr.erase(iterator); //删除元素
// tr.order_of_key();  //求k在树中是第几大
// tr.find_by_order(); //求树中的第k大
// tr.lower_bound();   //求前驱
// tr.upper_bound();   //求后继

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
struct ordered_set {
  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> s;

  ordered_set() = default;
  ordered_set(const vector<T> &v) : s(all(v)) {}
  ~ordered_set() = default;

  void insert(const T &x) { s.insert(x); }
  void erase(const T &x) { s.erase(x); }
  int rank(const T &x) { return s.order_of_key(x); }
  T nth_element(const int &k) { return *s.find_by_order(k); }
};
