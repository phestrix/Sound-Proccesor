#ifndef FACTORY
#define FACTORY
#include <map>

template <class ID, class Base, class... Args>
class Factory {
 private:
  typedef Base* (*finstantiator)(Args...);

  template <class Derived>
  static Base* instantiator(Args... args) {
    return new Derived(args...);
  }

  std::map<ID, finstantiator> classes;

 public:
  Factory(){};

  template <class Derived>
  void add(ID id) {
    classes[id] = &instantiator<Derived>;
  }

  inline finstantiator get(ID id) { return classes[id]; }
};

#endif