#include "Dictionary.h"
#include <iostream>
#include <cctype>
#include "Word.h.cpp"


// this function does a few thing, first of which it recieves a file name from the user, if the file doesn't exist it'll load the defualt file provided.
// once the file has loaded it'll parse the file, it'll do this by finding the headers such as "type:, Definition;, word:" then it'll delete the headers and store the info in the vector, assigning to corresponding 'w.'.
// 24/03/2024 created ~modified on 14/05/24 use setters to access vector 
// Ben Baxter

void Dictionary::File_load(bool& dictionaryload) {
    string file_name = "dictionary_2024s1.txt";
    string user_filename = "";
    cout << "What's the name of the file you would like to open?: ";
    cin >> user_filename;

    // Convert user_filename to lowercase
    for (char& c : user_filename) {
        c = tolower(c);
    }

    if (user_filename != "") {
        ifstream file;
        if (user_filename == file_name) {
            cout << "Opening: " << file_name << endl;
            file.open(file_name);
        }
        else {
            cout << "Opening: " << user_filename << endl;
            file.open(user_filename);
            if (!file.is_open()) {
                cout << "This file doesn't exist.\nLoading default file: " << file_name << endl;
                file.open(file_name);
            }
        }

        if (!file.is_open()) {
            cout << "There was an error opening the file." << endl;
            return;
        }

        Word* w = nullptr;
        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;

            if (line.find("Type: ") == 0) {
                if (w != nullptr) { // Check if w is not null
                    addWordToDictionary(*w); // Add the previous word to the dictionary
                    delete w; // Delete the dynamically allocated memory
                }
                w = new Word(); // Allocate memory for a new Word object
                w->setType(line.substr(6)); // Use setter method to set type
            }
            else if (line.find("Word: ") == 0) {
                w->setName(line.substr(6)); // Use setter method to set name
            }
            else if (line.find("Definition: ") == 0) {
                w->setDefinition(line.substr(12)); // Use setter method to set definition
            }
        }
        if (w != nullptr) { // Check if there is a pending word
            addWordToDictionary(*w); // Add the pending word to the dictionary
            delete w; // Delete the dynamically allocated memory
        }

        file.close();
        cout << "Dictionary loaded" << endl;
        dictionaryload = true;
    }
}

// Binary search algorithim - self explanatory, it searches for words,
// it has parameters of 'dictionary' which represents the 'word' within the vector and 'target' which is the searchjed word
// works by comparing the target word to the middle of the vector, the alorithim will delete the halfs the target word can't exist within each interation, more efficent than linear searches
// 24/03/2024 created ~modified on 14/05/24 implementaation of getters
// Ben Baxter
Word Dictionary::binarySearch(const string& target) {
    int low = 0;
    int high = dictionary.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (dictionary[mid].getName() == target) // Use getter method to access name
            return dictionary[mid];
        else if (dictionary[mid].getName() < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return Word("", "", "");
}

// main very basic menu system using if statements, utilising previously made functions  uses while statements to constantly loop menu 
 //25/03/2024
 //Ben Baxter
void Dictionary::menu() {
    bool mainMenu = true;
    bool dictionaryload = false;

    while (mainMenu) {
        string userInput;
        cout << "Dictionary Main Menu\n";
        cout << "--------------------\n";
        cout << "To load desired dictionary, please press 1 (note: you only need to load the dictionary once)\n";
        cout << "--------------------\n";
        cout << "To find a selected word and definition in the dictionary, please press 2\n";
        cout << "--------------------\n";
        cout << "Press 4 to exit the program\n";
        cin >> userInput;

        if (userInput == "1") {
            File_load(dictionaryload);
            if (dictionaryload) {
                cout << "\nLoading complete\n\n";
            }
            continue;
        }

        if (userInput == "2") {
            string searchWord;
            cout << '\n' << "What word are you looking for?: ";
            cin >> searchWord;

            LowCase(searchWord);
            Word result = binarySearch(searchWord);

            if (result.getName() == searchWord) {
                result.printDefinition();
            }
            else {
                cout << "Word '" << searchWord << "' not found in the dictionary." << endl;
            }
            int repeatSearch;
            cout << "Would you like to search for another word? Press 1 for yes or 2 for no: " << endl;
            cin >> repeatSearch;
            if (repeatSearch == 1)
                continue;
            if (repeatSearch == 2)
                break;
            else
                cout << "Not a valid input. Returning to the main menu." << endl;
            break;
        }

        if (userInput == "4") {
            cout << '\n' << "Quitting program";
            break;
        }
    }
}
// forces strings into lowercase through the use of the tolower function 
    // 20/03/2024 
    // Ben Baxter
void Dictionary::LowCase(string& targetString) {
    for (char& i : targetString)
        i = tolower(i);
}