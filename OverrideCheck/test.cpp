#include "iostream"
#include <cassert>

template <typename DerivedT>
class Base {
public:
  Base(size_t uid) : uid(uid) {
    std::cout << "Call Base::Base." << std::endl;
  }

  void X();

  void *func(size_t param1, size_t param2) {
#if defined(__clang__) || defined(__GNUC__)
    std::cout << "Call Base::func." << std::endl;
    // 没有对 Base::func 重载会触发 static_cast 失败。
    assert(
      // static_cast<void *(Base::*)(size_t, size_t)> 将这个地址强制转换为一个
      // 特定类型的成员函数指针。转换的目标类型是一个指向 Base 类的成员函数的指针，
      // 这个成员函数接受两个 size_t 类型的参数，并返回一个 void* 类型的指针。
      //
      // &Base::func 获取 Base 类中名为 func 的成员函数的地址。
      // void* 表示函数返回类型是一个指向 void 的指针，即一个通用指针，可以指向任
      // 何类型。
      // (Base::*) 表示这是一个指向 Base 类成员的指针。
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

template <typename X, template <typename _X = X> class DerivedT>
class BaseX {
public:
  BaseX(size_t uid) : uid(uid) {
    std::cout << "Call BaseX::BaseX." << std::endl;
  }

  void *func(size_t param1, size_t param2) {
#if defined(__clang__) || defined(__GNUC__)
    std::cout << "Call BaseX::func." << std::endl;
    // 没有对 BaseX::func 重载会触发 static_cast 失败。
    assert(
      // static_cast<void *(BaseX::*)(size_t, size_t)> 将这个地址强制转换为一个
      // 特定类型的成员函数指针。转换的目标类型是一个指向 BaseX 类的成员函数的指针，
      // 这个成员函数接受两个 size_t 类型的参数，并返回一个 void* 类型的指针。
      //
      // &BaseX::func 获取 BaseX 类中名为 func 的成员函数的地址。
      // void* 表示函数返回类型是一个指向 void 的指针，即一个通用指针，可以指向任
      // 何类型。
      // (BaseX::*) 表示这是一个指向 BaseX 类成员的指针。
      static_cast<void *(BaseX::*)(size_t, size_t)>(&BaseX::func) !=
      static_cast<void *(DerivedT<X>::*)(size_t, size_t)>(&DerivedT<X>::func) &&
      "Class derives from Base without implementing the core "
      "func(size_t, size_t) overload!"
    );
#endif
    return static_cast<DerivedT<X> *>(this)->func(param1, param2);
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

template <typename X>
class DerivedClassX : public BaseX<X, DerivedClassX> {
public:
  DerivedClassX(size_t uid) : BaseX<X, DerivedClassX>(uid) {
    std::cout << "Call DerivedClassX::DerivedClassX." << std::endl;
  }
  
  // 没有对 Base 重载会触发 static_cast 失败。
  // void *func(size_t param1, size_t param2) {
  //   std::cout << "Call DerivedClassX::func." << std::endl;
  //   return static_cast<void *>(nullptr);
  // }
};

class DerivedErrorClass : public Base<DerivedErrorClass> {
public:
  DerivedErrorClass(size_t uid) : Base(uid) {
    std::cout << "Call DerivedErrorClass::DerivedErrorClass." << std::endl;
  }

  // 没有对 Base 重载会触发 static_cast 失败。
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
  // DerivedErrorClassInstance.func(static_cast<size_t>(0), static_cast<size_t>(0));

  std::cout << "END." << std::endl;

  DerivedClassX<int> DerivedClassXInstance(static_cast<size_t>(2));
  DerivedClassXInstance.func(static_cast<size_t>(0), static_cast<size_t>(0));

  return 0;
}
