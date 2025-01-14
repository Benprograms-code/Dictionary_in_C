#ifndef IMPROVEDDICTIONARY_H
#define IMPROVEDDICTIONARY_H
using namespace std;
#include "dictionary.h"

// declare all functions from improveddicitionary.cpp 
// ImporvedDictionary class is an extentions of the Dictionary class
// 14/05/24
// Ben Baxter
class ImprovedDictionary : public Dictionary {
private:
   
public:
    // Constructor
    ImprovedDictionary() {}

    // Destructor
    ~ImprovedDictionary() {}

 

    // Override the menu function
    void menu();

    void palindromes();
    bool isPalindrome(const string& str);

    void findRhymingWords();

    void addWord();


    bool wordExists(const string& name) const;

    void saveToFile(const string& filename) const;

    void playGuessTheFourthWordGame();

    int loadHighScore() const;

    void saveHighScore(int score) const;

    vector<string> tokenizeDefinition(const string& definition) const;

    

    string getFourthWord(const string& definition) const;


   

    

   
   
    
};

#endif // IMPROVEDDICTIONARY_H
