#include "HelperLibrary.h"
#include <string>


void WhiteSpace::trim(std::string & input) {
  if(!input.empty()){
    std::size_t firstScan = input.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? input.length() : firstScan;
    std::size_t last      = input.find_last_not_of(' ');
    input = input.substr(first, last-first+1);
    //check if the last character is a unix terminating character
    if (input.substr(input.length()-1, input.length()) == "\r") {
      input.erase(input.length()-1);
    }
  }
}
