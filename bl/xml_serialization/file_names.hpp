#ifndef __File_H__
#define __File_H__

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

namespace bl {
    namespace ser {
 
using boost::property_tree::ptree;
  
      struct File {
	
	static void load(const ptree &pt, std::string& file_name) {
	      const ptree &pt_x =pt.get_child("<xmlattr>");
	      if(pt_x.count("name"))
	      {
		  file_name = pt.get<std::string>("<xmlattr>.name");
	      }
	  }
	static void save(ptree &pt,const std::string& file_name) {
	      pt.add("<xmlattr>.name", file_name);
	  }
      };

	  
      struct Folder {

	static void load(const ptree &pt, std::vector<std::string>& files_) {
	    using boost::property_tree::ptree;

	    BOOST_FOREACH(const ptree::value_type &v,
			    pt.get_child("folder")){
		  std::string file_name;
		  ser::File::load(v.second,file_name);
		  files_.push_back(file_name);
	      }
	    
	}
	static  void save(ptree &pt,const std::vector<std::string>& files_) {
	    using boost::property_tree::ptree;

	    for(std::vector<std::string>::const_iterator it = 
		files_.begin(); it != files_.end();++it ){
		  ptree file;
		  ser::File::save(file, *it);
		  pt.add_child("file", file);
	      }
	    
	}
      
      };
  }
}

#endif