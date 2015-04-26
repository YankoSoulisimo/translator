#ifndef bldictDictINCLUDED
#define bldictDictINCLUDED

#include <string>
#include <vector>

namespace bl {
namespace dict {  

struct Word {
    std::string name_;  
    std::string translation_;  
    std::string png_;  
    std::string sound_;
    std::string sentence_file_name_;
    std::string crossword_file_name_;
  
};
    
struct Dict {
    std::string name_;
    std::vector<Word> words_;
};

}
}

#endif