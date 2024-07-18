
#include <print>

#include "mycommon.h"
using namespace std;
//...在左边是定义
//...在右边是使用
enum CallbackResult
{
  KEEP,
  ERASE
};
const int SHOT_TIMES = 10;

inline constexpr struct one_shot_t {
  explicit one_shot_t() = default;
} oneshot;

enum class N_shot_t : int
{
};
template <class Self>
shared_ptr<Self> lock_if_weak(weak_ptr<Self> const &self)
{
  return self.lock();
}
template <class Self>
Self const &lock_if_weak(Self const &self)
{
  return self;
}
// template <class Self, class MemFn>
// auto bind(Self self, MemFn m)  //
// {
//   return [self = std::move(self), m](auto... __t) {
//     ((*self).*m)(__t...);
//     return CallbackResult::KEEP;
//   };
//   // 只能按值捕获。
// }
template <class Self, class MemFn>
auto bind(Self self, MemFn m, N_shot_t n)  //
{
  return [self = std::move(self), m, n = static_cast<int>(n)](auto... __t) mutable {
    auto const &ptr = lock_if_weak(self);
    if (ptr == nullptr) return CallbackResult::ERASE;
    if (n == 0) return CallbackResult::ERASE;
    n--;
    // cout << "n= " << n << endl;
    ((*ptr).*m)(__t...);
    return CallbackResult::KEEP;
  };
  // 由于lamda表达式封装的operator()是const的，所以不能修改n
}
// template <class Self, class MemFn>
// auto bind(std::weak_ptr<Self> self, MemFn m)  // 如果是weak_ptr就需要判断是否为空
// {
//   return [self = std::move(self), m](auto... __t) {
//     auto ptr = self.lock();
//     if (ptr != nullptr) {
//       ((*ptr).*m)(__t...);
//       return CallbackResult::KEEP;
//     } else
//       return CallbackResult::ERASE;
//   };
//   // 只能按值捕获。
// }
template <class... T>
class Signal
{
#if __cpp_lib_move_only_function
  using Functor = std::move_only_function<CallbackResult(T...)>;
#else
  using Functor = std::function<CallbackResult(T...)>;
#endif
  // std::vector<std::move_only_function<CallbackResult(T...)>> funs;
  std::vector<Functor> funs;

public:
  template <class Func>
  void connect(Func fun)
  {
    if constexpr (std::is_convertible_v<std::invoke_result_t<Func, T...>, CallbackResult>) {
      cout << "convertible\n";
      funs.push_back(move(fun));
    } else {
      cout << "not convertible\n";
      funs.push_back([fun = move(fun)](T... t) mutable {
        fun(t...);
        return CallbackResult::KEEP;
      });
    }
  }

  // template <class Self, class MemFn>
  // void connect(Self self, MemFn m)
  // {
  //   funs.push_back([=](T... t) { ((*self).*m)(t...); });  // 如果使用引用就会出现错误，因为外部的变量可能已经被销毁
  // }
  template <class Self, class MemFn, class... Tag>
  void connect(Self self, MemFn m, Tag... tag)
  {
    funs.push_back(bind(std::move(self), m, tag...));
  }

  // template <class Self, class MemFn>
  // void connect_N_shot(Self self, MemFn m, int n = SHOT_TIMES)
  // {
  //   funs.push_back(bind_N_shot(std::move(self), m, n));
  // }

  // template <class Self, class MemFn>
  // void connect_weak(std::weak_ptr<Self> self, MemFn m)
  // {
  //   funs.push_back(bind(std::weak_ptr<Self>(self), m));
  // }

  void emit(T... t)
  {
    for (auto it = funs.begin(); it != funs.end();) {
      CallbackResult result = (*it)(t...);
      switch (result) {
        case CallbackResult::KEEP:
          it++;
          break;
        case CallbackResult::ERASE:
          it = funs.erase(it);
          break;
      }
    }
  }
};
struct A {
  static int id;
  int data = 1000;
  void print(int i)
  {
    printf_s("A get %d and data = %d\n", i, data);
    // printf_s("A get i=%d j=%d and data = %d\n", i, j, data);
    data++;
  }
  A() { printf_s("A construct %d\n", data); }
  ~A() { printf_s("A destruct %d\n", data); }
  void exit(string s1, string s2) const { cout << "A" << s1 << " " << s2 << endl; }
};
shared_ptr<A> gloabl_ptr;
struct Input {
  Signal<int> on_input;
  Signal<string, string> on_exit;

  void start_loop()
  {
    int input;
    while (cin >> input && input != -1) {
      on_input.emit(input);
      if (input == 100) gloabl_ptr = nullptr;
    }
    on_exit.emit("exit", "!");
  }
};

#define FUN(f, ...) [=](auto &&...__t) { return f(__VA_ARGS__ __VA_OPT__(, ) forward<decltype(__t)>(__t)...); }

struct Test {
  void operator()(int i) { printf_s("Test get %d\n", i); }
} t;

void test(int i) { printf_s("test get %d\n", i); }

void dummy(Input &input)
{
  auto ptr = make_shared<A>();
  // 捕获shared_ptr不能使用引用,应该直接拷贝:(使用&ptr=ptr会出现错误)
  // 只有下面这一句话的时候,就会报错,因为ptr被析构了.如果后面还有用到ptr这里不论是写&还是=都没有问题.
  // input.on_input.connect([ptr = ptr](int i) { return ptr->print(i); });

  // weak_ptr<A> weak_ptr = ptr;
  shared_ptr<A> shared_a = ptr;
  // input.on_input.connect([weak_ptr](int i) {
  //   std::shared_ptr<A> shared_a = weak_ptr.lock();
  //   if (shared_a != nullptr)
  //     shared_a->print(i);
  //   else {
  //     cout << "home is empty" << endl;
  //   }
  // });

  // 使用weak_ptr导致A已经析构了,所以不会输出任何东西
  // 想要延长生命周期,可以使用一个全局的shared_ptr来指向A,
  gloabl_ptr = shared_a;  // 加上这句话延长了A的生命周期
  // input.on_input.connect(std::weak_ptr(shared_a), &A::print, N_shot_t(3));
  input.on_input.connect(ptr, &A::print, N_shot_t{3});
  // input.on_input.connect(FUN(ptr->print));
  // auto foo = make_unique<A>();
  input.on_input.connect(FUN(ptr->print));
  // input.on_input.connect([aa = ptr](int i) { aa->print(i); });
  // input.on_input.connect(ptr, &A::print);
  // input.on_input.connect(move(foo), &A::print);
  // input.on_exit.connect(ptr, &A::exit);
}

int main()
{
  // A a;

  Input input;
  int i;

  // input.singal.connect([a](std::any i) { a.print(any_cast<int>(i)); });
  dummy(input);
  // input.on_input.connect(bind(&a, &A::print));
  // input.on_input.connect(&a, &A::print);
  // input.on_input.connect(FUN(a.print));
  // input.on_input.connect(FUN(test));
  // input.on_exit.connect([&a](string s1, string s2) { a.exit(s1, s2); });
  // input.on_exit.connect(bind(&a, &A::exit));
  // input.on_exit.connect(&a, &A::exit);
  input.start_loop();

  return 0;
}