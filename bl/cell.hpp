#ifndef CellINCLUDED
#define CellINCLUDED


namespace bl {

  struct Cell {
    int row_;
    int col_;
    
    Cell(): row_(0), col_(0) { }
    Cell(int r, int c): row_(r), col_(c) { }
  };  
  
}


#endif