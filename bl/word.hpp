#ifndef WordINCLUDED
#define WordINCLUDED

#include "src/bl/picture.hpp"
#include "src/bl/direction.hpp"

namespace bl {

  struct Word {
    
    Word(): is_horizontal_(true) { }
      
    std::string text_;
    std::string hint_;
    bool is_horizontal_;
    Cell position_;
    Picture picture_;
  };
  
}


#endif