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

static size_t WriteCallback(void *contents, size_t size, size_t nmemb)
{ 
    size_t realsize = size * nmemb;
    readBuffer.append(contents, realsize);
    return realsize;
}

std::string translate(CURL *curl, std::string word) {
  CURLcode res;
  std::string result;
  readBuffer.clear();
 
  return result;
}


//========================================= MAIN FUNCTION =====================================================//
int main(int argc, char** argv) 
{
    std::string with_directory_tree;
    
  
    return 0;
}

