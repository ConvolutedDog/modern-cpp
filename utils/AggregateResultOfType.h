//===----------------------------------------------------------------------===//
//
//                         AggregateResultOfType.h
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//     Features from C++20
//===----------------------------------------------------------------------===//

// This file defines the AggregateResultOfType class template, which recursively
// computes the aggregate result of applying an aggregate function to a variadic
// number of types.

template <typename AggregateFunc, typename CmpFunc, 
          typename First, typename... Rest>
class AggregateResultOfType {
private:
  // Computes the result of applying AggregateFunc to the first type. Adds a
  // static assertion to ensure the result is an integer.
  static_assert(std::is_integral_v<std::decay_t<decltype(AggregateFunc{}(First{}))>>, 
                "AggregateFunc must return an integral type");
  // Compute the result of applying the aggregate function to the first type.
  const static size_t  FirstValue = AggregateFunc{}(First{});

  // Recursively compute the aggregate result for the remaining types.
  const static size_t  RestValue = AggregateResultOfType<AggregateFunc, CmpFunc, Rest...>::Value;

public:
  // The aggregate result obtained by comparing the result for the first type
  // with the aggregate result for the remaining types.
  const static size_t  Value = CmpFunc{}(FirstValue, RestValue) ? FirstValue : RestValue;
};

// Specialization for the base case (single type).
template <typename AggregateFunc, typename CmpFunc, typename First>
class AggregateResultOfType<AggregateFunc, CmpFunc, First> {
public:
  // Computes the result of applying AggregateFunc to the first type. Adds a
  // static assertion to ensure the result is an integer.
  static_assert(std::is_integral_v<std::decay_t<decltype(AggregateFunc{}(First{}))>>, 
                "AggregateFunc must return an integral type");
  // The result of applying the aggregate function to the single type.
  const static size_t  Value = AggregateFunc{}(First{});
};

//===----------------------------------------------------------------------===//
