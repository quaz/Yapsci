
#include <socket_reader.hpp>

namespace yapsci {

  using misc::log;

  void socket_reader::start_listen () {
    if (listening_) return;
    log(3) << "Start listening for incoming messages from "
           << wrapped().remote_endpoint().address().to_string() << "\n";
    listening_ = true;
    listen();
  }

  void socket_reader::handle_input
    (const boost::system::error_code & ec, std::size_t bytes_transferred) {

    if (ec == boost::asio::error::eof) {
        log(3) << "Connection closed by peer" << "\n";
        return;
    } else if (ec) {
      log(1) << "ERROR reading from connection: "
             << wrapped().remote_endpoint().address().to_string()
             << " Error code: " << ec << "\n";
    }

    if (bytes_transferred != input_buffer_.size() )
      log(1) << "ERROR reading from connection: Unknown error\n";

    string input;
    for (auto c : input_buffer_) input.push_back (c);
    input_.append (input);
    log(5) << "Data received from "
           << wrapped().remote_endpoint().address().to_string()
           << ": " << input << "\n";

    submit_input();
    if (listening_) listen();
  }

  void socket_reader::listen() {
    boost::asio::async_read
      (wrapped(), boost::asio::buffer (input_buffer_),
       boost::bind (&socket_reader::handle_input, this->shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                   )
      );
  }
}
