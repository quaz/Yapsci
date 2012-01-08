
#include<iostream>

namespace yapsci {
  namespace misc {

    inline logger & logger::get_instance() {
      if (!instance_) instance_ = new logger();
      return *instance_;
    }

    inline logger & logger::get_instance (level_type level) {
      return get_instance() (level);
    }

    inline logger & logger::operator() (int level) {
      current_level_ = level;
      return *this;
    }

    inline logger & logger::operator++ () {
      ++active_level_;
      return *this;
    }

    inline logger & logger::operator++ (int) {
      return ++ (*this);
    }

    inline logger & logger::operator-- () {
      --active_level_;
      return *this;
    }

    inline logger & logger::operator-- (int) {
      return -- (*this);
    }

    inline logger & logger::fix_level() {
      active_level_ = current_level_;
      return *this;
    }

    inline logger & log (int level) {
      return logger::get_instance(level);
    }

    template<class T>
    logger & logger::operator<< (const T & t) {
      if (current_level_ <= active_level_) {
        if (current_level_ <= error_levels_)
          std::cerr << t;
        else
          std::cout << t;
      }
      return *this;
    }
  }
}
