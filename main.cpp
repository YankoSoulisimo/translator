/* Developed by Yanko Bachvarov */
//2015//
//main.cpp file of translator project//
//Translator project goal:
//To read words from XML and send a request to 
//Google translate for translation. Words are split
//in 10 cateogries. The returned
//translation of the word to be recorded in XML, so that
//it can be used by another application.

#include <stdio.h>
#include <string>
#include <iostream>

#include <curl/curl.h>

using boost::property_tree::ptree;

static std::string readBuffer;
static std::string g_language;
static std::string g_translate_filename;
static std::string g_source_language = "en";

//helper function for proper callback
static size_t WriteCallback(void *contents, size_t size, size_t nmemb)
{ 
    size_t realsize = size * nmemb;
    readBuffer.append(contents, realsize);
    return realsize;
}

//parse result from google
std::string parce_google_result(std::string web_responce) {
  std::size_t begin = web_responce.find ("\"");
  std::size_t end = web_responce.find ("\"", begin + 1);
  std::string result;
  result.append(web_responce, begin + 1, end - begin - 1);  
  return  result;
}

//the translator function, sends word to google
//gets result and calls the parce_google_result function
//with the buffer written by WriteCallback
std::string translate(CURL *curl, std::string word) {
  readBuffer.clear();
  
  char * ptr = curl_easy_escape(curl,word.c_str(), word.size() );
  std::string word_escaped(ptr);
  
  std::cout << word_escaped << std::endl;
  curl_free(ptr);
  
  std::string url = "http://translate.google.com/translate_a/t?"
					  "client=t&text=" + word_escaped + 
					  "&hl="+ g_source_language + 
					  "&sl="+ g_source_language +"&tl="
					  + g_language +
					  "&ie=UTF-8&oe=UTF-8"
					  "&multires=1&prev=btn&ssel=0&tsel=0&sc=1";
					  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
  }

   return parce_google_result(readBuffer);
}

//function for processing the word category
void process_category(CURL *curl, std::string filename,  bool spaceTab, std::string dir){
  
  std::string in_file = dir + filename + "/" + filename + "_BG.xml";

  ptree pt;
  read_xml(in_file, pt);
  
  bl::dict::Dict dict_; 
  bl::dict::ser::Dict::load(pt, dict_);
  
  for(std::vector<bl::dict::Word>::iterator it = 
	   dict_.words_.begin(); it != dict_.words_.end();++it ) {
  
	     std::string text = it->name_;
	     if(spaceTab) {
	        boost::replace_all(text, "   ", ",");
	     }
	     
	     it->translation_ =  boost::to_lower_copy (translate(curl, text));
	     if(spaceTab) {
	        boost::replace_all(it->translation_, ",", "   ");
	     }
	     std::cout << "word: " <<  it->name_ << " - translation: " << it->translation_ << std::endl;
	     sleep(2 + rand()%3);
	  }
  std::string out_file = dir + filename + "/" + filename + "_"+ boost::to_upper_copy(g_language)+ ".xml";
  
  bl::dict::ser::Dict::save(out_file, dict_);
  std::cout << "Processing Dict. output file name: " + out_file <<std::endl;
}

//function for processing the list of categories
//calls process_category()
void process_category_list(CURL *curl, std::vector< bl::Category>& c_list_, std::string out_dir ) {
  
  for(std::vector<bl::Category>::iterator it = 
	   c_list_.begin(); it != c_list_.end();++it ){
	     
	     std::string old = boost::to_lower_copy (it->name_);
	     it->name_ =  boost::to_upper_copy (translate(curl, old));
	     it->name_[0] = toupper(it->name_[0]);
	     it->title_ =  it->name_;
	     std::cout << old << " - " << it->name_ << std::endl;

	     process_category(curl, it->filename_, false, out_dir);

	     it->filename_ += "_" + boost::to_upper_copy(g_language)+ ".xml";

	     sleep(2 + rand()%3);
	  }
  std::string out_file = out_dir + "dict_"+ boost::to_upper_copy(g_language)+ ".xml";
  std::cout << "Processing Icons. output file name: " + out_file <<std::endl;
  
  bl::ser::CategoryList::save(out_file, c_list_);
}

//function for processing all files for all categories in a directory
//calls process_category_list()
void process_directory(CURL *curl, std::string dir, bool spaceTab = false){
  std::string in_file = dir + "dict_EN.xml";

  ptree pt;
  read_xml(in_file, pt);
  
  std::vector< bl::Category> c_list_;
  bl::ser::CategoryList::load(pt, c_list_);  
  process_category_list(curl, c_list_, dir);
}


//========================================= MAIN FUNCTION =====================================================//
int main(int argc, char** argv) 
{
    std::string with_directory_tree;
    namespace po = boost::program_options;
    //set program options
    po::options_description desc("Options");
    desc.add_options() 
      ("help,h", "Print help messages") 
      ("language,l", po::value<std::string>(&g_language), "language - bg, es, it, fr, ... ")
      ("filename,f", po::value<std::string>(&g_translate_filename), "translate file with filename")
      ("wdt,d", po::value<std::string>(&with_directory_tree), "with directory tree"); 
      
    po::positional_options_description positionalOptions; 
 
    po::variables_map vm; 
 
    try 
    { 
      po::store(po::command_line_parser(argc, argv).options(desc) 
                  .positional(positionalOptions).run(), 
                vm); // throws on error 
 
  
      if ( vm.count("help")  ) 
      { 
        std::cout << " run app like this ./translator -l bg" 
                  << std::endl << std::endl; 
       
        return 0; 
      } 
 
      po::notify(vm); // throws on error, so do after help in case 
                      // there are any problems 
    } 
    catch(boost::program_options::required_option& e) 
    { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
     
      return -1; 
    } 
    catch(boost::program_options::error& e) 
    { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      
      return -1; 
    } 
    
    if(g_language.empty()) {
      
      std::cerr << "ERROR: You need to specify the language, required!";
      g_language = "ru";
    }
   
  CURL *curl;
  curl = curl_easy_init();
  process_directory(curl, "./");
  

  curl_easy_cleanup(curl);
  
  return 0;
}

