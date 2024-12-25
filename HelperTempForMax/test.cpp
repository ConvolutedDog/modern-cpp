#include <iostream>
#include <functional> // for std::function

namespace Helper {
  template <typename First, typename... Rest>
  class MaxSizeOfType {
  private:
    enum {
      FirstValue = sizeof(First),
      RestValue = MaxSizeOfType<Rest...>::Value,
    };
  public:
    enum {
      Value = FirstValue > RestValue ? FirstValue : RestValue,
    };
  };
  
  template <typename First>
  class MaxSizeOfType<First> {
  public:
    enum {
      Value = sizeof(First),
    };
  };
}

#include "AggregateResultOfType.h"

// Example custom size function (could be more complex)
template <typename T>
constexpr int customSize(const T&) {
  return sizeof(T) * 2; // Double the size for example
}

int main(int argc, char **argv) {
  std::cout << Helper::MaxSizeOfType<
    unsigned, int, unsigned long long, long long, double, long double
  >::Value << std::endl;
  
  // Using sizeof
  auto sizeofFunc = [](auto x) { return sizeof(x) * 2; };
  auto cmpFunc = [](auto x, auto y) { return static_cast<size_t>(x) > static_cast<size_t>(y); };
  std::cout << "sizeof: " << AggregateResultOfType<
    decltype(sizeofFunc), decltype(cmpFunc), unsigned, long double
  >::Value << std::endl;

  // Using customSize
  auto customSizeFunc = [](auto T) { return customSize(T); };
  auto cmpFunc2 = [](auto x, auto y) { return x < y; };
  std::cout << "sizeof: " << AggregateResultOfType<
    decltype(customSizeFunc), decltype(cmpFunc2), unsigned, int, unsigned long long, long long, double, long double
  >::Value << std::endl;

  return 0;
}
