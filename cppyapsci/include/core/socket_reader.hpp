
#ifndef SOCKET_READER_HPP
#define SOCKET_READER_HPP

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <function_object.hpp>
#include <wrapper.hpp>
#include <creatable.hpp>

namespace yapsci {

  class socket_reader
    : virtual public misc::wrapper<boost::asio::ip::tcp::socket,
                                   boost::shared_ptr<boost::asio::ip::tcp::socket> >
    , public boost::enable_shared_from_this<socket_reader>
    , public misc::creatable<socket_reader, boost::shared_ptr<socket_reader> > {

    friend class misc::creatable<socket_reader, boost::shared_ptr<socket_reader> >;

    public:

      typedef std::string string;

    private:

      typedef misc::wrapper<boost::asio::ip::tcp::socket,
                            boost::shared_ptr<boost::asio::ip::tcp::socket>
                           > socket_wrapper;

      typedef socket_reader this_type;
      static constexpr unsigned short buffer_size = 1;
      typedef boost::array<char, buffer_size> input_buffer;
      typedef misc::function_object<void, string> raw_input_handler;

    public:

      typedef this_type * pointer;
      typedef socket_wrapper::pointer socket_ptr;
      typedef raw_input_handler::pointer input_handler;

      void start_listen();
      void stop_listen();

      virtual ~socket_reader();

    protected:

      template<class Function_Type>
      socket_reader (const socket_ptr & socket, const Function_Type & handler);

    private:

      void listen ();

      void handle_input (const boost::system::error_code& ec, std::size_t bytes_transferred);
      void submit_input ();

      input_handler handler_;
      bool listening_;
      input_buffer input_buffer_;
      string input_;
  };
}

#include "inline/socket_reader.inl"

#endif
