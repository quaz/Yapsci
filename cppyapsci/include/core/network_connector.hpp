
#ifndef NETWORK_CONNECTOR_HPP
#define NETWORK_CONNECTOR_HPP

#include <network_sender.hpp>
#include <network_seti.hpp>
#include <boost/smart_ptr.hpp>
#include <socket_creator.hpp>
#include <creatable.hpp>

namespace yapsci {
  class network_connector
    : public network_sender
    , public network_seti
    , public misc::creatable<network_connector, boost::shared_ptr<network_connector> > {

    friend class misc::creatable<network_connector, boost::shared_ptr<network_connector> >;

    private:

      typedef network_connector this_type;

    public:

      typedef boost::shared_ptr<this_type> pointer;
      typedef boost::asio::io_service io_service;

      //TODO: find some neat solution for this... see also socket_read_writer::create
      template<class ... Args>
      static pointer create(Args ... args);

      virtual ~network_connector();

    protected:

      template<class Function_Type>
      network_connector (io_service & service, Function_Type handler);
  };
}

#include "inline/network_connector.inl"

#endif
