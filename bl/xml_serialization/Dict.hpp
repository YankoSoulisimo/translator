//
//  Created by Владимир Рангелов on 1/16/13.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "src/bl/Dict.hpp"

namespace bl {
  namespace dict { 
    namespace ser {
 
using boost::property_tree::ptree;
  
      struct Word {
	
	static void load(const ptree &pt, dict::Word& w) {
	      const ptree &pt_x =pt.get_child("<xmlattr>");
	      if(pt_x.count("name")) {
              w.name_ = pt.get<std::string>("<xmlattr>.name");
	      }
        
	      if(pt_x.count("translation")) {
              w.translation_ = pt.get<std::string>("<xmlattr>.translation");
	      }
        
	      if(pt_x.count("png")) {
              w.png_ = pt.get<std::string>("<xmlattr>.png");
	      }
        
	      if(pt_x.count("sound")) {
              w.sound_ = pt.get<std::string>("<xmlattr>.sound");
	      }
        
          if(pt_x.count("sentence_file_name")) {
              w.sentence_file_name_ = pt.get<std::string>("<xmlattr>.sentence_file_name");
          }

          if(pt_x.count("crossword_file_name")) {
              w.crossword_file_name_ = pt.get<std::string>("<xmlattr>.crossword_file_name");
          }
        
        
	  }
	static void save(ptree &pt,const dict::Word& w) {
	      pt.add("<xmlattr>.name", w.name_);
	      pt.add("<xmlattr>.translation", w.translation_);
	      pt.add("<xmlattr>.png", w.png_);
	      
          if(! w.sound_.empty()) pt.add("<xmlattr>.sound",
                                        w.sound_);
          if(! w.crossword_file_name_.empty())pt.add("<xmlattr>.crossword_file_name", w.crossword_file_name_);
          if(! w.sentence_file_name_.empty())pt.add("<xmlattr>.sentence_file_name", w.sentence_file_name_);
	  }
      };

	  
      struct Words {

	static void load(const ptree &pt, std::vector<dict::Word>& words_) {
	    using boost::property_tree::ptree;

	    BOOST_FOREACH(const ptree::value_type &v,
			    pt.get_child("words")){
		  dict::Word w;
		  ser::Word::load(v.second,w);
		  words_.push_back(w);
	      }
	    
	}
	static  void save(ptree &pt,const std::vector<dict::Word>& words_) {
	    using boost::property_tree::ptree;

	    for(std::vector<dict::Word>::const_iterator it = 
		words_.begin(); it != words_.end();++it ){
		  ptree word;
		  ser::Word::save(word, *it);
		  pt.add_child("word", word);
	      }
	    
	}
      
      };
	  
      struct Dict {
	static void load(const ptree &pt1, dict::Dict& d){
	      const ptree &pt_x =pt1.get_child("dict");
	      d.name_ = pt_x.get<std::string>("<xmlattr>.name");
	      ser::Words::load(pt_x, d.words_);
	  }

	static  void load(const std::string &filename, dict::Dict& d) {
	      using boost::property_tree::ptree;
	      ptree pt;
	      read_xml(filename, pt);
	      load(pt, d);
	  }
	  static void save(const std::string &filename, dict::Dict& d){
	    ptree pt;
	    ptree dict;
	    dict.add("<xmlattr>.name", d.name_);
	    ptree words;
	    ser::Words::save(words, d.words_);
	    dict.add_child("words", words);
	    pt.add_child("dict", dict);
	    write_xml(filename, pt);
	  }
      };
    }
  }
}