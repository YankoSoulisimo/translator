#ifndef SizeINCLUDED
#define SizeINCLUDED

namespace bl {

  struct Size {
    int rows_;
    int cols_;
    Size(): rows_(0), cols_(0) { }
    Size(int r, int c): rows_(r), cols_(c) { }
  };  
 
}


#endif