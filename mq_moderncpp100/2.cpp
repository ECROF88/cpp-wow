#include <format>
#include <iostream>
#include <numbers>
#include <print>
#include <string>
#include <string_view>

// struct X {
//   size_t operator()(size_t n) const { return n; }
// };
// X operator""_f(const char* c, size_t n) { return X{}; }

// constexpr auto operator""_f(const char* fmt, size_t)
// {
//   return [=]<typename... T>(T&&... Args) { return std::vformat(fmt, std::make_format_args((Args)...)); };
// }
namespace impl {
struct Helper {
  std::string_view s;
  Helper(const char* s, std::size_t len) : s(s, len) {};
  template <typename... Args>
  std::string operator()(Args&&... args) const
  {
    return std::vformat(s, std::make_format_args((args)...));
  }
};
}  // namespace impl
impl::Helper operator""_f(const char* s, std::size_t len) { return {s, len}; }
int main()
{
  std::cout << "乐 :{} *\n"_f(5);
  std::cout << "乐 :{0} {0} *\n"_f(5);
  std::cout << "乐 :{:b} *\n"_f(0b01010101);
  std::cout << "{:*<10}"_f("卢瑟");
  std::cout << '\n';
  int n{};
  std::cin >> n;
  std::cout << "π：{:.{}f}\n"_f(std::numbers::pi_v<double>, n);
}
