#ifndef CrosswordSerINCLUDED
#define CrosswordSerINCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include "src/bl/crossword.hpp"

#include "src/bl/xml_serialization/word.hpp"


using boost::property_tree::ptree;

namespace bl {
namespace ser {
  struct Crossword {
    static bl::Crossword deserialize(const ptree &pt) {
     
      bl::Crossword result;

        BOOST_FOREACH(const ptree::value_type &v,
                      pt.get_child("words")){
            bl::Word word = ser::Word::deserialize(v.second);
            result.words_.push_back(word);
        }
      return result;
    }
  };  
}
}


#endif