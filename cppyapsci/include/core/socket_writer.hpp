
#ifndef SOCKET_WRITER_HPP
#define SOCKET_WRITER_HPP

#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <queue>
#include <wrapper.hpp>
#include <creatable.hpp>

namespace yapsci {

  class socket_writer
    : virtual public misc::wrapper<boost::asio::ip::tcp::socket,
                                   boost::shared_ptr<boost::asio::ip::tcp::socket> >
    , public misc::creatable<socket_writer, boost::shared_ptr<socket_writer> > {

    friend class misc::creatable<socket_writer, boost::shared_ptr<socket_writer> >;

    private:

      typedef socket_writer this_type;

      typedef misc::wrapper<boost::asio::ip::tcp::socket,
                            boost::shared_ptr<boost::asio::ip::tcp::socket>
                           > socket_wrapper;

    public:

      typedef this_type * pointer;
      typedef socket_wrapper::pointer socket_ptr;
      typedef std::string string;

      void send (const string & message);

      virtual ~socket_writer();

    protected:

      socket_writer (const socket_ptr & socket);

    private:

      void write_next();
      void handle_write (const boost::system::error_code & ec, size_t bytes_sent);

      std::queue<string> message_queue_; //TODO: make this thread-safe!
      bool writing_;
  };
}

#include "inline/socket_writer.inl"

#endif

