#include <boost/bind.hpp>

#include <logger.hpp>

namespace yapsci {

  using misc::log;

  inline socket_reader::~socket_reader() {
    delete handler_;
  }

  inline void socket_reader::submit_input () {
    (*handler_) (input_);
    input_.clear();
  }

  template<class Function_Type>
  inline socket_reader::socket_reader (const socket_ptr & socket, const Function_Type & handler)
    : socket_wrapper (socket), handler_(raw_input_handler::create(handler)), listening_ (false), input_buffer_() {
  }

  inline void socket_reader::stop_listen () {
    log(3) << "Stop listening for incoming messages from "
           << wrapped().remote_endpoint().address().to_string() << "\n";
    listening_ = false;
  }
}
