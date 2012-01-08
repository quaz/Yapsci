
namespace yapsci {

  inline socket_read_writer::~socket_read_writer() {
  }

  template<class ... Args>
  socket_read_writer::pointer socket_read_writer::create (Args ... args) {
   return misc::creatable<this_type, pointer>::create(args ...);
  }

  template<class Function_Type>
  socket_read_writer::socket_read_writer(const socket_ptr & socket, const Function_Type & handler)
    : socket_wrapper(socket) , socket_reader(socket, handler) , socket_writer(socket) {
  }

}
