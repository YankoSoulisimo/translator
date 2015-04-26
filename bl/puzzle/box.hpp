#ifndef boxINCLUDED
#define boxINCLUDED

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/multi/multi.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>

#include "src/details/traits.hpp"
#include "src/bl/puzzle/become_part_of_the_puzzle.hpp"

namespace bl {
  namespace puzzle {
  
  
struct Box {
  
 protected:
  std::string id_;
  bl::traits::point_2i min_corner_;
  int width_;
  int height_;
    double angle_;
    
 public:   
  Box() : id_("") { }
  Box(const Box& b) {
      this->operator=(b);
  }
  ~Box() {  }
  
  const Box& operator=(const Box& e){
        id_ = e.id_;
        
        min_corner_ = e.min_corner_;
        width_  = e.width_;
        height_ = e.height_;
        return *this;
  }
  
  bool operator==(const Box& e) const{
      return 
	id_ == e.id_ &&
        min_corner_.x() == e.min_corner_.x() &&
        min_corner_.y() == e.min_corner_.y() &&
        width_  == e.width_&&
        height_ == e.height_;
  }
  
  void set_id(std::string ID) { id_ = ID;}  
  std::string id() const { return id_;}

     
  const traits::point_2i& min_corner() const{
    return min_corner_;
  }

  
  void set_min_corner(const traits::point_2i& p) {
    min_corner_ = p;
  }
  
  void set_min_corner(int x, int y ){
        min_corner_ = bl::traits::point_2i(x, y);
  }
  
  void set_center(int x, int y ){
        min_corner_ = bl::traits::point_2i(x - width_/2, y - height_/2);
  }

  void set_angle(double a){
        angle_ = a;
  }
  void set_bounding_rect(const traits::box_2i& r) {
    min_corner_ = r.min_corner();
    width_ = r.max_corner().x() - r.min_corner().x();
    height_ = r.max_corner().y() - r.min_corner().y();
  }
  
  virtual traits::box_2i bounding_rect() const {
    traits::point_2i max_corner(min_corner_.x() + width_,
			  min_corner_.y() + height_ );
    return traits::box_2i(min_corner_, max_corner);
  }

  traits::point_2i center() const {
        traits::point_2i center(min_corner_.x() + width_/2,
                                    min_corner_.y() + height_/2 );
        return center;
  }
    double angle() const{
        return angle_;
    }
  int width()const {
      return width_;
  }

  int height()const {
      return height_;
  }
  void set_width(int w){
      width_ = w;
  }

  void set_height(int h) {
      height_ = h;
  }
};

struct Place : public BecomePartOfThePuzzle, public Box {};
    
}
}

#endif
