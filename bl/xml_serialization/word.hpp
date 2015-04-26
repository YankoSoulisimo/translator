#ifndef WordSerINCLUDED
#define WordSerINCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "src/bl/word.hpp"

#include "src/bl/xml_serialization/picture.hpp"
using boost::property_tree::ptree;

namespace bl {
namespace ser {
  struct Word {
    static bl::Word deserialize(const ptree &pt) {
     
      bl::Word result;
      if(pt.count("<xmlattr>")) {
	  result.is_horizontal_ = pt.get<int>("<xmlattr>.is_horizontal") == 1;
      }
      
      if(pt.count("text")) {
	result.text_ = pt.get_child("text").get_value<std::string>();
      }

      if(pt.count("hint")) {
	result.hint_ = pt.get_child("hint").get_value<std::string>();
      }
      if(pt.count("position")) {
	result.position_ = ser::Cell::deserialize(pt.get_child("position"));
      }
      if(pt.count("picture")) {
	result.picture_ = ser::Picture::deserialize(pt.get_child("picture"));
      }
      return result;
    }
  };  
}
}


#endif