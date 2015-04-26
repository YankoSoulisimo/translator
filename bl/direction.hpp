#ifndef DirectionINCLUDED
#define DirectionINCLUDED

#include "src/bl/cell.hpp"

namespace bl {

  struct Direction {
    Cell begin_;
    Cell end_;
  };
}


#endif