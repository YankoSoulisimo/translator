#ifndef crosswordFactoryBaseINCLUDED
#define crosswordFactoryBaseINCLUDED

#include "src/bl/crossword.hpp"

namespace bl {

  struct CrosswordFactoryBase {
    virtual void current(Crossword& cw) = 0;
  };
}


#endif