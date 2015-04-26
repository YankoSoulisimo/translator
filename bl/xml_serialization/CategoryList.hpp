//
//  Created by Владимир Рангелов on 1/16/13.
//

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "src/bl/CategoryList.hpp"

namespace bl {
  namespace ser {
    using boost::property_tree::ptree;
    
      struct Category {
	
	static  void load(const ptree &pt, bl::Category& c) {
	      const ptree &pt_x =pt.get_child("<xmlattr>");
	      if(pt_x.count("locked"))
	      {
		  c.locked_ = pt.get<std::string>("<xmlattr>.locked");
	      }
	    
	    if(pt_x.count("title"))
	      {
		  c.title_ = pt.get<std::string>("<xmlattr>.title");
	      }

	      if(pt_x.count("name"))
	      {
		  c.name_ = pt.get<std::string>("<xmlattr>.name");
	      }

	      if(pt_x.count("png"))
	      {
		  c.png_ = pt.get<std::string>("<xmlattr>.png");
	      }
	      if(pt_x.count("zipFile"))
	      {
		  c.filename_ = pt.get<std::string>("<xmlattr>.zipFile");
	      }
	  }
	static void save(ptree &pt, const bl::Category& c) {
	      pt.add("<xmlattr>.locked", c.locked_);
	      pt.add("<xmlattr>.title", c.title_);
	      pt.add("<xmlattr>.name", c.name_);
	      pt.add("<xmlattr>.png", c.png_);
	      pt.add("<xmlattr>.zipFile", c.filename_);
	  }
      };

	  
      struct CategoryList {

	static void load(const ptree &pt, std::vector<bl::Category>& icons_) {
	    using boost::property_tree::ptree;
	    
	    BOOST_FOREACH(const ptree::value_type &v,
			    pt.get_child("dicts")){
		  bl::Category c;
		  ser::Category::load(v.second, c);
		  icons_.push_back(c);
	      }
	    
	}
	
	static void load(const std::string &filename, std::vector<bl::Category>& icons_) {
	      using boost::property_tree::ptree;
	      ptree pt;
	      read_xml(filename, pt);
      //	const ptree &pt_x =pt.get_child("dicts");
	      load(pt, icons_);
	}
	
	static void save(ptree &pt, const std::vector<bl::Category> icons_) {
	    using boost::property_tree::ptree;

	    for(std::vector<bl::Category>::const_iterator it = 
		icons_.begin(); it != icons_.end();++it ){
		  ptree icon;
		  ser::Category::save(icon, *it);
		  pt.add_child("dict", icon);
	      }
	    
	}
	static void save(const std::string &filename, const std::vector<bl::Category> icons_){
	    ptree pt;
	    ptree dicts;
	    ser::CategoryList::save(pt, icons_);
	    dicts.add_child("dicts", pt);
	    write_xml(filename, dicts);
	  }
      };
  } 
}