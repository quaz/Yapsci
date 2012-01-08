
namespace yapsci {

  inline socket_writer::~socket_writer() {
  }

  inline socket_writer::socket_writer (const socket_ptr & socket)
    : socket_wrapper (socket), message_queue_(), writing_(false) {
  }
}
