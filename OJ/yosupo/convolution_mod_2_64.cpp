#include<cstdio>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
namespace ModularPolynomial
{
  using ull = unsigned long long;
  constexpr const unsigned mod = 998244353, modM1 = mod - 1, modM1D2 = (mod - 1) >> 1, G = 3189;
  constexpr const ull modmod2 = static_cast<ull>(mod) * (mod << 1); constexpr const size_t sizeof_unsigned = sizeof(unsigned);
  inline constexpr unsigned Div2(const unsigned val) { return (val & 1 ? val + mod : val) >> 1; }
  inline constexpr unsigned Power(unsigned a, unsigned b) { unsigned ans = 1; for (; b; a = static_cast<ull>(a) * a % mod, b >>= 1) if (b % 2) ans = ans * static_cast<ull>(a) % mod; return ans; }
  inline constexpr unsigned Inv(unsigned val) { unsigned ans = 1; for (; val > 1; ans = ans * static_cast<ull>(mod - mod / val) % mod, val = mod % val); return ans; }
  inline constexpr void UpdateAdd(unsigned& pos, const unsigned val) { if ((pos += val) >= mod) pos -= mod; return; }
  unsigned inv_power_2[33], unit_root[8388608]; std::pair<unsigned, unsigned> gn[33]; std::vector<unsigned> aux1, aux2;
  constexpr unsigned inv_G = Inv(G), sqrt_M1 = Power(G, modM1D2 >> 1), inv_sqrt_M1 = Inv(sqrt_M1), & inv_power2_0 = inv_power_2[0], & unit_root_1 = unit_root[1];
  inline void Prepare(const unsigned maxi_length)
  {
    const unsigned siz_gn = 32 - __builtin_clz(maxi_length - 1), siz_unit_root = 1u << siz_gn;
    gn[siz_gn].first = Power(G, modM1D2 >> siz_gn); gn[siz_gn].second = Power(inv_G, modM1D2 >> siz_gn); unit_root_1 = inv_power2_0 = 1;
    for (unsigned i = siz_gn; i > 1; gn[i - 1].first = static_cast<ull>(gn[i].first) * gn[i].first % mod, gn[i - 1].second = static_cast<ull>(gn[i].second) * gn[i].second % mod, --i);
    for (unsigned i = 2, p_gn = 1; i < siz_unit_root; inv_power_2[p_gn] = Div2(inv_power_2[p_gn - 1]), ++p_gn)
    {
      const unsigned i2 = i << 1, cur_gn = gn[p_gn].first; for (unsigned j = i; j < i2; unit_root[j | 1] = static_cast<ull>(unit_root[j] = unit_root[j >> 1]) * cur_gn % mod, j += 2); i = i2;
    }
    inv_power_2[siz_gn] = Div2(inv_power_2[siz_gn - 1]);
    return;
  }
  inline void DIFNTT(const unsigned lengthD2, unsigned* const a)
  {
    for (unsigned i = lengthD2, end_j = 1; i; i >>= 1, end_j <<= 1)
    {
      const unsigned* const start_pur = unit_root + i;
      for (unsigned j = 0, *p = a; j < end_j; ++j, p += i)
      {
        const unsigned* p_unit_root = start_pur;
        for (unsigned k = 0; k < i; ++k, ++p, ++p_unit_root) { const unsigned t = *p; UpdateAdd(*p, *(p + i)); *(p + i) = static_cast<ull>(t + mod - *(p + i)) * *p_unit_root % mod; }
      }
    }
    return;
  }
  inline void DITNTT(const unsigned lengthD2, unsigned* const a)
  {
    for (unsigned i = 1, end_j = lengthD2; i <= lengthD2; i <<= 1, end_j >>= 1)
    {
      const unsigned* const start_pur = unit_root + i;
      for (unsigned j = 0, *p = a; j < end_j; ++j, p += i)
      {
        const unsigned* p_unit_root = start_pur;
        for (unsigned k = 0; k < i; ++k, ++p, ++p_unit_root)
        {
          const unsigned t = static_cast<ull>(*(p + i)) * *p_unit_root % mod; if ((*(p + i) = *p - t) > 2147483647) *(p + i) += mod; UpdateAdd(*p, t);
        }
      }
    }
    return;
  }
  inline void Multi(const unsigned length_ans, vector<unsigned>& a, vector<unsigned>& b)
  {
    const unsigned log2_siz = 32 - __builtin_clz(length_ans - 1), siz = 1u << log2_siz, inv_siz = inv_power_2[log2_siz]; a.resize(siz); b.resize(siz);
    DIFNTT(siz >> 1, a.data()); DIFNTT(siz >> 1, b.data()); for (unsigned i = 0; i < siz; b[i] = static_cast<ull>(a[i]) * b[i] % mod, ++i); DITNTT(siz >> 1, b.data());
    a[0] = b[0] * static_cast<ull>(inv_siz) % mod; for (unsigned i = 1; i < length_ans; a[i] = b[static_cast<ull>(siz - i)] * static_cast<ull>(inv_siz) % mod, ++i);
    return;
  }
  inline void Inv(const unsigned length_ans, std::vector<unsigned>& a, std::vector<unsigned>& ans)
  {
    const unsigned siz = 1u << (32 - __builtin_clz(length_ans - 1)); a.resize(siz); aux1.resize(siz); aux2.resize(siz); ans.resize(siz); ans[0] = Inv(a[0]);
    for (unsigned i = 1, p_gn = 1; i < length_ans; ++p_gn)
    {
      const unsigned i2 = i << 1; memcpy(aux1.data(), a.data(), i2 * sizeof_unsigned); memcpy(aux2.data(), ans.data(), i * sizeof_unsigned); memset(aux2.data() + i, 0, i * sizeof_unsigned);
      DIFNTT(i, aux1.data()); DIFNTT(i, aux2.data()); for (unsigned j = 0; j < i2; aux2[j] = (aux1[j] * static_cast<ull>(aux2[j]) + modM1) % mod * aux2[j] % mod, ++j); DITNTT(i, aux2.data());
      const unsigned inv_i = inv_power_2[p_gn - 1], inv_i2 = inv_power_2[p_gn], cur_gn = gn[p_gn].first, inv_cur_gn = gn[p_gn].second; aux1[0] = aux2[0] * static_cast<ull>(inv_i2) % mod;
      for (unsigned j = 1; j < i2; aux1[j] = static_cast<ull>(aux2[static_cast<size_t>(i2 - j)]) * inv_i2 % mod, ++j);
      for (unsigned j = 0, val = 1; j < i; ++j)
      {
        aux2[j] = (a[j] + a[i | j] * static_cast<ull>(sqrt_M1)) % mod * val % mod; ans[i | j] = ans[j] * static_cast<ull>(val) % mod; val = val * static_cast<ull>(cur_gn) % mod;
      }
      DIFNTT(i >> 1, aux2.data()); DIFNTT(i >> 1, ans.data() + i); for (unsigned j = 0; j < i; aux2[j] = (aux2[j] * static_cast<ull>(ans[i | j]) + modM1) % mod * ans[i | j] % mod, ++j);
      DITNTT(i >> 1, aux2.data()); ans[i] = Div2((modmod2 - ((static_cast<ull>(aux2[0]) * inv_i + aux1[0]) % mod * inv_sqrt_M1 + aux1[i])) % mod);
      const unsigned end_j = std::min(i, length_ans - i);
      for (unsigned j = 1, val = cur_gn, inv_val = static_cast<ull>(inv_sqrt_M1) * inv_cur_gn % mod; j < end_j; ++j)
      {
        const unsigned t = (static_cast<ull>(aux2[static_cast<size_t>(i - j)]) * inv_i + static_cast<ull>(aux1[j]) * val) % mod;
        ans[i | j] = Div2((modmod2 - (static_cast<ull>(t) * inv_val + aux1[i | j])) % mod); val = val * static_cast<ull>(cur_gn) % mod; inv_val = inv_val * static_cast<ull>(inv_cur_gn) % mod;
      }
      i = i2;
    }
    return;
  }
}
namespace Polynomial
{
  using ull = unsigned long long; constexpr const double PiD2 = acos(-1) / 2.0;
  struct Complex
  {
    double real, imag;
    constexpr Complex(const double _real = 0, const double _imag = 0) :real(_real), imag(_imag) {}
    inline constexpr Complex& operator+=(const Complex& other) { real += other.real; imag += other.imag; return *this; }
    inline constexpr Complex operator-(const Complex& other)const { return Complex(real - other.real, imag - other.imag); }
    inline constexpr Complex operator*(const Complex& other)const { return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real); }
    inline friend constexpr Complex Conjugate(const Complex& val) { return Complex(val.real, -val.imag); }
  }unit_root[8388608];
  std::vector<Complex> aux1, aux2, aux3, aux4; constexpr const size_t sizeof_Complex = sizeof(Complex); constexpr Complex& unit_root_1 = unit_root[1];
  inline void Prepare(const unsigned maxi_length)
  {
    unit_root_1 = 1; const unsigned siz_unit_root = 1u << (32 - __builtin_clz(maxi_length - 1)); double angle = PiD2;
    for (unsigned i = 2; i < siz_unit_root; angle /= 2.0)
    {
      const unsigned i2 = i << 1; const Complex gn(cos(angle), sin(angle)); for (unsigned j = i; j < i2; unit_root[j | 1] = (unit_root[j] = unit_root[j >> 1]) * gn, j += 2); i = i2;
    }
    return;
  }
  inline void DIFFFT(const unsigned lengthD2, Complex* const a)
  {
    for (unsigned i = lengthD2, end_j = 1; i; i >>= 1, end_j <<= 1)
    {
      const Complex* const start_pur = unit_root + i; Complex* p = a;
      for (unsigned j = 0; j < end_j; ++j, p += i)
      {
        const Complex* p_unit_root = start_pur; for (unsigned k = 0; k < i; ++k, ++p, ++p_unit_root) { const Complex t = *p; *p += *(p + i); *(p + i) = (t - *(p + i)) * *p_unit_root; }
      }
    }
    return;
  }
  inline void DITFFT(const unsigned lengthD2, Complex* const a)
  {
    for (unsigned i = 1, end_j = lengthD2; i <= lengthD2; i <<= 1, end_j >>= 1)
    {
      const Complex* const start_pur = unit_root + i; Complex* p = a;
      for (unsigned j = 0; j < end_j; ++j, p += i)
      {
        const Complex* p_unit_root = start_pur; for (unsigned k = 0; k < i; ++k, ++p, ++p_unit_root) { const Complex t = *(p + i) * *p_unit_root; *(p + i) = *p - t; *p += t; }
      }
    }
    return;
  }
  inline void Multi(const unsigned mod, const unsigned length_a, const unsigned length_b, const vector<unsigned>& a, const vector<unsigned>& b, vector<unsigned>& c)
  {
    const unsigned length_ans = length_a + length_b - 1, siz = 1u << (32 - __builtin_clz(length_ans - 1)), sizD2 = siz >> 1; aux1.resize(siz); aux2.resize(siz); aux3.resize(siz); aux4.resize(siz);
    for (unsigned i = 0; i < length_a; aux1[i].real = a[i] >> 15, aux1[i].imag = a[i] & 32767, ++i); for (unsigned i = 0; i < length_b; aux2[i].real = b[i] >> 15, aux2[i].imag = b[i] & 32767, ++i);
    memset(aux1.data() + length_a, 0, static_cast<size_t>(siz - length_a) * sizeof_Complex); memset(aux2.data() + length_b, 0, static_cast<size_t>(siz - length_b) * sizeof_Complex);
    DIFFFT(sizD2, aux1.data()); DIFFFT(sizD2, aux2.data()); for (unsigned i = 0; i < siz; aux3[i] = aux1[i] * aux2[i], ++i); aux4[0] = Conjugate(aux1[0]) * aux2[0];
    for (unsigned i = 1; i < siz;) { const unsigned i2 = i << 1, t = i + i2 - 1; for (unsigned j = i; j < i2; aux4[j] = Conjugate(aux1[static_cast<size_t>(t - j)]) * aux2[j], ++j); i = i2; }
    DITFFT(sizD2, aux3.data()); DITFFT(sizD2, aux4.data()); const double inv_siz = 1.0 / siz, inv_2siz = inv_siz / 2.0; const ull barrett_t = (~static_cast<ull>(mod - 1)) / mod + 1;
    const unsigned barrett_a = barrett_t >> 32, barrett_b = static_cast<unsigned>(barrett_t);
    const auto barrett_reduce = [&mod, &barrett_a, &barrett_b](const ull val)->unsigned
    {
      const ull t1 = (val & 0xffffffffu) * barrett_a, t2 = (val >> 32) * barrett_b;
      return val - ((((((val & 0xffffffffu) * barrett_b) >> 32) + (t1 & 0xffffffff) + (t2 & 0xffffffff)) >> 32) + (t1 >> 32) + (t2 >> 32) + (val >> 32) * barrett_a) * mod;
    };
    const auto calc = [&mod, &inv_siz, &inv_2siz, &barrett_reduce](const Complex& x, const Complex& y)->unsigned
    {
      const ull t1 = static_cast<ull>((x.real + y.real) * inv_2siz + 0.5), t2 = static_cast<ull>(y.real * inv_siz - t1 + 0.5), t3 = static_cast<ull>(x.imag * inv_siz + 0.5);
      const unsigned ans = barrett_reduce((static_cast<ull>(barrett_reduce(t1)) << 30) + (static_cast<ull>(barrett_reduce(t3)) << 15) + t2);
      return ans >= mod ? ans - mod : ans;
    };
    c.resize(siz); c[0] = calc(aux3[0], aux4[0]); for (unsigned i = 1; i < length_ans; c[i] = calc(aux3[static_cast<size_t>(siz - i)], aux4[static_cast<size_t>(siz - i)]), ++i); return;
  }
}
char buf_in[4194304], buf_out[4194304], buf_temp[11], * p_buf_out = buf_out;
constexpr char& buf_temp_1 = buf_temp[1];
const char* p_buf_in = buf_in;
inline unsigned ReadU()
{
  for (; *p_buf_in < '0'; ++p_buf_in);
  unsigned ans = *p_buf_in ^ '0';
  for (; *(++p_buf_in) >= '0'; ans = ans * 10 + (*p_buf_in ^ '0'));
  return ans;
}
inline void WriteUS(unsigned val)
{
  unsigned char len = 1;
  for (buf_temp_1 = val % 10; val /= 10; buf_temp[++len] = val % 10);
  for (; len; *(p_buf_out++) = buf_temp[len--] ^ '0');
  *(p_buf_out++) = ' ';
  return;
}
int main()
{
  fread(buf_in, 1, 4194304, stdin);
  const unsigned n = ReadU(), m = ReadU(), mod = ReadU(), length_ans = n + m + 1;
  Polynomial::Prepare(length_ans);
  vector<unsigned> a(n), b(m);
  for (unsigned& i : a)
  {
    i = ReadU();
  }
  for (unsigned& i : b)
  {
    i = ReadU();
  }
  Polynomial::Multi(mod, n + 1, m + 1, a, b, a);
  for (unsigned i = 0; i < length_ans; WriteUS(a[i++]));
  fwrite(buf_out, 1, p_buf_out - buf_out, stdout);
  return 0;
}
