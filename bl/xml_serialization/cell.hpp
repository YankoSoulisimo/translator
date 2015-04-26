#ifndef CellSerINCLUDED
#define CellSerINCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "src/bl/cell.hpp"

using boost::property_tree::ptree;

namespace bl {
namespace ser {
  struct Cell {
    static bl::Cell deserialize(const ptree &pt) {
     
      bl::Cell result;
      const ptree &pt_x =pt.get_child("<xmlattr>");
      if(pt_x.count("row"))
      {
	  result.row_ = pt.get<double>("<xmlattr>.row");
      }
      if(pt_x.count("col"))
      {
	  result.col_ = pt.get<double>("<xmlattr>.col");
      }
      return result;
    }
  };  
}
}


#endif