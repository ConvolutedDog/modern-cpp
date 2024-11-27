#include "iostream"
#include <cassert>

template <typename DerivedT>
class Base {
public:
  Base(size_t uid) : uid(uid) {
    std::cout << "Call Base::Base." << std::endl;
  }
  void *func(size_t param1, size_t param2) {
#ifdef __clang__
    std::cout << "Call Base::func." << std::endl;
    assert(
      static_cast<void *(Base::*)(size_t, size_t)>(&Base::func) !=
      static_cast<void *(DerivedT::*)(size_t, size_t)>(&DerivedT::func) &&
      "Class derives from Base without implementing the core "
      "func(size_t, size_t) overload!"
    );
#endif
    return static_cast<DerivedT *>(this)->func(param1, param2);
  }
private:
  size_t uid;
};

class DerivedClass : public Base<DerivedClass> {
public:
  DerivedClass(size_t uid) : Base(uid) {
    std::cout << "Call DerivedClass::DerivedClass." << std::endl;
  }

  void *func(size_t param1, size_t param2) {
    std::cout << "Call DerivedClass::func." << std::endl;
    return static_cast<void *>(nullptr);
  }
};

class DerivedErrorClass : public Base<DerivedErrorClass> {
public:
  DerivedErrorClass(size_t uid) : Base(uid) {
    std::cout << "Call DerivedErrorClass::DerivedErrorClass." << std::endl;
  }

  // void *func(size_t param1, size_t param2) {
  //   std::cout << "Call DerivedErrorClass::func." << std::endl;
  //   return static_cast<void *>(nullptr);
  // }
};

int main(int argc, char *argv[]) {
  std::cout << "START." << std::endl;
  // Call Base::Base.
  Base<DerivedClass> BaseInstance(static_cast<size_t>(1));
  // Call Base::func.
  //   Call DerivedClass::func.
  BaseInstance.func(static_cast<size_t>(0), static_cast<size_t>(0));

  std::cout << "@" << std::endl;

  // Call Base::Base.
  //   Call DerivedClass::DerivedClass.
  DerivedClass DerivedClassInstance(static_cast<size_t>(2));
  // Call DerivedClass::func.
  DerivedClassInstance.func(static_cast<size_t>(0), static_cast<size_t>(0));

  std::cout << "@" << std::endl;

  // Call Base::Base.
  //   Call DerivedErrorClass::DerivedErrorClass.
  DerivedErrorClass DerivedErrorClassInstance(static_cast<size_t>(2));
  // Call Base::func.
  //   Assertion failed.
  DerivedErrorClassInstance.func(static_cast<size_t>(0), static_cast<size_t>(0));

  std::cout << "END." << std::endl;
  return 0;
}
