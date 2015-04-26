#ifndef crosswordINCLUDED
#define crosswordINCLUDED

#include <vector>
#include "src/bl/word.hpp"

namespace bl {

  struct Crossword {
    std::vector<Word> words_;	  
  };
  
}


#endif