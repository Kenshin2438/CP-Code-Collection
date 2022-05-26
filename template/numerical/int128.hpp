#include "../main.hpp"

using i128 = __int128;

istream &operator>>(istream &is, i128 &v) {
  str s; is >> s, v = 0;
  for (const char &c : s) {
    if (c >= '0' && c <= '9') v = v * 10 + (c & 15);
  }
  if (s.front() == '-') v = -v;
  return is;
}

ostream &operator<<(ostream &os, const i128 &v) {
  if (v == 0) return (os << "0");
  i128 num = v; str s;
  if (v < 0) os << '-', num = -num;
  for (; num > 0; num /= 10) s.push_back(char(num % 10) + '0');
  return reverse(s.begin(), s.end()), (os << s);
}
