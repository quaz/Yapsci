
#ifndef CREATABLE_HPP
#define CREATABLE_HPP

namespace yapsci {
  namespace misc {

    template<class T, class Pointer = T * >
    class creatable {
      public:

        template<class ... Args>
        static Pointer create (Args ... args);

        virtual ~creatable();
    };

  }
}

#include "inline/creatable.inl"

#endif
