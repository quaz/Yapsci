
namespace yapsci {

  inline network_seti::~network_seti() {
    for (auto acc : acceptors_)
      delete acc.second;
  }

  template<class Function_Type>
  inline network_seti::network_seti
    (io_service & service, const Function_Type & handler)
    : socket_creator(handler)
    , misc::wrapper<boost::asio::io_service> (&service)
    , acceptors_() {
  }

  inline void network_seti::start_listen (unsigned short port, protocol p) {
    start_listen(identifier(port, p));
  }

  inline void network_seti::stop_listen (unsigned short port, protocol p) {
    stop_listen(identifier(port, p));
  }

  inline void network_seti::handle_accept (
    const identifier & id, socket_ptr socket, const boost::system::error_code & ec
  ) {
    new_socket(socket);
    accept(id);
  }
}
