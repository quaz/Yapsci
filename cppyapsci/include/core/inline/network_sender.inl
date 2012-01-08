
namespace yapsci {

  inline network_sender::~network_sender(){
  }

  template<class Function_Type>
  inline network_sender::network_sender(io_service & service, const Function_Type & handler)
    : socket_creator(handler) , io_service_wrapper(&service) , resolver_(service){
  }
}
