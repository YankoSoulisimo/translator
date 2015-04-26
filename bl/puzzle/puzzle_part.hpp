#ifndef partINCLUDED
#define partINCLUDED


#include "src/bl/puzzle/box.hpp"

namespace bl {
  namespace puzzle {
    
  struct Part : public BecomePartOfThePuzzle, public Box {

       
 public:   
  
  Part() {
  }
  
  int z_index_;
  
  bool include(int x, int y) {
    bl::traits::point_2d p(x ,y );
    return boost::geometry::within(p, bounding_rect()) ;
  }

};

}
}

#endif
