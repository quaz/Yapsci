
namespace yapsci {
  namespace misc {

    template<class T, class Pointer>
    template<class ... Args>
    Pointer creatable<T, Pointer>::create(Args ... args) {
      return Pointer (new T (args ...));
    }

    template<class T, class Pointer>
    creatable<T, Pointer>::~creatable() {
    }
  }
}
