struct SuffixArray {
  vector<int> SA, LCP;

  SuffixArray(const string &s, char first = 'a', char last = 'z') {
    get_sa(s, first, last), get_lcp(s);
  }

  vector<int> SA_IS(const vector<int> &v, int K) {
    const int n = sz(v);
    vector<int> SA(n), lms;
    vector<bool> sl(n, false);
    for (int i = n - 2; i >= 0; i--) {
      sl[i] = (v[i] == v[i + 1] ? sl[i + 1] : v[i] > v[i + 1]);
      if (sl[i] && !sl[i + 1]) lms.push_back(i + 1);
    }
    reverse(all(lms));
    const auto induced_sort = [&](const vector<int> &LMS) {
      vector<int> l(K, 0), r(K, 0);
      for (const int &x : v) {
        if (x + 1 < K) l[x + 1]++;
        ++r[x];
      }
      partial_sum(all(l), begin(l));
      partial_sum(all(r), begin(r));
      fill(all(SA), -1);
      for_each(rall(LMS), [&](const int &p) { SA[--r[v[p]]] = p; });
      for (const int &p : SA) if (p >= 1 && sl[p - 1]) {
        SA[l[v[p - 1]]++] = p - 1;
      }
      fill(all(r), 0);
      for (const int &x : v) ++r[x];
      partial_sum(all(r), begin(r));
      for_each(rall(SA) - 1, [&](const int &p) {
        if (p >= 1 && !sl[p - 1]) SA[--r[v[p - 1]]] = p - 1;
      });
    };
    induced_sort(lms);
    vector<int> new_lms(sz(lms)), new_v(sz(lms));
    for (int i = 0, k = 0; i < n; i++) {
      if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
        new_lms[k++] = SA[i];
      }
    }
    int cur = SA.back() = 0;
    for (int k = 1; k < sz(new_lms); k++) {
      int i = new_lms[k - 1], j = new_lms[k];
      if (v[i] != v[j]) { SA[j] = ++cur; continue; }
      bool flag = false;
      for (int a = i + 1, b = j + 1;; a++, b++) {
        if (v[a] != v[b]) { flag = true; break; }
        if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
          flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
          break;
        }
      }
      SA[j] = (flag ? ++cur : cur);
    }
    for (int i = 0; i < sz(lms); i++) new_v[i] = SA[lms[i]];
    if (cur + 1 < sz(lms)) {
      auto lms_SA = SA_IS(new_v, cur + 1);
      for (int i = 0; i < sz(lms); i++) new_lms[i] = lms[lms_SA[i]];
    }
    return induced_sort(new_lms), SA;
  }

  void get_sa(const string &s, char first = 'a', char last = 'z') {
    vector<int> v(sz(s) + 1);
    copy(all(s), begin(v));
    for (auto &&x : v) x -= first - 1;
    v.back() = 0;
    this->SA = SA_IS(v, last - first + 2);
    this->SA.erase(begin(this->SA));
  }

  void get_lcp(const string &s) {
    int n = sz(s);
    vector<int> rank(n), lcp(n);
    for (int i = 0; i < n; i++) rank[SA[i]] = i;
    for (int i = 0, p = 0; i < n; i++, p ? p--: 0) {
      if (rank[i] == 0) { p = 0; continue; }
      int j = SA[rank[i] - 1];
      while (i + p < n && j + p < n && s[i + p] == s[j + p]) p++;
      lcp[rank[i]] = p;
    }
    this->LCP = move(lcp);
  }
};