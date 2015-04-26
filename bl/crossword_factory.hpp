#ifndef crosswordFactoryINCLUDED
#define crosswordFactoryINCLUDED

#include <vector>
#include "src/bl/crossword_factory _base.hpp"
#include "svg_viewer/cocos2dx_parse.h"
#include "svg_viewer/agg_svg_parser.h"
#include "svg_viewer/render_svg_file.hpp"
#include "src/details/RGBBitmap.hpp"

#include "src/bl/crossword_factory _base.hpp"
#include "src/bl/xml_serialization/CategoryList.hpp"
#include "src/bl/xml_serialization/Dict.hpp"

#include "src/details/utils.h"
#include "src/details/SVGGraphicContext.hpp"
#include "src/bl/xml_serialization/crossword.hpp"
#include "src/bl/xml_serialization/file_names.hpp"

namespace bl {
  
  struct CrosswordFactoryCategories : public CrosswordFactoryBase {
    
    CrosswordFactoryCategories(const bl::dict::Word& w){
      {
	word_index_ = 0;
	category_index_ = 17;
	
	dict_.words_.push_back(w) ;
      }
    }
    
    virtual void current(Crossword& cw) {
      cw = crossword_from_text_and_pictt(dict_.words_[word_index_].name_, 
							dict_.words_[word_index_].png_);
    }

  private:

    bl::Crossword crossword_from_text_and_pictt(std::string text, std::string pict_file_name) {

	std::transform(text.begin(), text.end(), text.begin(), ::toupper);
	bl::Word w;
	w.text_ = text;
	bl::Crossword crossword;
	bl::Picture p;
	p.size_ = bl::Size(3,3);
	p.position_ = bl::Cell(-1,-3);
	p.id_ = pict_file_name;
	SVGGraphicContext::shared_instans().
	  load_texture( p.id_ , p.id_, 3, 3);
	w.picture_ = p;
	crossword.words_.push_back(w);
	return crossword;
      }
      int category_index_;
      int word_index_;
      std::vector< bl::Category> c_list_;
      bl::dict::Dict dict_;

  };

  struct CrosswordFactoryPuzzle : public CrosswordFactoryBase {
    
      CrosswordFactoryPuzzle(const std::string& filename) : filename_(filename) { }
    virtual void current(Crossword& cw){
      ptree pt;
      std::stringstream ss2;
      Cocos2dSvgParserAdapter::read_file_content_into_stream(ss2,filename_);
      read_xml(ss2, pt);
      cw = bl::ser::Crossword::deserialize(pt.get_child("crossword"));
      
    }
    
  private:
     std::string filename_;
  };
}


#endif