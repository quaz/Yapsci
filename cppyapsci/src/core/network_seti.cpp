
#include <network_seti.hpp>

#include <logger.hpp>
#include <boost/bind.hpp>

namespace yapsci {

  using misc::log;

  void network_seti::start_listen (const identifier & id) {
    log(3) << "Start listening on port " << std::get<0>(id) << "\n"; //TODO: add comment about protocol

    acceptor_ptr acc(
      new acceptor(
        wrapped(),
        boost::asio::ip::tcp::endpoint (map_protocol(std::get<1>(id)), std::get<0>(id))
      )
    );
    auto it = acceptors_.insert(std::make_pair(id, acc));
    if (!it.second) {
      log(3) << "Was already listening\n";
      delete acc;
      return;
    }
    accept(id);
  }

  void network_seti::stop_listen (const identifier & id) {
    log(3) << "Stop listening on port " << std::get<0>(id) << "\n"; //TODO: add comment about protocol

    auto it = acceptors_.find(id);
    it->second->cancel();
    delete it->second;
    acceptors_.erase(it);
  }

  void network_seti::accept (const identifier & id) {
    socket_ptr socket(new socket_type(wrapped()));
    acceptors_[id]->async_accept(*socket,
                                 boost::bind(&network_seti::handle_accept,
                                             this,
                                             id, socket,
                                             boost::asio::placeholders::error
                                            )
                                );
  }

  boost::asio::ip::tcp::endpoint::protocol_type
    network_seti::map_protocol (protocol p) {

    switch (p) {
      default:
      case protocol::IPV4:
        return boost::asio::ip::tcp::v4();
      case protocol::IPV6:
        return boost::asio::ip::tcp::v6();
    }
  }
}
