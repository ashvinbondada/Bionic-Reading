// phone app?

#include <iostream>


#include "bionic_mapping.h"
using namespace std;

// bionicMapping* processFile(const std::string& raw_text_file) {
//     std::fstream input_file(raw_text_file);

//     if (!input_file.is_open()) {
//         std::cerr << "Error: Unable to open the file " << raw_text_file << std::endl;
//         return nullptr;
//     }

//     std::string line;
//     std::vector<std::string> words;
//     while (std::getline(input_file, line)) {
//         std::istringstream token(line);
//         std::string word;
//         while (token >> word) {
//             words.push_back(word);
//         }
//     }
//     bionicMapping* mapping = new bionicMapping(input_file, words);

//     input_file.close();
//     return mapping;
// }
int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <#ofWordsPerLine>" << std::endl;
        return 1;
    }
    const std::string raw_text_file = argv[1];
    const int num_words_per_line = std::stoi(argv[2]);

    bionicMapping* text_mapping = new bionicMapping(raw_text_file, num_words_per_line);
    text_mapping->createBionicText();
    text_mapping->printText();
    text_mapping->writeText();



}
