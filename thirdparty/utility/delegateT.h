#pragma once

#include <typeinfo>

template <typename Return, typename... Args> class StaticDelegateT;

template <typename T, typename Return, typename... Args>
class ClassMemberDelegateT;

template <typename Return, typename... Args> class DelegateT {
public:
  DelegateT() = default;
  virtual ~DelegateT() = default;
  virtual bool isType(const std::type_info &_type) = 0;
  virtual bool canInvoke() const = 0;
  virtual Return invoke(Args... args) = 0;
  virtual bool compare(DelegateT<Return, Args...> *_delegate) const = 0;
};

template <typename Return, typename... Args>
class StaticDelegateT<Return (*)(Args...)> : public DelegateT<Return, Args...> {

public:
  typedef Return (*InvokeFun)(Args...);
  explicit StaticDelegateT(InvokeFun _fun) : invoke_fun_(_fun) {}
  virtual ~StaticDelegateT() = default;
  bool isType(const std::type_info &_type) override {
    return typeid(StaticDelegateT<Return (*)(Args...)>) == _type;
  }
  Return invoke(Args... args) override {
    return invoke_fun_(std::forward<Args>(args)...);
  }
  bool compare(DelegateT<Return, Args...> *_delegate) const override {
    if (!_delegate ||
        !_delegate->isType(typeid(StaticDelegateT<Return (*)(Args...)>))) {
      return false;
    }

    auto *cast =
        dynamic_cast<StaticDelegateT<Return (*)(Args...)> *>(_delegate);

    return invoke_fun_ == cast->invoke_fun_;
  }
  bool canInvoke() const override { return invoke_fun_; }

private:
  InvokeFun invoke_fun_ = nullptr;
};

template <typename T, typename Return, typename... Args>
class ClassMemberDelegateT<T, Return (T::*)(Args...)>
    : public DelegateT<Return, Args...> {
public:
  typedef Return (T::*memInvokeFun)(Args...);

  ClassMemberDelegateT(T *_object, memInvokeFun _memfun)
      : obj(_object), invoke_fun_(_memfun) {}
  virtual bool isType(const std::type_info &_type) override {
    return typeid(ClassMemberDelegateT<T, Return (T::*)(Args...)>) == _type;
  }
  Return invoke(Args... args) override {
    return (obj->*invoke_fun_)(std::forward<Args>(args)...);
  }
  bool compare(DelegateT<Return, Args...> *_delegate) const override {
    if (!_delegate || !_delegate->isType(typeid(
                          ClassMemberDelegateT<T, Return (T::*)(Args...)>))) {
      return false;
    }

    auto *cast =
        dynamic_cast<ClassMemberDelegateT<T, Return (T::*)(Args...)> *>(
            _delegate);
    return invoke_fun_ == cast->invoke_fun_ && obj == cast->obj;
  }
  virtual bool canInvoke() const override { return (obj && invoke_fun_); }

private:
  memInvokeFun invoke_fun_ = nullptr;
  T *obj = nullptr;
};

template <typename Fun> inline StaticDelegateT<Fun> *new_delegate(Fun _fun) {
  return new StaticDelegateT<Fun>(_fun);
}

template <typename T, typename Fun>
inline ClassMemberDelegateT<T, Fun> *new_delegate(T *_object, Fun _fun) {
  return new ClassMemberDelegateT<T, Fun>(_object, _fun);
}