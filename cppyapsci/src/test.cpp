
#include <socket_read_writer.hpp>
#include <network_connector.hpp>
#include <logger.hpp>
#include <boost/asio.hpp>

using yapsci::socket_read_writer;

#include <iostream>

socket_read_writer::pointer con;


void foo (socket_read_writer::string input) {
  if (input.size() == 1) con->stop_listen();
}
void bar (const yapsci::network_connector::socket_ptr & socket) {
  con = socket_read_writer::create(socket, foo);
  con->send("foo");
  con->start_listen();
  con->send("bar");
}

int main (int argc, const char ** argv) {

  //if (argc != 3) {
  //  std::cout << "Usage: yapsci <host> <port>" << std::endl;
  //  return 1;
  //}
  yapsci::misc::log(5).fix_level();

  boost::asio::io_service io_service;

  //auto ns = yapsci::network_sender::create (std::ref(io_service), bar);
  //ns->connect_to(argv[1], argv[2]);
  auto nc = yapsci::network_connector::create (std::ref(io_service), bar);
  nc->start_listen(1338, yapsci::protocol::IPV4);
  nc->connect_to(argv[1], argv[2]);

  io_service.run();

  return 0;
}

/*
class tcp_server {
  public:
    tcp_server (boost::asio::io_service & io_service)
      : acceptor_ (io_service, tcp::endpoint (tcp::v4(), 13) ) {

      start_accept();
    }

  private:
    void start_accept() {
      tcp_connection::pointer new_connection =
        tcp_connection::create (acceptor_.get_io_service() );

      acceptor_.async_accept (new_connection->socket(),
                              boost::bind (&tcp_server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error) );
    }

    void handle_accept (tcp_connection::pointer new_connection,
                        const boost::system::error_code & error) {
      if (!error) {
          new_connection->start();
        }

      start_accept();
    }

    tcp::acceptor acceptor_;
};

int main() {
  try {
      boost::asio::io_service io_service;
      tcp_server server (io_service);
      io_service.run();
    }
  catch (std::exception & e) {
      std::cerr << e.what() << std::endl;
    }

  return 0;
}
*/
