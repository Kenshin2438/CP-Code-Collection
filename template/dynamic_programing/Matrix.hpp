struct Matrix {
  int n; vector<vector<mint>> M;

  Matrix(int _n, bool id = false) : n(_n) {
    M.resize(n, vector<mint>(n));
    if (id) for (int i = 0; i < n; i++) M[i][i] = 1;
  }

  Matrix &operator*=(const Matrix &m) {
    vector<vector<mint>> ans(n, vector<mint>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          ans[i][j] += M[i][k] * m.M[k][j];
        }
      }
    }
    this->M = move(ans);
    return *this;
  }
  Matrix pow(int k) const {
    Matrix x(*this), res(n, true);
    for (; k > 0; k >>= 1, x *= x) {
      if (k & 1) res *= x;
    }
    return res;
  }
};
