
#ifndef SOCKET_CREATOR_HPP
#define SOCKET_CREATOR_HPP

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <function_object.hpp>

namespace yapsci {

  class socket_creator {

    public:

      typedef boost::asio::ip::tcp::socket socket_type;
      typedef boost::shared_ptr<socket_type> socket_ptr;

      virtual ~socket_creator();

    protected:

      template<class Function_Type>
      socket_creator(const Function_Type & handler);

      void new_socket (const socket_ptr & socket);

    private:

      typedef misc::function_object<void, const socket_ptr &> socket_handler;
      typedef socket_handler * socket_handler_ptr;

      socket_handler_ptr socket_handler_;
  };
}

#include "inline/socket_creator.inl"

#endif
