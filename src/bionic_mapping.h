#ifndef BIONIC_MAPPING_H 
#define BIONIC_MAPPING_H  

#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "dictionary.h"

class bionicMapping {
    public:
        // generate the original bionic_mapping between
        // all words and their bolded version
        bionicMapping(const std::string filename, int size_line=5) 
        : _bionic_mapping(BIONIC_MAPPING::word_to_bold),_size_line(size_line) 
        {
            std::__fs::filesystem::path pathObj(filename);
            _filename = (pathObj.parent_path() / (pathObj.stem().string() + "_BOLDED" + pathObj.extension().string())).string();
            
            std::fstream input_file(filename);
            if (!input_file.is_open()) {
                std::cerr << "Error: Unable to open the file " << _filename << std::endl;
                return;
            }

            std::string line;
            while (std::getline(input_file, line)) {
                std::istringstream token(line);
                std::string word;
                while (token >> word) {
                    _text.push_back(word);
                }
            }
        }
        void createBionicText() {
            std::string bold_start = "\033[1m";
            std::string bold_end = "\033[0m";

            for (int i=0; i<_text.size(); ++i) {
                std::string raw_word = _text[i];
                std::string bold_word = "";
                for (auto& x : raw_word) { 
                    bold_word += tolower(x); 
                } 
                
                int len = 0;
                if (_bionic_mapping.find(bold_word) != _bionic_mapping.end()) {
                    len = _bionic_mapping[bold_word];
                } else {
                    len = raw_word.length() / 2;
                    _undocumented_words.push_back(raw_word);
                }
                bold_word = "";
                for (int j=0; j<raw_word.length(); ++j) {
                    if (j < len)
                        bold_word += bold_start + raw_word[j] + bold_end; // Convert to uppercase for bold effect (you can adjust formatting as needed)
                    else
                        bold_word += raw_word[j];
                }

                _text[i] = bold_word;
            }
        }

        void printText() {
            // std::cout << _filename << std::endl;
            for (int i = 0; i< _text.size(); ++i) {
               std::cout << _text[i];
               if ((i+1) % _size_line == 0)
                    std::cout << std::endl;
               else
                    std::cout << " ";
            }
            std::cout << std::endl;

            // print undocumented words
            // std::cout << "==================" << std::endl;

            // for (int j=0; j< _undocumented_words.size(); ++j) {
            //     std::cout << _undocumented_words[j];
            //     if ((j+1) % _size_line == 0)
            //         std::cout << std::endl;
            //     else
            //         std::cout << " ";
            // }
            // std::cout << "done!" << std::endl;
        }


        void writeText() {

            std::ofstream outputFile(_filename);
             if (!outputFile.is_open()) {
                std::cerr << "Error: Unable to open the file for writing." << std::endl;
                return;
            }   
            for (int i = 0; i< _text.size(); ++i) {
               outputFile << _text[i];
               if ((i+1) % _size_line == 0)
                    outputFile << std::endl;
               else
                    outputFile << " ";
            }
  
        }
    
    private:
        std::unordered_map<std::string, int> _bionic_mapping;
        int _size_line;

        std::vector<std::string> _undocumented_words;
        std::string _filename;
        std::vector<std::string> _text;
        

    };



#endif /* BIONIC_MAPPING.H */