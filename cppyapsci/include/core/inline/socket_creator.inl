
#include <logger.hpp>

namespace yapsci {

  inline socket_creator::~socket_creator() {
    delete socket_handler_;
  }

  template<class Function_Type>
  inline socket_creator::socket_creator (const Function_Type & handler)
    : socket_handler_(socket_handler::create(handler)) {
  }

  inline void socket_creator::new_socket (const socket_ptr & socket) {
    misc::log(3) << "New socket to " << socket->remote_endpoint().address().to_string()
                 << ":" << socket->remote_endpoint().port() << "\n";
    (*socket_handler_)(socket);
  }
}
