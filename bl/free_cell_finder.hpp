#ifndef FreeSellSpaceFinderINCLUDED
#define FreeSellSpaceFinderINCLUDED

#include "src/details/traits.hpp"
#include "src/bl/cell.hpp"

namespace bl {

  struct FreeCellSpaceFinder {
  private:   
    int display_width_; 
    int display_height_; 
    int cell_width_; 
    int cell_height_;
    
  public: 
    std::vector<traits::box_2i> possibilities_;
    
    void init(int display_width, int display_height, int bottom_extra_offset,
	      int cell_width, int cell_height) {
      possibilities_.clear();
      display_width_ = display_width; 
      display_height_ = display_height; 
      cell_width_ = cell_width; 
      cell_height_ = cell_height;

      int x = 0;
      int y = 0;
      for(int y = cell_height; y < display_height - cell_height*2;y +=cell_height - std::rand()%(cell_height/2)){
	for(int x = cell_width; x < display_width - cell_width*2;x +=cell_width - std::rand()%(cell_width/2)){
	    traits::point_2i min_p(x, y + bottom_extra_offset);
	    traits::point_2i max_p(x + cell_width,y + cell_height + bottom_extra_offset);  
	    possibilities_.push_back(traits::box_2i(min_p, max_p));
	    y += (cell_height/4) - std::rand()%(cell_height/2);
	    if(y < - cell_height/2 ) {
	      y  =  cell_height/2;
;	    }
	  } 
      } 
    }
    
    static bool intersects ( const traits::box_2i& r1, const traits::box_2i& r2) {
      float ulx = std::max ( r1.min_corner().x(), r2.min_corner().x() );
      float uly = std::max ( r1.min_corner().y(), r2.min_corner().y() );
      float lrx = std::min ( r1.max_corner().x(), r2.max_corner().x());
      float lry = std::min ( r1.max_corner().y(), r2.max_corner().y());

      return ulx <= lrx && uly <= lry;
    }
    
    void remove_if_overlabs(const traits::box_2i& s) {
      for( int i = 0; i < possibilities_.size(); ++i) {
          if(intersects(possibilities_[i], s)){
              possibilities_.erase(possibilities_.begin() + i);
              i--;
          }
        }
    }
    traits::box_2i reserve_place() {
      traits::box_2i result(traits::point_2i(cell_width_,cell_height_), 
			    traits::point_2i(cell_width_*2,cell_height_*2));
      int size = possibilities_.size();
      if(size > 0) {
	int current_possibilities = std::rand()% possibilities_.size();
	result = possibilities_[current_possibilities];
	possibilities_.erase(possibilities_.begin() + current_possibilities);
      } 
      return result;
    }
  };
}


#endif