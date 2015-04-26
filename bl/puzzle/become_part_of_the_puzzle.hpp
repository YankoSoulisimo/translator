#ifndef become_part_of_the_puzzleINCLUDED
#define partINCLUDED


#include "src/bl/puzzle/box.hpp"

namespace bl {
  namespace puzzle {
    
  struct BecomePartOfThePuzzle {
  
 private:
    bool flag_;

 public:   
  
  BecomePartOfThePuzzle() : flag_(false) {
    
  }
  
  void set_become_part_of_the_puzzle(){
     flag_ = true;
  }
  
  bool become_part_of_the_puzzle()const {
     return flag_;
  }
};

}
}

#endif
