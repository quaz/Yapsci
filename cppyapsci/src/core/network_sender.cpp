
#include <network_sender.hpp>

#include <boost/bind.hpp>
#include <logger.hpp>

namespace yapsci {

  using misc::log;

  void network_sender::handle_resolve(const string & target,
                                      const boost::system::error_code & ec,
                                      boost::asio::ip::tcp::resolver::iterator it) {

    if (it == boost::asio::ip::tcp::resolver::iterator()) {
      log(3) << "Unknown host or service: " << target << "\n";
      return;
    }
    socket_ptr socket(new socket_type(wrapped()));
    try {
      boost::asio::connect(*socket, it);
    } catch (...) {
      log(3) << "Connection refused by " << it->endpoint().address().to_string()
             << ":" << it->endpoint().port() << "\n";
      return;
    }
    new_socket(socket);
  }

  void network_sender::connect_to(const string & host, const string & service) {
    log(4) << "Trying to get connection to " << host << ":" << service << "\n";
    boost::asio::ip::tcp::resolver::query query(host, service);
    resolver_.async_resolve(query, boost::bind(&network_sender::handle_resolve, this,
                                               host+":"+service,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::iterator));
  }
}
