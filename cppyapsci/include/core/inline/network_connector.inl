
namespace yapsci {

  template<class ... Args>
  inline network_connector::pointer network_connector::create (Args ... args) {
    return misc::creatable<this_type, pointer>::create (args ...);
  }

  inline network_connector::~network_connector() {
  }

  template<class Function_Type>
  inline network_connector::network_connector (io_service & service, Function_Type handler)
    : socket_creator (handler)
    , wrapper<io_service> (&service)
    , network_sender (service, handler)
    , network_seti (service, handler) {
  }
}
