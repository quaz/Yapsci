
#ifndef FUNCTION_OBJECT_HPP
#define FUNCTION_OBJECT_HPP

namespace yapsci {
  namespace misc {

    template<class Return_Type, class ... Params>
    class function_object {
      public:
        typedef function_object<Return_Type, Params ...> this_type;
        typedef this_type * pointer;
        virtual Return_Type operator() (Params ... params) const = 0;
        virtual Return_Type operator() (Params ... params) = 0;
        virtual ~function_object ();

        template<class Function_Type>
        static pointer create (Function_Type function);
    };

    template<class Function_Type, class Return_Type, class ... Params>
    class derived_function_object
      : public function_object<Return_Type, Params ...> {

      friend class function_object<Return_Type, Params ...>;

      public:
        virtual Return_Type operator() (Params ... params) const;
        virtual Return_Type operator() (Params ... params);
        virtual ~derived_function_object();

      private:

        derived_function_object(Function_Type function);

        Function_Type function_;
    };
  }
}

#include <inline/function_object.inl>

#endif
