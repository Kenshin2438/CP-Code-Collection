#if __cplusplus >= 201402L
  #define rall(a) std::rbegin(a), std::rend(a)
#else
  #define rall(a) a.rbegin(), a.rend()
#endif

struct SuffixArray {
  std::vector<int> SA, LCP, RK;
  SuffixArray(const std::string &s, char first = 'a', char last = 'z') {
    get_sa(s, first, last), get_lcp(s);
  }
  auto SA_IS(const std::vector<int> &v, int K) -> std::vector<int> {
    const int n = int(v.size());
    std::vector<int> sa(n), lms;
    std::vector<bool> sl(n, false);
    for (int i = n - 2; i >= 0; i--) {
      sl[i] = (v[i] == v[i + 1] ? sl[i + 1] : v[i] > v[i + 1]);
      if (sl[i] && !sl[i + 1]) lms.push_back(i + 1);
    }
    reverse(all(lms));
    const auto induced_sort = [&](const std::vector<int> &LMS) {
      std::vector<int> l(K, 0), r(K, 0);
      for (const int &x : v) {
        if (x + 1 < K) l[x + 1]++;
        ++r[x];
      }
      partial_sum(all(l), begin(l));
      partial_sum(all(r), begin(r));
      fill(all(sa), -1);
      for_each(rall(LMS), [&](const int &p) { sa[--r[v[p]]] = p; });
      for (const int &p : sa)
        if (p >= 1 && sl[p - 1]) {
          sa[l[v[p - 1]]++] = p - 1;
        }
      fill(all(r), 0);
      for (const int &x : v) ++r[x];
      partial_sum(all(r), begin(r));
      for_each(rall(sa) - 1, [&](const int &p) {
        if (p >= 1 && !sl[p - 1]) sa[--r[v[p - 1]]] = p - 1;
      });
    };
    induced_sort(lms);
    std::vector<int> new_lms(int(lms.size())), new_v(int(lms.size()));
    for (int i = 0, k = 0; i < n; i++) {
      if (!sl[sa[i]] && sa[i] >= 1 && sl[sa[i] - 1]) new_lms[k++] = sa[i];
    }
    int cur = sa.back() = 0;
    for (int k = 1; k < int(new_lms.size()); k++) {
      int i = new_lms[k - 1], j = new_lms[k];
      if (v[i] != v[j]) {
        sa[j] = ++cur;
        continue;
      }
      bool flag = false;
      for (int a = i + 1, b = j + 1;; a++, b++) {
        if (v[a] != v[b]) {
          flag = true;
          break;
        }
        if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
          flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
          break;
        }
      }
      sa[j] = (flag ? ++cur : cur);
    }
    for (int i = 0; i < int(lms.size()); i++) new_v[i] = sa[lms[i]];
    if (cur + 1 < int(lms.size())) {
      auto lms_SA = SA_IS(new_v, cur + 1);
      for (int i = 0; i < int(lms.size()); i++) new_lms[i] = lms[lms_SA[i]];
    }
    induced_sort(new_lms);
    return sa;
  }
  void get_sa(const std::string &s, char first = 'a', char last = 'z') {
    std::vector<int> v(int(s.size()) + 1);
    copy(all(s), begin(v));
    for (auto &&x : v) x -= first - 1;
    v.back() = 0;
    this->SA = SA_IS(v, last - first + 2), this->SA.erase(begin(this->SA));
  }
  void get_lcp(const std::string &s) {
    int n = int(s.size());
    std::vector<int> rank(n), lcp(n);
    for (int i = 0; i < n; i++) rank[SA[i]] = i;
    for (int i = 0, p = 0; i < n; i++, p ? p-- : 0) {
      if (rank[i] == 0) {
        p = 0;
        continue;
      }
      int j = SA[rank[i] - 1];
      while (i + p < n && j + p < n && s[i + p] == s[j + p]) p++;
      lcp[rank[i]] = p;
    }
    this->LCP = std::move(lcp), this->RK = std::move(rank);
  }
};