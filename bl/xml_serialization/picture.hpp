#ifndef PictureSerINCLUDED
#define PictureSerINCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "src/bl/picture.hpp"

#include "src/bl/xml_serialization/cell.hpp"
#include "src/bl/xml_serialization/size.hpp"
using boost::property_tree::ptree;

namespace bl {
namespace ser {
  struct Picture {
    static bl::Picture deserialize(const ptree &pt) {
     
      bl::Picture result;
      const ptree &pt_x =pt.get_child("<xmlattr>");
      if(pt_x.count("id"))
      {
	  result.id_ = pt.get<std::string>("<xmlattr>.id");
      }
      result.position_ = ser::Cell::deserialize(pt.get_child("position"));
      result.size_ = ser::Size::deserialize(pt.get_child("size"));
      return result;
    }
  };  
}
}


#endif