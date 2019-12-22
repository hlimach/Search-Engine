#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//basic function declarations
map<string,int> loadLexicon();
map<int,map<int,vector<int>>> loadInvertedIndex();
map<int,map<int,int>> loadSmallInvertedIndex();

//creating a search vector
vector<int> search(string str);

int main() {
    //loading the lexicon and inverted indexes into the system
    map<string,int> lexicon = loadLexicon();
    map<int,map<int,vector<int>>> invertedIndex = loadInvertedIndex();
    map<int,map<int,int>> smallInvertedIndex =  loadSmallInvertedIndex();
    
    //loop to repeatedly ask for search word. This will later be editted to create a frontend of search queries
    while(true) {
        string word;
        cout << "Enter any word (enter -1 to end):" << endl; //prompting the user to input a word as a search query
        cin >> word;
        
        //check on the input word to exit the code if the word input is -1
        if(word == "-1")
            break;
        
        //converting the single word search query to lowercase inorder to check it against the lexicons
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        cout << "DocIDs with your word in it: " << endl;  //acknowledging the user 
    
        /*checking the input query word in the lexicon to see if the word exists. 
        In case of a match the lexicon.find() function will return a pointer to the word.
        In that case, we will take the the wordid and use it to find the documents that match the search query.
        If the lexicon.find() function does not find the word in the lexicon, it will return the iterator to the end of the 
        lexicon which will be used as a check to identify whether the word existed in the data or not. */
        
        if (lexicon.find(word) != lexicon.end()) {
            int wordId = lexicon.find(word)->second;
            
            //checking in the smaller fancy hit barrel to see whether the word exists as a fancy hit
            if(smallInvertedIndex.find(wordId) != smallInvertedIndex.end()) {
                map<int,int>::iterator itr = smallInvertedIndex.find(wordId)->second.begin();
            
                //if the word is found as a fancy hit, this code will display the names of all the documents that contain the word
                for(itr; itr != smallInvertedIndex.find(wordId)->second.end(); itr++)
                    cout << itr->first << endl;
            }
            else {
                //checking the other barrel to see if the word exists as a plain text
                map<int,vector<int>>::iterator itr = invertedIndex.find(wordId)->second.begin();
            
                for(itr; itr != invertedIndex.find(wordId)->second.end(); itr++)
                    cout << itr->first << endl;
            }
        }
        else {
            //if the lexicon.end() returns to the end of the lexicon, it will tell the user that the word does not exist in the data
            cout << "No matching results found!" << endl;
        }
    }
}

//function to load the lexicon file
map<string,int> loadLexicon() {
    ifstream lex;
    lex.open("lexicon.txt");
    map<string, int> lexicon;
    
    //error message if the lexicon file is not loaded
    if (lex.fail()) {
        cout << "Error: cannot open lexicon file" << endl;
        return lexicon;
    }
    
    //the loop that reads the lexicon.txt line by line and creates a lexicon map
    while (true) {
        string str, word;
        getline(lex, word, '\n');

        if (word == ".") break;

        getline(lex, str, '\n');
        lexicon.insert({word,stoi(str)});
    }
    
    return lexicon;
}

//the function to load the inverted index into the system
map<int,map<int,vector<int>>> loadInvertedIndex() {
    ifstream index;
    index.open("inverted_index.txt");
    map<int, map<int,vector<int>>> invertedIndex;
    
    //loop till the end of the file
    while (!index.eof()) {
        map<int,vector<int>> hits;
        string str;
        getline(index, str, '\n');

        if (str == "") break;

        int wordID = stoi(str);

        //loop to read the inverted into the map
        while (true) {
            getline(index, str, '\n');
            if (str == "_") break;
            int docID = stoi(str);
            vector<int> temp;
            
            while (true) {
                getline(index, str, '\n');
                if (str == "." || str == "_") break;
                temp.push_back(stoi(str));
            }
            
            //inputting the docID against its hits into the map against its wordID
            hits.insert({docID,temp});
        }
        
        invertedIndex.insert({wordID, hits});
    }
    //returning the fully generated inverted index
    return invertedIndex;
}

//the function similar to the previous one that reads the shorter barrel into the system
map<int,map<int,int>> loadSmallInvertedIndex() {
    ifstream index;
    index.open("small_inverted_index.txt");
    map<int, map<int,int>> smallInvertedIndex;
    
    while (!index.eof()) {
        map<int,int> fancyHits;
        string str;
        getline(index, str, '\n');

        if (str == "")
            break;
        
        int wordID = stoi(str);
        while(true) {
            getline(index, str, '\n');
            
            if(str == "_")
                break;
            
            int docID = stoi(str);
            getline(index, str, '\n');
            int count = stoi(str);
            
            fancyHits.insert({docID,count});
        }
        smallInvertedIndex.insert({wordID, fancyHits});
    }
    
    //returning the fully generated shorter barrel
    return smallInvertedIndex;
}

