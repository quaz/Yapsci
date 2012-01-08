
#include <socket_writer.hpp>

#include <logger.hpp>

namespace yapsci {

  using misc::log;

  void socket_writer::send (const string & message) {
    log(5) << "Scheduling message for sending: " << message
           << " to " << wrapped().remote_endpoint().address().to_string() << "\n";

    message_queue_.push(message);
    if (!writing_)
      write_next();
  }

  void socket_writer::write_next () {
    writing_ = true;
    boost::asio::async_write
      (wrapped(), boost::asio::buffer (message_queue_.front()),
       boost::bind (&socket_writer::handle_write, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
      );
  }

  void socket_writer::handle_write
    (const boost::system::error_code &, size_t) {

    log(4) << "Message sent successfully: " << message_queue_.front() << " to "
           << wrapped().remote_endpoint().address().to_string() << "\n";

    message_queue_.pop();
    if (!message_queue_.empty()) write_next();
    else writing_ = false;
  }
}
