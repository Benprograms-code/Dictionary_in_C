// Word.h
#include <iostream>
#ifndef WORD_H
#define WORD_H
using namespace std;
#include <string>
// word header holds the the functions directly related 
// 15/05/24
// Ben Baxter 
class Word {
private:
    string name;
    string type;
    string definition;

public:
    // Constructor
    Word() {}

    // Constructor with parameters
    Word(const string& name, const string& type, const string& definition)
        : name(name), type(type), definition(definition) {}

    // Getters and setters
    string getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    string getType() const {
        return type;
    }

    void setType(const string& newType) {
        type = newType;
    }

    string getDefinition() const {
        return definition;
    }

    void setDefinition(const string& newDefinition) {
        definition = newDefinition;
    }

    // Function to print the word's name, type, and definition
    void printDefinition() const {
        cout << "Word: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Definition: " << definition << endl;
    }
   
};

#endif // WORD_H
