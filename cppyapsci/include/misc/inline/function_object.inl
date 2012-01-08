
namespace yapsci {
  namespace misc {
    template<class Return_Type, class ... Params>
    inline function_object<Return_Type, Params ...>::~function_object () {
    }

    template<class Return_Type, class ... Params> template<class Function_Type>
    inline typename function_object<Return_Type, Params ...>::pointer
      function_object<Return_Type, Params ...>::create (Function_Type function) {

      return pointer(new derived_function_object<Function_Type, Return_Type, Params ...> (function));
    }

    template<class Function_Type, class Return_Type, class ... Params>
    inline Return_Type derived_function_object<Function_Type, Return_Type, Params ...>::operator() (Params ... params) const {

      function_(params ...);
    }

    template<class Function_Type, class Return_Type, class ... Params>
    inline Return_Type derived_function_object<Function_Type, Return_Type, Params ...>::operator() (Params ... params) {

      function_(params ...);
    }

    template<class Function_Type, class Return_Type, class ... Params>
    inline derived_function_object<Function_Type, Return_Type, Params ...>::~derived_function_object() {
    }

    template<class Function_Type, class Return_Type, class ... Params>
    inline derived_function_object<Function_Type, Return_Type, Params ...>::derived_function_object(Function_Type function)
      : function_(function) {
    }
  }
}
