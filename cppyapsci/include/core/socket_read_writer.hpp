
#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include <socket_writer.hpp>
#include <socket_reader.hpp>
#include <creatable.hpp>

namespace yapsci {

  class socket_read_writer
    : public socket_reader , public socket_writer
    , public misc::creatable<socket_read_writer, boost::shared_ptr<socket_read_writer> > {

    friend class misc::creatable<socket_read_writer, boost::shared_ptr<socket_read_writer> >;

    private:

      typedef socket_read_writer this_type;

      typedef misc::wrapper<boost::asio::ip::tcp::socket,
                            boost::shared_ptr<boost::asio::ip::tcp::socket>
                           > socket_wrapper;

    public:

      typedef boost::shared_ptr<this_type> pointer;
      typedef socket_wrapper::pointer socket_ptr;
      typedef socket_reader::string string;
      typedef socket_reader::input_handler input_handler;

      virtual ~socket_read_writer();

      //TODO: find some neat solution for this... if I leave the following out, I get a "call ambiguous" error whenever calling socket_read_writer::create
      template<class ... Args>
      static pointer create(Args ... args);


    protected:

      template<class Function_Type>
      socket_read_writer (const socket_ptr & socket, const Function_Type & handler);
  };
}

#include "inline/socket_read_writer.inl"

#endif

