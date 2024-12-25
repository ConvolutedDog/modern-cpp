#include <iostream>
#include <functional>
#include <vector>
#include "FunctionRef.h"

// template<typename ResTy, typename... Params>
// class FuncRefWrapper {
// public:
//   FuncRefWrapper(function_ref<ResTy, Params...> f) : func(f) {}

// private:
//   function_ref<ResTy, Params...> func;
// }


// template<typename Ret, typename... Params, typename... Rest>
// std::vector<std::unique_ptr<IFuncWrapper>> make_func_wrapper_vector(function_ref<Ret, Params...> f, Rest... rest) {
//     std::vector<std::unique_ptr<IFuncWrapper>> vec = make_func_wrapper_vector(rest...);
//     vec.emplace_back(std::make_unique<FuncWrapper<Ret, Params...>>(f));
//     return vec;
// }


// template<
//   typename T,
//   typename ResTy,
//   typename... FunctionRefT
// >
// class Base {
// public:
//   Base(T &a, T &b) : a(a), b(b) {}
//   Base(T &a, T &b, FunctionRefT... ctors) : a(a), b(b) {
//     for (size_t i = 0; i < sizeof...(FunctionRefT); ++i)
//       ctors.push_back(ctors...);
//   }
//   // ResTy test() {
//   //   std::cout << ctor(a, b) << std::endl;
//   //   return ctor(a, b);
//   // }
// private:
//   T a, b;
//   std::vector<std::unique_ptr<function_ref>> ctors;
// };

#include <memory>
#include <vector>
#include <functional> // 可能需要#include <functional>来使用std::function

// 抽象基类，用于类型擦除和统一接口
class CallableBase {
public:
  virtual ~CallableBase() = default;
  // 可以添加需要的虚函数，用于调用存储的回调
};

// 模板派生类，用于封装具体的function_ref<Ret(Params...)>
template<typename Ret, typename... Params>
class CallableWrapper : public CallableBase {
  function_ref<Ret(Params...)> func;

public:
  CallableWrapper(function_ref<Ret(Params...)> f) : func(f) {}

  // 示例函数，展示如何调用存储的function_ref
  Ret call(Params... args) {
    return func(args...);
  }
};

template<typename T, typename... FunctionRefT>
class Base {
public:
  Base(T &a, T &b) : a(a), b(b) {}

  // 使用变长模板参数和转发引用以及完美转发
  template<typename... Args>
  Base(T &a, T &b, Args&&... funcs) : a(a), b(b) {
    (ctors.push_back(std::make_unique<CallableWrapper<Args>>(std::forward<Args>(funcs))), ...);
  }

private:
  T a, b;
  std::vector<std::unique_ptr<CallableBase>> ctors; // 使用基类指针来存储任何类型的CallableWrapper
};

int sum(int a, int b) {
  return a + b;
}

int main(int argc, char **argv) {
  int x = 5, y = 10;

  Base<int, std::function<int(int, int)>> myBase(x, y, std::function<int(int, int)>(sum));
}
