#ifndef SizeSerINCLUDED
#define SizeSerINCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "src/bl/size.hpp"

using boost::property_tree::ptree;

namespace bl {
namespace ser {
  struct Size {
    static bl::Size deserialize(const ptree &pt) {
     
      bl::Size result;
      const ptree &pt_x =pt.get_child("<xmlattr>");
      if(pt_x.count("rows"))
      {
	  result.rows_ = pt.get<double>("<xmlattr>.rows");
      }
      if(pt_x.count("cols"))
      {
	  result.cols_ = pt.get<double>("<xmlattr>.cols");
      }
      return result;
    }
  };  
}
}


#endif