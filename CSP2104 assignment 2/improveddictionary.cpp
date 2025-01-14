using namespace std;
#include <algorithm>
#include <set>
#include <list>
#include "word.h.cpp"
#include "improveddictionary.h"

// main very basic menu system using if statements, utilising previously made functions  uses while statements to constantly loop menu 
    //25/03/2024
    // modified 15/05/24
    // added functionality for improved dictionary under new sub menu 
    //Ben Baxter

void ImprovedDictionary::menu() {
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
        cout << "to access improved dictionary utilities press 3\n";
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
        if (userInput == "3") {
            // Submenu for improved dictionary utilities
            while (true) {
                cout << "\nImproved Dictionary Utilities\n";
                cout << "-----------------------------\n";
                cout << "1. Check for Palindromes\n";
                cout << "2. Find Rhyming Words\n";
                cout << "3. Add a Word\n";
                cout << "4. play guess the forth word game\n";
                cout << "5. Return to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> userInput;

                if (userInput == "1") {
                    palindromes();
                }
                else if (userInput == "2") {
                    findRhymingWords();
                }
                else if (userInput == "3") {
                    addWord();
                }
                else if (userInput == "4") {
                    playGuessTheFourthWordGame();
                }
                else if (userInput == "5") {
                    break;
                }
                else {
                    cout << "Invalid choice. Please enter a valid option.\n";
                }
            }
            continue; // Continue with the main menu loop
        }

        if (userInput == "4") {
            cout << '\n' << "Quitting program";
            break;
        }
    }
}

// palendrome function, doesn't perform the actual palendrome check but stores the palendromes in a list 
//15/05/24
//Ben Baxter
void ImprovedDictionary::palindromes() {
    list<string> palindromeList; // List to store palindromes
    int palindromecount = 0;
    cout << "Palindromes in the dictionary:\n";
    const auto& dict = getDictionary();
    for (const auto& word : dict) {
        
        if (isPalindrome(word.getName())) {
            palindromeList.push_back(word.getName()); // Store palindrome in the list
            palindromecount++;
        }
    }

    // Print palindromes from the list
    for (const auto& palindrome : palindromeList) {
        cout << palindrome << endl;
    }
    cout << "amount of palendromes: " << palindromecount << endl;
}
// performs the palendrom check on each word, works be checking if the fathest left charcter and farthest right character are == 
// incrementing till it reaches the middle of the word, if not equal then false and not palendrome
// 15/05/24
//Ben Baxter
bool ImprovedDictionary::isPalindrome(const std::string& str) {
    int left = 0;
    
    int right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// find rhyme function- works by extracting the final three letters of a word given 
// then comparing the three letters with the final three letters of the dictionary word and holds all amtches then prints
// 15/04/24
// Ben Baxter

void ImprovedDictionary::findRhymingWords() {
    string inputWord;
    cout << "Enter a word to find rhyming words: ";
    cin >> inputWord;

    // Convert input word to lowercase
    LowCase(inputWord);

    // Extract the last three letters from the input word
    string inputSuffix = inputWord.substr(inputWord.length() - 3);

    // Set to store unique rhyming words
    set<string> rhymingWords;

    // Iterate through the dictionary to find rhyming words
    const auto& dict = getDictionary();
    for (const auto& word : dict) {
        string currentWord = word.getName();
        // Convert current word to lowercase
        LowCase(currentWord);

        // Check if the current word ends with the same sequence of three letters as the input word
        if (currentWord.length() >= 3 && currentWord.substr(currentWord.length() - 3) == inputSuffix) {
            rhymingWords.insert(word.getName());
        }
    }

    // Print the rhyming words
    if (rhymingWords.empty()) {
        cout << "No rhyming words found." << endl;
    }
    else {
        cout << "Rhyming words for \"" << inputWord << "\": ";
        for (const auto& word : rhymingWords) {
            cout << word << " " << endl;
        }
        cout << endl;
    }
}

// function used to add words to the dictyionary file you've loaded by either overwriting or creating a new dictionary file with appended changes 
// this function essential retrieves new word,type and definition and holds the other functions related
// 16/05/24
// Ben Baxter
void ImprovedDictionary::addWord() {
    //intialise data
    string userWord;
    string userType;
    string userDefinition;
    bool closeLoop = false;

    while (!closeLoop) {
        closeLoop = true;

        cout << "Enter a word that you would like to add to the dictionary: ";
        getline(cin, userWord);

        // Check if word already exists
        if (wordExists(userWord)) {
            cout << "Error: Word exists." << endl;
            cout << "Type 'exit' to exit or anything else to try again: ";
            string userExit;
            getline(cin, userExit);
            if (userExit == "exit") {
                return;
            }
            closeLoop = false;
            continue;
        }

        if (userWord.empty()) {
            cout << "Error: The input doesn't contain any word." << endl;
            closeLoop = false;
        }
    }

    // get word type
    cout << "Enter the type of the word (e.g., noun, verb, adjective): ";
    getline(cin, userType);

    // Fetch word definition
    std::cout << "Enter the definition of the word: ";
    getline(cin, userDefinition);

    // Create a new Word object
    Word newWord(userWord, userType, userDefinition);

    // Add the new word to the dictionary
    addWordToDictionary(newWord);

    // Save the dictionary to file 
    cout << "Do you want to overwrite dictionary_2024s1.txt? if not a new file will be created (yes/no): ";
    string overwrite;
    getline(cin, overwrite);
    if (overwrite == "yes") {
        saveToFile("dictionary_2024s1.txt");
    }
    else {
        saveToFile("dictionary.txt");
    }

    cout << "Word successfully added!" << endl;
}


// checks if word exist , uses get_name, iterates running comparison 
// 15/05/24
// Ben Baxter

bool ImprovedDictionary::wordExists(const string& name) const {
    for (const auto& word : getDictionary()) {
        if (word.getName() == name) {
            return true;
        }
    }
    return false;
}
// opens file in append mode then sdaves new word, this avoids reloading the file 
// 16/05/24
// Ben baxter
void ImprovedDictionary::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    for (const auto& word : getDictionary()) {
        file  <<word.getName() << endl;
        file<< word.getDefinition() << endl;
        file  << word.getType() << endl;
        file << "" << endl;
    }

    file.close();
}







