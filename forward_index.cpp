#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

void writeForwardIndex(ofstream& index, int docID, map<int,vector<int>> hits);

int main() {
    
    ifstream file;
    ofstream f1index, f2index, f3index, f4index, outputlex;

    f1index.open("f1_index.txt");
    f2index.open("f2_index.txt");
    f3index.open("f3_index.txt");
    f4index.open("f4_index.txt");
    outputlex.open("lexicon.txt");

    int docID = 1, fancy = -1, lastWordID = 0;
    map<string, int> lexicon;
    
    auto start = high_resolution_clock::now();
    
    while (docID < 1001) {
        file.open(to_string(docID) + ".txt");
        
        if (file.fail()) {
            cout << "Error: Cannot open file: " << docID << endl;
            return -1;
        }
        
        if(docID % 5000 == 0)
            cout << docID << endl;
        
        map<int,vector<int>> hits1, hits2, hits3, hits4;
        int plain = 0, count = 0;
        string str, word;

        while(getline(file, str, '\n')) {
            
            stringstream str1(str);
            
            while (getline(str1, word, ' ')) {
                int wordID;
                map<string, int>::iterator lexitr = lexicon.find(word);
                
                if (lexitr != lexicon.end())
                    wordID = lexitr->second;
                else {
                    wordID = lastWordID + 1;
                    lexicon.insert({ word, wordID });
                    outputlex << word << endl << wordID << endl;
                    lastWordID++;
                }
                
                map<int,vector<int>>::iterator hitsitr;
                
                if (wordID % 4 == 0) {
                    hitsitr = hits4.find(wordID);

                    if (hitsitr == hits4.end()) {
                        hits4.insert({wordID,vector<int>()});
                        hitsitr = hits4.find(wordID);
                    }
                }
                else if (wordID % 3 == 0) {
                    hitsitr = hits3.find(wordID);

                    if (hitsitr == hits3.end()) {
                        hits3.insert({wordID,vector<int>()});
                        hitsitr = hits3.find(wordID);
                    }
                }
                else if (wordID % 2 == 0) {
                    hitsitr = hits2.find(wordID);

                    if (hitsitr == hits2.end()) {
                        hits2.insert({wordID,vector<int>()});
                        hitsitr = hits2.find(wordID);
                    }
                }
                else {
                    hitsitr = hits1.find(wordID);

                    if (hitsitr == hits1.end()) {
                        hits1.insert({wordID,vector<int>()});
                        hitsitr = hits1.find(wordID);
                    }
                }
                
                if (count == 0 || count == 1 || count == 2 || count == 3)
                    hitsitr->second.push_back(fancy);
                else if (count == 6) {
                    hitsitr->second.push_back(plain);
                    plain++;
                }
                
            }
            
            count++;
        }
        
        //writing into all 4 barrels
        writeForwardIndex(f1index, docID, hits1);
        writeForwardIndex(f2index, docID, hits2);
        writeForwardIndex(f3index, docID, hits3);
        writeForwardIndex(f4index, docID, hits4);
        
        docID++;
        file.close();
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    
    f1index.close();
    cout << "Forward index file 1 finalized." << endl;
    
    f2index.close();
    cout << "Forward index file 2 finalized." << endl;
    
    f3index.close();
    cout << "Forward index file 3 finalized." << endl;
    
    f4index.close();
    cout << "Forward index file 4 finalized." << endl;
    
    outputlex << ".";
    outputlex.close();
    cout << "Lexicon file finalized." << endl;
    
    cout << "Time taken: " << (duration.count()) << " seconds" << endl;

    return 0;
}

void writeForwardIndex(ofstream& index, int docID, map<int,vector<int>>hits) {
    
    index << docID << endl;
    for(map<int,vector<int>>::iterator itr = hits.begin(); itr != hits.end(); itr++) {
        index << itr->first << endl;
        
        for(int i = 0; i < itr->second.size(); i++)
            index << itr->second[i] << endl;
        
        index << "." << endl;
    }
    index << "_" << endl;
    
}
