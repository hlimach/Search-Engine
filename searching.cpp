/*#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string,int> loadLexicon();
map<int,map<int,vector<int>>> loadInvertedIndex();
map<int,map<int,int>> loadSmallInvertedIndex();
vector<int> search(string str);

int main() {
    
    map<string,int> lexicon = loadLexicon();
    map<int,map<int,vector<int>>> invertedIndex = loadInvertedIndex();
    map<int,map<int,int>> smallInvertedIndex =  loadSmallInvertedIndex();
    
    while(true) {
        string word;
        cout << "Enter any word (enter -1 to end):" << endl;
        cin >> word;
        
        if(word == "-1")
            break;
        
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        cout << "DocIDs with your word in it: " << endl;
    
        if (lexicon.find(word) != lexicon.end()) {
            int wordId = lexicon.find(word)->second;
        
            if(smallInvertedIndex.find(wordId) != smallInvertedIndex.end()) {
                map<int,int>::iterator itr = smallInvertedIndex.find(wordId)->second.begin();
            
                for(itr; itr != smallInvertedIndex.find(wordId)->second.end(); itr++)
                    cout << itr->first << endl;
            }
            else {
                map<int,vector<int>>::iterator itr = invertedIndex.find(wordId)->second.begin();
            
                for(itr; itr != invertedIndex.find(wordId)->second.end(); itr++)
                    cout << itr->first << endl;
            }
        }
        else {
            cout << "No matching results found!" << endl;
        }
    }
}

map<string,int> loadLexicon() {
    ifstream lex;
    lex.open("lexicon.txt");
    map<string, int> lexicon;
    
    if (lex.fail()) {
        cout << "Error: cannot open lexicon file" << endl;
        return lexicon;
    }
    
    while (true) {
        string str, word;
        getline(lex, word, '\n');

        if (word == ".") break;

        getline(lex, str, '\n');
        lexicon.insert({word,stoi(str)});
    }
    
    return lexicon;
}

map<int,map<int,vector<int>>> loadInvertedIndex() {
    ifstream index;
    index.open("inverted_index.txt");
    map<int, map<int,vector<int>>> invertedIndex;
    
    while (!index.eof()) {
        map<int,vector<int>> hits;
        string str;
        getline(index, str, '\n');

        if (str == "") break;

        int wordID = stoi(str);

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
            
            hits.insert({docID,temp});
        }
        
        invertedIndex.insert({wordID, hits});
    }
    
    return invertedIndex;
}

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
    
    return smallInvertedIndex;
}
*/
