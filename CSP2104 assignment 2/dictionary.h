#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <fstream>
#include "Word.h.cpp"

// declare all functions from dicitionary.cpp
// 14/05/24
// Ben Baxter
class Dictionary {
private:
   vector<Word> dictionary;

public:
    void File_load(bool& dictionaryload);
    Word binarySearch(const string& target);
    void menu();
    void LowCase(string& targetString);
    const vector<Word>& getDictionary() const  {
        return dictionary;
    }
    // allows modification of dictionary vector if needed
    void addWordToDictionary(const Word& word) {
        dictionary.push_back(word);
    }
};

#endif // DICTIONARY_H
