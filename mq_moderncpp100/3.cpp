#include <format>

#include "../mycommon.h"

struct Frac {
  int a, b;
};
// 特化formatter，使其能够格式化Frac，使用std::format等函数格式化Frac类型的对象时，将使用这里定义的规则。
template <>
struct std::formatter<Frac> : std::formatter<char> {
  auto format(const Frac& frac, auto& ctx) const
  {
    return std::format_to(ctx.out(), "{}/{}", frac.a, frac.b);
  }
};
void print(std::string_view fmt, auto&&... args)
{
  std::cout << std ::vformat(fmt, std::make_format_args(args...));
}
int main()
{
  Frac f{1, 2};
  std::cout << std::format("{}", f) << std::endl;

  print("{}", f);
}