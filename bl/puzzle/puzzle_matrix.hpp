#ifndef PuzzleMatrixINCLUDED
#define PuzzleMatrixINCLUDED

#include <vector>
#include "src/bl/puzzle/puzzle_part.hpp"

namespace bl {
namespace puzzle {
    
  struct PuzzleMatrix {
  private:
    int draging_element_index_;

  public:
    std::list< Part > elements_;
    std::vector< Place > destinations_;
    std::vector< Box > pictures_;
    PuzzleMatrix() : draging_element_index_(-1) {}
    
    
    bool on_mouse_button_down(int x, int y) {
      draging_element_index_ = -1;

      for(std::list<Part>::iterator it = elements_.begin(); it != elements_.end();++it) {
          if (!	it->become_part_of_the_puzzle() &&
              it->include(x,y)) {
              elements_.push_front(*it);
              elements_.erase(it);
              //elements_.front().set_drag_offset(x,y);
              draging_element_index_ = 0;
              break;
          }
      }
      return draging_element_index_ >=0;
    }
    bool on_mouse_move(int x, int y) {
      bool result = false;
      if(draging_element_index_ >=0 ) {
          Part& current = elements_.front();
          current.set_min_corner(x,y);
          result = true;
      } 
      return result;
    }
    
    bool on_mouse_button_up(int x, int y) {
      bool flag = false;
      if( draging_element_index_>=0 ) {

          bool overlaps = false;
	
          for(int i = 0 ;i < destinations_.size();i++ ) {
              Place& current = destinations_[i];
              if(current.become_part_of_the_puzzle()) {
                  continue;
              }
	  
              if(are_they_close_enough(elements_.front(), current) ) {
                  elements_.front().set_become_part_of_the_puzzle() ;
                  current.set_become_part_of_the_puzzle() ;
                  move(elements_.front(), current);
		  flag = true;
                  break;
              }
              overlaps |= intersects( elements_.front().bounding_rect(),
						  current.bounding_rect());
          }

          draging_element_index_ =-1;
        }
      return flag;
    }

      bool on_mouse_button_up(Part& part) {
          bool flag = false;
              for(int i = 0 ;i < destinations_.size();i++ ) {
                  Place& current = destinations_[i];
                  if(current.become_part_of_the_puzzle()) {
                      continue;
                  }
                  
                  if(are_they_close_enough(part, current) ) {
                      part.set_become_part_of_the_puzzle() ;
                      current.set_become_part_of_the_puzzle() ;
                      move(part, current);
                      flag = true;
                      break;
                  }
              }
              
          draging_element_index_ =-1;
          return flag;
      }
      Part* move_to_front(Part* part, int x, int y) {
          draging_element_index_ = -1;
          
          for(std::list<Part>::iterator it = elements_.begin(); it != elements_.end();++it) {
              if (	&(*it) == part) {
                  elements_.push_front(*it);
                  elements_.erase(it);
                  //elements_.front().set_drag_offset(x,y);
		  draging_element_index_ = 0;
                  return &(elements_.front());
              }
          }
          return NULL;
      }
      
      
    static bool intersects ( const traits::box_2i& r1, const traits::box_2i& r2) {
          float ulx = std::max ( r1.min_corner().x(), r2.min_corner().x() );
          float uly = std::max ( r1.min_corner().y(), r2.min_corner().y() );
          float lrx = std::min ( r1.max_corner().x(), r2.max_corner().x());
          float lry = std::min ( r1.max_corner().y(), r2.max_corner().y());
          
          return ulx <= lrx && uly <= lry;
    }
    
    bool are_they_close_enough(const Part& e1, const Box& e2) const {
	     
        if(e1.id() != e2.id()) return false;
        int deviation  = e1.width()/3;
	
        int current_cordinat_dx =
            e1.min_corner().x() - e2.min_corner().x();
        int current_cordinat_dy =
        e1.min_corner().y() - e2.min_corner().y();

        if(( std::abs(current_cordinat_dx) < deviation) &&
           (std::abs(current_cordinat_dy) < deviation) ) {
	  
            //	std::cout << std::abs((int)current_cordinat_dx - dx) << std::endl;
            //	std::cout << std::abs((int)current_cordinat_dy - dy) << std::endl << std::endl;
	  
            return true;
        }
        return false;
    }
    void move(Part& e2, const Box& source ) const {
      e2.set_min_corner(source.min_corner());
    }
    
    void add_part( std::string id,
		   const bl::traits::box_2i& destination_rect ) {
      
        bl::puzzle::Part p;
        bl::puzzle::Place b;
        p.set_id(id);
        b.set_id(id);
	
        bl::traits::box_2i r = destination_rect;
        p.set_min_corner(r.min_corner());
        p.set_width(r.max_corner().x() - r.min_corner().x());
        p.set_height(r.max_corner().y() - r.min_corner().y());
	
        b.set_min_corner(destination_rect.min_corner());
        b.set_width(destination_rect.max_corner().x() - destination_rect.min_corner().x());
        b.set_height(destination_rect.max_corner().y() - destination_rect.min_corner().y());
	
        /*
        for(std::size_t i = 0; i < destinations_.size();++i) {
            if(destinations_[i] == b) {
                return false;
            }
        }
         */
	
        elements_.push_back(p);
        destinations_.push_back(b);
	
    }
    
    void add_picture( std::string id, 
		    const bl::traits::box_2i& destination_rect ) {
      
        bl::puzzle::Place b;
        b.set_id(id);

        b.set_min_corner(destination_rect.min_corner());
        b.set_width(destination_rect.max_corner().x() - destination_rect.min_corner().x());
        b.set_height(destination_rect.max_corner().y() - destination_rect.min_corner().y());
        b.set_become_part_of_the_puzzle();
        pictures_.push_back(b);
	
    }
    
    bool is_done() const {
	
        for(std::size_t i = 0; i < destinations_.size();++i) {
            if(destinations_[i].become_part_of_the_puzzle() == false ) {
                return false;
            }
        }
        return true;
    }
   
    void reset(){
        elements_.clear();
        destinations_.clear();
        pictures_.clear();
        draging_element_index_ = -1;
    }
  };
}

}

#endif