//this is the foundation for the guessing the forth word game
// is does perform some tasks of its own such as the randome word generation which works by finding a word by randomly searching index numbers
// and will only break out of look till it finds a word with a definitioon lomger than 4 words, this code is also responsible for replacing forth word with "_"
// it works similar to find fourth word by incrementing till forth then replacing all characters with __. the code then checks user input reqrding 10 point if successful 
// and stops game if iccorrect answer is given saving the highscore
// 17/05/24
// Ben Baxter   
void ImprovedDictionary::playGuessTheFourthWordGame() {
    cout << "Welcome to Guess the Fourth Word Game!\n";

    int highScore = loadHighScore(); // Load the high score from file
    cout << "highscore: " << highScore <<" points" << endl;
    int score = 0;
    srand(time(0));
    // Recursive game loop
    while (true) {
        // Get a random word with more than 4 words in its definition
        const auto& dict = getDictionary();
        const Word* randomWordPtr = nullptr;
        while (true) {
            const Word& randomWord = dict[rand() % dict.size()];
            string definition = randomWord.getDefinition();
            int wordCount = count(definition.begin(), definition.end(), ' ') + 1;
            if (wordCount > 4) {
                randomWordPtr = &randomWord;
                break;
            }
        }

        // Tokenize the definition into words
        vector<string> words = tokenizeDefinition(randomWordPtr->getDefinition());

        // Replace the fourth word with underscores
        if (words.size() >= 4) {
            words[3] = string(words[3].size(), '_');
        }

        // Print the word and the modified definition
        cout << "Word: " << randomWordPtr->getName() << endl;
        cout << "Definition: ";
        for (const string& w : words) {
            cout << w << " ";
        }
        cout << endl;

        // Prompt the player to guess the fourth word
        string guess;
        cout << "Guess the missing word: ";
        cin >> guess;

        // Check the guess
        string actualWord = getFourthWord(randomWordPtr->getDefinition());
        if (guess == actualWord) {
            cout << "Congratulations! You guessed correctly.\n";
            score+=10;
        }
        else {
            cout << "Incorrect guess. The correct word is: " << actualWord << endl;
            cout << "your score was: " << score << endl;
            break; // Break the loop if the guess is incorrect
        }
    }

    // Update high score and save to file
    if (score > highScore) {
        cout << "New high score: " << score << endl;
        saveHighScore(score);
    }
}
//self expainitory loads txt file with the high score within
// 17/05/24
// Ben Baxter
int ImprovedDictionary::loadHighScore() const {
    int highScore = 0;
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    return highScore;
}
//saves highs score 
// 17/05/24
// Ben Baxter
void ImprovedDictionary::saveHighScore(int score) const {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    }
}






// this tokenisation prgram is used to seperate the defintion based on words instead of characters, makes finding the forth word easier
//17/05/24
//Ben Baxter 
vector<string> ImprovedDictionary::tokenizeDefinition(const string& definition) const {
    vector<string> words;
    string currentWord;

    for (char c : definition) {
        if (c == ' ') {
            // If a space is encountered, add the current word to the vector and reset it
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        else {
            // Append non-space characters to the current word
            currentWord += c;
        }
    }

    // Add the last word if it's not empty
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    return words;
}



// checks if there is at least 4 words within definition
// if there is more than four words is returns the forth "words[3]"
//  17/05/24
//Ben Baxter
string ImprovedDictionary::getFourthWord(const string& definition) const {
    vector<string> words = tokenizeDefinition(definition);
    if (words.size() >= 4) {
        return words[3];
    }
    return ""; // Return empty string if there are less than 4 words
}
