
#include <logger.hpp>

namespace yapsci {
  namespace misc {

    logger * logger::instance_ = nullptr;

    logger::logger ()
     : current_level_ (1) {
    }
  }
}
