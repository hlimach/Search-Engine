#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

map<string,int> loadLexicon();
map<int,vector<vector<int>>> loadInvertedIndex(string filename);
map<int,vector<vector<int>>> loadSmallInvertedIndex();
vector<vector<int>> singlewordSearch(int wordID, map<int,vector<vector<int>>> smallInvertedIndex, map<int,vector<vector<int>>> invertedIndex);

int main() {

    map<string,int> lexicon = loadLexicon();
    cout << "lex" << endl;
    map<int,vector<vector<int>>> invertedIndex1 = loadInvertedIndex("inverted_index1.txt");
    cout << "ii1" << endl;
    map<int,vector<vector<int>>> invertedIndex2 = loadInvertedIndex("inverted_index2.txt");
    cout << "ii2" << endl;
    map<int,vector<vector<int>>> invertedIndex3 = loadInvertedIndex("inverted_index3.txt");
    cout << "ii3" << endl;
    map<int,vector<vector<int>>> invertedIndex4 = loadInvertedIndex("inverted_index4.txt");
    cout << "ii4" << endl;
    map<int,vector<vector<int>>> smallInvertedIndex =  loadSmallInvertedIndex();
    cout << "sii" << endl;
    
    while(true){
    string word, str;
    
    cout << "Enter a word (-1 to exit) : " << endl;
    cin >> word;
        
        if(word == "-1") break;
    if (lexicon.find(word) != lexicon.end()) {
        vector<vector<int>> docIDs;
        int wordID = lexicon.find(word)->second;
            
        if (wordID % 4 == 0)
            docIDs = singlewordSearch(wordID, smallInvertedIndex, invertedIndex4);
        else if (wordID % 3 == 0)
            docIDs = singlewordSearch(wordID, smallInvertedIndex, invertedIndex3);
        else if (wordID % 2 == 0)
            docIDs = singlewordSearch(wordID, smallInvertedIndex, invertedIndex2);
        else
            docIDs = singlewordSearch(wordID, smallInvertedIndex, invertedIndex1);
                
        cout << "Documents with your query: " << endl;
        for(int i = 0; i < docIDs.size(); i++)
            cout << docIDs[i][0] << endl;
            
        }
        
        else {
            cout << "No matching results found!" << endl;
        }
    }
}

vector<vector<int>> singlewordSearch(int wordID, map<int,vector<vector<int>>> smallInvertedIndex, map<int,vector<vector<int>>> invertedIndex) {
    vector<vector<int>> docIDs;
    map<int,vector<vector<int>>>::iterator itr = smallInvertedIndex.find(wordID);
    
    if(itr != smallInvertedIndex.end()) {
        bool swapped;
        for (int i = 0; i < itr->second.size(); i++) {
           swapped = false;
           for (int j = 0; j < itr->second.size()-1; j++) {
               
              if (itr->second[j][1] > itr->second[j+1][1]) {
                 swap(itr->second[j], itr->second[j+1]);
                 swapped = true;
              }
               
           }
        
           if (swapped == false)
              break;
        }
        docIDs = itr->second;
    }
    
    if (docIDs.size() < 5) {
        map<int,vector<vector<int>>>::iterator itr = invertedIndex.find(wordID);
        vector<vector<int>> secondary;
        for(int i = 0; i != itr->second.size(); i++) {
            vector<int> temp;
            temp.push_back(itr->second[i][0]);
            temp.push_back(itr->second[i].size()-1);
            secondary.push_back(temp);
        }
        
        bool swapped;
        for (int i = 0; i < secondary.size(); i++) {
           swapped = false;
           for (int j = 0; j < secondary.size()-1; j++) {
              if (secondary[j][1] > secondary[j+1][1]) {
                 swap(secondary[j], secondary[j+1]);
                 swapped = true;
              }
           }
           if (swapped == false)
              break;
        }
        for(int i = 0; i < secondary.size(); i++)
            docIDs.push_back(secondary[i]);
    }

    return docIDs;
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

map<int,vector<vector<int>>> loadInvertedIndex(string filename) {
    ifstream index;
    index.open(filename);
    map<int,vector<vector<int>>> invertedIndex;
    
    while (!index.eof()) {
        vector<vector<int>> hits;
        string str;
        getline(index, str, '\n');

        if (str == "") break;

        int wordID = stoi(str);

        while (true) {
            getline(index, str, '\n');
            if (str == "_") break;
            vector<int> temp;
            temp.push_back(stoi(str));
            
            while (true) {
                getline(index, str, '\n');
                if (str == "." || str == "_") break;
                temp.push_back(stoi(str));
            }
            
            hits.push_back(temp);
        }
        
        invertedIndex.insert({wordID, hits});
    }
    
    return invertedIndex;
}

map<int,vector<vector<int>>> loadSmallInvertedIndex() {
    ifstream index;
    index.open("small_inverted_index.txt");
    map<int, vector<vector<int>>> smallInvertedIndex;
    
    while (!index.eof()) {
        vector<vector<int>> fancyHits;
        string str;
        getline(index, str, '\n');

        if (str == "")
            break;
        
        int wordID = stoi(str);
        while(true) {
            vector<int> temp;
            getline(index, str, '\n');
            
            if(str == "_")
                break;
            
            int docID = stoi(str);
            getline(index, str, '\n');
            int count = stoi(str);
            
            temp.push_back(docID);
            temp.push_back(count);
            fancyHits.push_back(temp);
        }
        smallInvertedIndex.insert({wordID, fancyHits});
    }
    
    return smallInvertedIndex;
}

