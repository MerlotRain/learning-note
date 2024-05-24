#pragma once

#include "delegate.h"
#include <atomic>
class NoneCopyable {
public:
  NoneCopyable() = default;
  virtual ~NoneCopyable() = default;

private:
  NoneCopyable(const NoneCopyable &) = delete;
  NoneCopyable &operator=(const NoneCopyable &) = delete;
};
class RefObject : public NoneCopyable {
protected:
  std::atomic_int m_refCount;

public:
  RefObject() { m_refCount = 0; }
  virtual ~RefObject() = default;
  virtual int addRef() noexcept {
    m_refCount.fetch_add(1);
    return m_refCount.load();
  }
  virtual int release() noexcept {
    m_refCount.fetch_sub(1);
    int count = m_refCount.load();
    if (count == 0) {
      onDestructor(this);
      delete this;
    }
    return count;
  }
  virtual int refCount() noexcept { return m_refCount.load(); }
  template <class T> T *castTo() noexcept { return dynamic_cast<T *>(this); }
  template <class T> bool instanceOf() noexcept {
    return dynamic_cast<T *>(this) ? true : false;
  }
  Delegate<void(RefObject *)> onDestructor;
};

class WeakReference : public RefObject {
  RefObject *m_refObject;

  void onDestructor(RefObject *obj) {
    if (obj == m_refObject)
      m_refObject = nullptr;
  }

public:
  WeakReference(RefObject *object) : m_refObject(object) {
    m_refObject->onDestructor.add(this, &WeakReference::onDestructor);
  }
  ~WeakReference() { m_refObject = nullptr; }

  RefObject *lock() {
    if (m_refObject) {
      m_refObject->addRef();
    }
    return m_refObject;
  }

  bool expired() { return (!m_refObject || m_refObject->refCount() == 0); }
};

template <class T> class SmarterPtr {
public:
  T *p;

  SmarterPtr() noexcept { p = NULL; }

  SmarterPtr(int nNull) noexcept { p = NULL; }

  SmarterPtr(long int nNull) noexcept { p = NULL; }

  template <class O> SmarterPtr(O *lp, bool bAddRef = true) noexcept {
    p = dynamic_cast<T *>(lp);
    if (p != NULL && bAddRef)
      p->addRef();
  }

  template <class O> SmarterPtr(const SmarterPtr<O> &lp) noexcept {
    p = dynamic_cast<T *>(lp.p);
    if (p != NULL)
      p->addRef();
  }

  SmarterPtr(const SmarterPtr<T> &lp) noexcept {
    p = lp.p;
    if (p != NULL)
      p->addRef();
  }

  SmarterPtr(const RefObject *lp, bool bAddRef = true) noexcept {
    p = dynamic_cast<T *>(lp);
    if (p != NULL && bAddRef)
      p->addRef();
  }

  explicit SmarterPtr(T *lp, bool bAddRef = true) noexcept {
    p = lp;
    if (p != NULL && bAddRef)
      p->addRef();
  }

public:
  ~SmarterPtr() noexcept {
    if (p)
      p->release();
  }
  template <class Q> SmarterPtr<Q> ad() {
    if (!p)
      return 0;
    return dynamic_cast<Q *>(p);
  }
  template <class Q> bool is() {
    if (!p)
      return false;
    return dynamic_cast<Q *>(p) != 0;
  }

  operator T *() const noexcept { return p; }

  operator RefObject *() const noexcept { return p; }

  explicit operator bool() const noexcept { return 0 != p; }

  T &operator*() const { return *p; }

  T *operator->() const noexcept { return p; }

  bool operator!() const noexcept { return (p == 0); }

  bool operator<(T *pT) const noexcept { return p < pT; }

  void addRef() noexcept {
    if (p)
      p->addRef();
  }
  void release() noexcept {
    T *pTemp = p;
    if (pTemp) {
      p = NULL;
      pTemp->release();
    }
  }
  bool isEqualObject(RefObject *pOther) noexcept {
    if (p == NULL && pOther == NULL)
      return true;
    if (p == NULL || pOther == NULL)
      return false;
    RefObject *p1 = dynamic_cast<RefObject *>(p);
    return p1 == pOther;
  }
  void attach(T *p2) noexcept {
    if (p)
      p->release();
    p = p2;
  }
  T *detach() noexcept {
    T *pt = p;
    p = NULL;
    return pt;
  }
  bool copyTo(T **ppT) noexcept {
    if (ppT == NULL)
      return false;
    *ppT = p;
    if (p)
      p->addRef();
    return true;
  }

  T *operator=(T *lp) noexcept {
    if (p != NULL)
      if (this->p == lp)
        return *this;
    if (lp)
      lp->addRef();
    attach(lp);
    return *this;
  }
  T *operator=(const SmarterPtr<T> &lp) noexcept {
    if (this->p != lp.p) {
      if (lp)
        lp->addRef();
      attach(lp);
    }
    return *this;
  }
};

