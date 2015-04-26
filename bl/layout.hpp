#ifndef crossword_layoutINCLUDED
#define crossword_layoutINCLUDED

#include "src/bl/crossword.hpp"
#include "src/details/traits.hpp"
#include "src/bl/grid.hpp"


namespace bl {
  
  struct Layout {
    
    double cell_width_; 
    double cell_height_;
    int draw_offset_x_;
    int draw_offset_y_;
    int total_rows_;
    int total_cols_;
    
    int min_rows_index_;
    int min_cols_index_;
    
    
      Layout() : cell_width_(0), 
		 cell_height_(0),
		 draw_offset_x_(1),
		 draw_offset_y_(1){ }
		 
      void recalculate(int display_width, 
		       int display_height, 
		       int bottom_extra_offset,
		       const bl::Crossword& crossword ) {
	min_rows_index_ = Grid::min_row_index(crossword.words_);
	min_cols_index_ = Grid::min_col_index(crossword.words_);
	
	total_rows_ =  Grid::max_row_index(crossword.words_) - min_rows_index_ + 1;
	total_cols_ =  Grid::max_col_index(crossword.words_) - min_cols_index_ + 1;
	//patch for sentences
	total_cols_ = std::max(total_cols_, max_column(crossword));
	
	calculate_cell_size(display_width, display_height);
	calculate_offsets(display_width, display_height);
	draw_offset_y_ += bottom_extra_offset;
      };
      
      int max_column(const bl::Crossword& crossword) {
	int result = 0;
	int current_col = 0;
	int current_row = 0;
	for(std::size_t i = 0; i < crossword.words_.size(); ++i){
	      
	      bl::Word w = crossword.words_[i]; 
	      if(current_row != w.position_.row_){
		current_col = 0;
	      }
	      current_row = w.position_.row_;
	      current_col += w.text_.size() + 1;
	      result = std::max(result, current_col);
	}
	
	return result -1;
      }

      
      int calculate_cell_size(int display_width, 
			      int display_height) {
	
	  double cell_size_rows = display_height/(total_rows_ + 2);
	  double cell_size_cosl = (display_width )/(total_cols_ + 2);
	  cell_height_ = cell_width_ = (cell_size_rows < cell_size_cosl)? cell_size_rows : cell_size_cosl;
	  double min_width = (display_height > display_width?display_width:display_height)/8;
	  if(cell_height_ > min_width) {
	      cell_height_ = cell_width_ = min_width;
	  } 
	  return cell_height_;
      }
      
      void calculate_offsets(int display_width,  int display_height) {
		draw_offset_x_ = (display_width - total_cols_*cell_width_)/2;
        draw_offset_y_ = (display_height - total_rows_*cell_height_)/2;
      }
      int cell_width() const {
	return cell_width_;
      }
      
      int cell_height() const {
	return cell_height_;
      }
      
      traits::box_2i get_cell_frame(int row_pos, int col_pos, 
				    int rows = 1, int cols = 1) {
	col_pos -= min_cols_index_;
	row_pos -= min_rows_index_;
	
	row_pos = total_rows_ - row_pos - rows;
	traits::point_2i min_corner(draw_offset_x_ + col_pos*cell_width_, 
				  draw_offset_y_ + row_pos*cell_height_); 
	traits::point_2i max_corner(min_corner.x() + cell_width_*cols,
				  min_corner.y() + cell_height_*rows); 

	return traits::box_2i(min_corner, max_corner);
      } 
      
  };
}


#endif