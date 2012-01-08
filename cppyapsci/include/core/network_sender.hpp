
#ifndef NETWORK_SENDER_HPP
#define NETWORK_SENDER_HPP

#include <boost/asio.hpp>
#include <string>
#include <wrapper.hpp>
#include <function_object.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <creatable.hpp>
#include <socket_creator.hpp>

namespace yapsci {

  class network_sender
    : virtual public socket_creator
    , virtual public misc::wrapper<boost::asio::io_service>
    , public misc::creatable<network_sender, boost::shared_ptr<network_sender> >
    , public boost::enable_shared_from_this<network_sender> {

    friend class misc::creatable<network_sender, boost::shared_ptr<network_sender> >;

    private:

      typedef misc::wrapper<boost::asio::io_service> io_service_wrapper;

    public:

      typedef io_service_wrapper::value_type io_service;
      typedef std::string string;
      typedef network_sender this_type;
      typedef boost::shared_ptr<this_type> pointer;

      virtual ~network_sender();

      void connect_to(const string & host, const string & service);

    protected:

      template<class Function_Type>
      network_sender(io_service & service, const Function_Type & handler);

    private:

      void handle_resolve(const string & target,
                          const boost::system::error_code & ec,
                          boost::asio::ip::tcp::resolver::iterator it);

      boost::asio::ip::tcp::resolver resolver_;
  };
}

#include "inline/network_sender.inl"

#endif
