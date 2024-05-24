#pragma once

#include "delegateT.h"
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

template <typename Return, typename... Args> class Delegate;

template <typename Return, typename... Args> class Delegate<Return(Args...)> {
  typedef std::shared_ptr<DelegateT<Return, Args...>> ptr;
  std::vector<ptr> invoke_delegates;
  std::mutex _mutex;

public:
  Delegate() = default;
  ~Delegate() { clear(); }
  void clear() { invoke_delegates.clear(); }

  template <typename Fun> void add(Fun _fun) {
    std::unique_lock<std::mutex> l(this->_mutex);
    ptr oneDelegate(new_delegate(_fun));
    if (oneDelegate) {
      for (auto &_invokeObj : invoke_delegates) {
        if (oneDelegate->compare(_invokeObj.get())) {
          return;
        }
      }
      invoke_delegates.emplace_back(oneDelegate);
    }
  }

  template <typename T, typename Fun> void add(T *_object, Fun _fun) {
    std::unique_lock<std::mutex> l(this->_mutex);
    ptr oneDelegate(new_delegate(_object, _fun));
    if (oneDelegate) {
      for (auto &_invokeObj : invoke_delegates) {
        if (oneDelegate->compare(_invokeObj.get())) {
          return;
        }
      }
      invoke_delegates.emplace_back(oneDelegate);
    }
  }

  template <typename Fun> void remove(Fun _fun) {
    std::unique_lock<std::mutex> l(this->_mutex);
    ptr oneDelegate(new_delegate(_fun));
    if (oneDelegate) {
      auto it = invoke_delegates.begin();
      while (it != invoke_delegates.end()) {
        if (oneDelegate->compare(it.get())) {
          invoke_delegates.erase(it);
          return;
        }
        ++it;
      }
    }
  }

  template <typename T, typename Fun> void remove(T *_object, Fun _fun) {
    std::unique_lock<std::mutex> l(this->_mutex);
    ptr oneDelegate(new_delegate(_object, _fun));
    if (oneDelegate) {
      auto it = invoke_delegates.begin();
      while (it != invoke_delegates.end()) {
        if (oneDelegate->compare(it->get())) {
          invoke_delegates.erase(it);
          return;
        }
        ++it;
      }
    }
  }

  std::vector<Return> operator()(Args... args) {
    std::vector<Return> vecRt;
    for (auto &_invokeObj : invoke_delegates) {
      if (_invokeObj && _invokeObj->canInvoke()) {
        vecRt.push_back(_invokeObj->invoke(std::forward<Args>(args)...));
      }
    }
    return vecRt;
  }
};

template <typename... Args> class Delegate<void(Args...)> {
  typedef std::shared_ptr<DelegateT<void, Args...>> ptr;
  std::vector<ptr> invoke_delegates;
  std::mutex _mutex;

public:
  Delegate() = default;
  ~Delegate() { clear(); }

  void clear() { invoke_delegates.clear(); }

  template <typename Fun> void add(Fun &&_fun) {
    _mutex.lock();
    ptr oneDelegate(new_delegate(_fun));
    if (oneDelegate) {
      for (auto &_invokeObj : invoke_delegates) {
        if (oneDelegate->compare(_invokeObj.get())) {
          _mutex.unlock();
          return;
        }
      }
      invoke_delegates.emplace_back(oneDelegate);
    }
    _mutex.unlock();
  }

  template <typename T, typename Fun> void add(T *_object, Fun &&_fun) {
    _mutex.lock();
    ptr oneDelegate(new_delegate(_object, _fun));
    if (oneDelegate) {
      for (auto &_invokeObj : invoke_delegates) {
        if (oneDelegate->compare(_invokeObj.get())) {
          _mutex.unlock();
          return;
        }
      }
      invoke_delegates.emplace_back(oneDelegate);
    }
    _mutex.unlock();
  }

  template <typename Fun> void remove(Fun &&_fun) {
    _mutex.lock();
    ptr oneDelegate(new_delegate(_fun));
    if (oneDelegate) {
      auto it = invoke_delegates.begin();
      while (it != invoke_delegates.end()) {
        if (oneDelegate->compare(it.get())) {
          invoke_delegates.erase(it);
          _mutex.unlock();
          return;
        }
        ++it;
      }
    }
    _mutex.unlock();
  }

  template <typename T, typename Fun> void remove(T *_object, Fun &&_fun) {
    _mutex.lock();
    ptr oneDelegate(new_delegate(_object, _fun));
    if (oneDelegate) {
      auto it = invoke_delegates.begin();
      while (it != invoke_delegates.end()) {
        if (oneDelegate->compare(it->get())) {
          invoke_delegates.erase(it);
          _mutex.unlock();
          return;
        }
        ++it;
      }
    }
    _mutex.unlock();
  }

  void operator()(Args... args) {
    for (auto &_invokeObj : invoke_delegates) {
      if (_invokeObj && _invokeObj->canInvoke()) {
        _invokeObj->invoke(std::forward<Args>(args)...);
      }
    }
  }
};