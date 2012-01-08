
#ifndef LOGGER_HPP
#define LOGGER_HPP

namespace yapsci {
  namespace misc {

    class logger {

     public:

      typedef unsigned char level_type;

     private:

      logger ();

      logger (const logger &) = delete;
      logger & operator= (const logger &) = delete;

      static logger * instance_;
      static constexpr level_type error_levels_ = 2;

      level_type active_level_;  // all levels above are passive
      level_type current_level_; // level at which stuff is being logged atm

     public:

      static logger & get_instance();
      static logger & get_instance(level_type level);

      logger & operator++ ();
      logger & operator++ (int);
      logger & operator-- ();
      logger & operator-- (int);

      logger & operator() (int);

      logger & fix_level();

      template<class T>
      logger & operator<< (const T & t);
    };

    logger & log(int level);
  }
}

#include "inline/logger.inl"

#endif
