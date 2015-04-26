#ifndef PictureINCLUDED
#define PictureINCLUDED

#include <string>

#include "src/bl/cell.hpp"
#include "src/bl/size.hpp"

namespace bl {

  
  struct Picture {
    
    Picture() { }
    
    Cell position_;
    Size size_;
    std::string id_;
    bool exist() const {
      return ! id_.empty();
    }
  };
 
}


#endif