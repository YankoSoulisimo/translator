#ifndef GridINCLUDED
#define GridINCLUDED

#include "src/bl/crossword.hpp"
#include <boost/concept_check.hpp>
#define  GRID_CELL_BG "grid_cell_bg"
#define  GRID_PICTURE_CELL_BG "grid_picture_cell_bg"
#define  GRID_LETTER_BG "grid_letter_bg" 
#define  GRID_FILLED_CELL_BG "grid_filled_cell_bg"

namespace bl {

  struct Grid {
    
    Grid() { }
    void set(const Crossword& c) {
      
    }

    static int max_row_index(const Word& w) { 
      if(w.is_horizontal_) {
	return w.picture_.exist()? 
	    std::max( w.picture_.position_.row_ + w.picture_.size_.rows_ -1 , w.position_.row_) : w.position_.row_;
      } else {
	return w.position_.row_ + w.text_.size() - 1;
      }
    }
 
    static int max_col_index(const Word& w) { 
      if(w.is_horizontal_) {
	return w.position_.col_ + w.text_.size() - 1;
      } else {
	return  w.picture_.exist()? 
	    std::max( w.picture_.position_.col_ + w.picture_.size_.cols_ -1 , w.position_.col_) : w.position_.col_;
      }
    }
    
    static int min_row_index(const Word& w) { 
      if(w.picture_.exist()) {
	return std::min( w.picture_.position_.row_ , w.position_.row_);
      } else {
	return w.position_.row_;
      }

    }
    static int min_col_index(const Word& w) { 
      if(w.picture_.exist()) {
	return std::min( w.picture_.position_.col_, w.position_.col_);
      } else {
	return w.position_.col_;
      }
    }
    
    

    static int max_row_index(const std::vector<Word>& con) {
      int result_max = -100000;
     
      for(std::size_t i = 0; i < con.size();++i ) {
	result_max = std::max(result_max, max_row_index(con[i]));
      }
      return result_max;
    }

    static int min_row_index(const std::vector<Word>& con) {
      int result_min = 100000;
     
      for(std::size_t i = 0; i < con.size();++i ) {
	result_min = std::min(result_min, min_row_index(con[i]));
      }
      return result_min;
    }

    static int max_col_index(const std::vector<Word>& con) {
      int result_max = -100000;
     
      for(std::size_t i = 0; i < con.size();++i ) {
	result_max = std::max(result_max, max_col_index(con[i]));
      }
      return result_max ;
    }

    static int min_col_index(const std::vector<Word>& con) {
      int result_min = 100000;
     
      for(std::size_t i = 0; i < con.size();++i ) {
	result_min = std::min(result_min, min_col_index(con[i]));
      }
      return result_min;
    }
    
  };
  
}


#endif