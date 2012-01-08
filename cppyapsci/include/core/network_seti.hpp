
#ifndef NETWORK_SETI_HPP
#define NETWORK_SETI_HPP

#include <creatable.hpp>
#include <wrapper.hpp>
#include <socket_creator.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <map>
#include <tuple>

namespace yapsci {

  enum class protocol {
    IPV4 = 4,
    IPV6 = 6
  };

  class network_seti
    : virtual public socket_creator
    , virtual public misc::wrapper<boost::asio::io_service>
    , public misc::creatable<network_seti, boost::shared_ptr<network_seti> >
    , public boost::enable_shared_from_this<network_seti> {

    friend class misc::creatable<network_seti, boost::shared_ptr<network_seti> >;

    private:

      typedef misc::wrapper<boost::asio::io_service> io_service_wrapper;

    public:

      typedef io_service_wrapper::value_type io_service;
      typedef network_seti this_type;
      typedef boost::shared_ptr<this_type> pointer;
      typedef std::tuple<unsigned short, protocol> identifier;

      void start_listen (unsigned short port, protocol p);
      void start_listen (const identifier & id);
      void stop_listen (unsigned short port, protocol p);
      void stop_listen (const identifier & id);

      virtual ~network_seti();

    protected:

      template<class Function_Type>
      network_seti(io_service & service, const Function_Type & handler);

    private:

      void accept (const identifier & id);
      void handle_accept(const identifier & id,
                         socket_ptr socket,
                         const boost::system::error_code & ec);

      typedef boost::asio::ip::tcp::acceptor acceptor;
      typedef acceptor * acceptor_ptr;
      typedef std::map<identifier, acceptor_ptr> container;

      container acceptors_;

      static boost::asio::ip::tcp::endpoint::protocol_type
        map_protocol (protocol p);
  };
}

#include "inline/network_seti.inl"

#endif
