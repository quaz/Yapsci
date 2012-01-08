
#ifndef SOCKET_WRAPPER_HPP
#define SOCKET_WRAPPER_HPP

namespace yapsci {
  namespace misc {

    template<class T, class Pointer = T *>
    class wrapper {

      public:

        typedef T value_type;
        typedef Pointer pointer;
        virtual ~wrapper();

      protected:

        wrapper(const pointer & value);
        const value_type & wrapped() const;
        value_type & wrapped();

      private:

        pointer wrapped_;
    };
  }
}

#include "inline/wrapper.inl"

#endif

