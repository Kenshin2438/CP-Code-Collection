// 前缀函数 lps[i] -> 前缀串s[0..i]的最长匹配的真前后缀
// lps[i] = max{k : s[0..k-1]==s[i-k+1..i]}

vector<int> KMP(const string &s, const string &pat) {
  string t = pat + '\0' + s;
  vector<int> lps(sz(t), 0);
  for (int i = 1; i < sz(t); i++) {
    int g = lps[i - 1];
    while (g && t[i] != t[g]) g = lps[g - 1];
    lps[i] = g + (t[i] == t[g]);
  }
  vector<int> match;
  for (int i = sz(t) - sz(s); i < sz(t); i++) {
    if (lps[i] == sz(pat)) {
      match.push_back(i - 2 * sz(pat));
    }
  }
  return match;
}

// 根据前缀函数建自动机
// aut[l][c] -> 前缀l后面添加字符c后 的前缀函数

void LPS_automaton(const string &s) {
  vector<int> lps(sz(s), 0);
  vector<array<int, 26>> aut(sz(s));
  aut[0][s[0] - 'a'] = 1;
  for (int i = 1; i < sz(s); i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'a' + c != s[i]) {
        aut[i][c] = aut[lps[i - 1]][c];
      } else {
        aut[i][c] = i + ('a' + c == s[i]);
      }
    }
    lps[i] = aut[lps[i - 1]][s[i] - 'a'];
  }
};
