
namespace yapsci {
 namespace misc {

  template<class T, class Pointer>
  inline wrapper<T, Pointer>::wrapper(const pointer & value)
    : wrapped_ (value) {
  }

  template<class T, class Pointer>
  inline const typename wrapper<T, Pointer>::value_type & wrapper<T, Pointer>::wrapped() const {
    return *wrapped_;
  }

  template<class T, class Pointer>
  inline typename wrapper<T, Pointer>::value_type & wrapper<T, Pointer>::wrapped() {
    return *wrapped_;
  }

  template<class T, class Pointer>
  inline wrapper<T, Pointer>::~wrapper() {
  }
 }
}
