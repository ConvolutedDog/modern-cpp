#include <iostream>
#include <functional>
#include "function_ref.h"

template<
  typename T,
  typename ResTy,
  typename FunctionRefT
>
class Base {
public:
  Base(T &a, T &b) : a(a), b(b) {}
  Base(T &a, T &b, FunctionRefT ctor) : a(a), b(b), ctor(ctor) {}
  ResTy test() {
    std::cout << ctor(a, b) << std::endl;
    return ctor(a, b);
  }
private:
  T a, b;
  FunctionRefT ctor;
};

int main(int argc, char **argv) {
  size_t a = 5, b = 2;
  Base<size_t, bool, function_ref<bool (size_t &, size_t &)>> x(
    a, b, [](size_t &a, size_t &b) { return a > b; }
  );
  x.test();

  Base<size_t, size_t, function_ref<size_t (size_t &, size_t &)>> x1(
    a, b, [](size_t &a, size_t &b) { return a + b; }
  );
  x1.test();

  Base<size_t, size_t, function_ref<size_t (size_t &, size_t &)>> x2(
    a, b, [](size_t &a, size_t &b) { return a - b; }
  );
  x2.test();
}