template <class T, class Q>
bool operator==(const SmarterPtr<T> &lp1, const SmarterPtr<Q> &lp2) noexcept {
  return (lp1.p == lp2.p);
}

template <class T, class Q>
bool operator!=(const SmarterPtr<T> &lp1, const SmarterPtr<Q> &lp2) noexcept {
  return lp1.p != lp2.p;
}

template <class T>
bool operator==(const SmarterPtr<T> &lp, std::nullptr_t) noexcept {
  return lp.p == nullptr;
}

template <class T>
bool operator==(std::nullptr_t, const SmarterPtr<T> &lp) noexcept {
  return nullptr == lp.p;
}

template <class T>
bool operator!=(const SmarterPtr<T> &lp, std::nullptr_t) noexcept {
  return lp.p != nullptr;
}

template <class T>
bool operator!=(std::nullptr_t, const SmarterPtr<T> &lp) noexcept {
  return nullptr != lp.p;
}

template <class T> class WeakSmarterPtr {
  WeakReference *m_WeakRef;

public:
  WeakSmarterPtr() : m_WeakRef(NULL) {}
  WeakSmarterPtr(T *obj) : m_WeakRef(NULL) {
    if (!obj)
      return;
    m_WeakRef = new WeakReference(obj);
    m_WeakRef->addRef();
  }

  WeakSmarterPtr(const SmarterPtr<T> &obj) : m_WeakRef(NULL) {
    if (!obj.p)
      return;
    m_WeakRef = new WeakReference(obj.p);
    m_WeakRef->addRef();
  }
  WeakSmarterPtr(const WeakSmarterPtr<T> &weak) : m_WeakRef(NULL) {
    reset(weak);
  }
  ~WeakSmarterPtr() {
    if (m_WeakRef)
      m_WeakRef->release();
  }

  bool expired() {
    if (!m_WeakRef)
      return true;
    return m_WeakRef->expired();
  }
  operator bool() { return !expired(); }

  void reset() {
    if (m_WeakRef)
      m_WeakRef->release();
    m_WeakRef = NULL;
  }
  void reset(const WeakSmarterPtr<T> &weak) {
    if (weak.m_WeakRef)
      weak.m_WeakRef->addRef();
    reset();
    m_WeakRef = weak.m_WeakRef;
  }
  void reset(const SmarterPtr<T> &obj) { reset(obj.p); }

  void reset(T *obj) {
    reset();
    if (!obj)
      return;
    m_WeakRef = new WeakReference(obj);
    m_WeakRef->addRef();
  }

  WeakSmarterPtr<T> &operator=(const WeakSmarterPtr<T> &right) {
    reset(right);
    return *this;
  }
  WeakSmarterPtr<T> &operator=(T *right) {
    reset(right);
    return *this;
  }

  WeakSmarterPtr<T> &operator=(const SmarterPtr<T> &right) {
    reset(right);
    return *this;
  }
  SmarterPtr<T> lock() const {
    if (!m_WeakRef)
      return SmarterPtr<T>();

    RefObject *ref = m_WeakRef->lock();
    if (!ref)
      return SmarterPtr<T>();
    return SmarterPtr<T>(ref, false);
  }
};

#define SMARTER_PTR(P)                                                         \
  typedef SmarterPtr<P> P##Ptr;                                                \
  typedef WeakSmarterPtr<P> P##WPtr;