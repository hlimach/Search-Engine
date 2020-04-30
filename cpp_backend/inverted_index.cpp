#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

map<int, vector<vector<int>>> genForwardIndex (ifstream& findex); //reads forward index file into map
void writeInvertedIndex (ofstream& outputfile, ofstream& shortIndex, map<int, vector<vector<int>>> invertedIndex);
map<int, vector<vector<int>>> genInvertedIndex (map<int, vector<vector<int>>> findex); //generates ii

int main() {
    ifstream fi1, fi2, fi3, fi4;
    ofstream ii1, ii2, ii3, ii4, shortIndex;

    //opening files
    fi1.open("f1_index.txt");
    fi2.open("f2_index.txt");
    fi3.open("f3_index.txt");
    fi4.open("f4_index.txt");
    ii1.open("inverted_index1.txt");
    ii2.open("inverted_index2.txt");
    ii3.open("inverted_index3.txt");
    ii4.open("inverted_index4.txt");
    shortIndex.open("small_inverted_index.txt");

    //exception if forward index file is not opened
    if (fi1.fail() || fi2.fail() || fi3.fail() || fi4.fail()) {
        cout << "Error: Cannot open forward index files." << endl;
        return -1;
    }

    auto start = high_resolution_clock::now();
    
    map<int, vector<vector<int>>> f1index = genForwardIndex(fi1);
    map<int, vector<vector<int>>> f2index = genForwardIndex(fi2);
    map<int, vector<vector<int>>> f3index = genForwardIndex(fi3);
    map<int, vector<vector<int>>> f4index = genForwardIndex(fi4);
    
    map<int, vector<vector<int>>> i1index = genInvertedIndex(f1index);
    map<int, vector<vector<int>>> i2index = genInvertedIndex(f2index);
    map<int, vector<vector<int>>> i3index = genInvertedIndex(f3index);
    map<int, vector<vector<int>>> i4index = genInvertedIndex(f4index);
    
    writeInvertedIndex(ii1, shortIndex, i1index);
    writeInvertedIndex(ii2, shortIndex, i2index);
    writeInvertedIndex(ii3, shortIndex, i3index);
    writeInvertedIndex(ii4, shortIndex, i4index);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time taken: " << (duration.count()) << " seconds" << endl;

    return 0;
}

map<int, vector<vector<int>>> genInvertedIndex (map<int, vector<vector<int>>> findex) {
    map<int, vector<vector<int>>> invertedIndex;
    
    while(true) {
        vector<vector<int>> updated2dvec;
        map<int, vector<vector<int>>>::iterator itr = findex.begin();
        
        if(itr->second.size() == 0) {
            while(itr!=findex.end() && itr->second.size() == 0)
                    itr++;
            if (itr == findex.end())
                break;
        }
        
        int wordID = itr->second[0][0];
        itr->second[0][0] = itr->first;
        updated2dvec.push_back(itr->second[0]);
        itr->second.erase(itr->second.begin());
        itr++;
        
        for(itr; itr != findex.end(); itr++) {
            if(itr->second.size() == 0)
                continue;
            
            if(itr->second[0][0] == wordID) {
                itr->second[0][0] = itr->first;
                updated2dvec.push_back(itr->second[0]);
                itr->second.erase(itr->second.begin());
            }
        }
        
        invertedIndex.insert({wordID, updated2dvec});
        
    }
    cout << "inverted index generated" << endl;
    return invertedIndex;
}


map<int, vector<vector<int>>> genForwardIndex (ifstream& findex) {
    map<int, vector<vector<int>>> forwardIndex;

    while (!findex.eof()) {
        vector<vector<int>> vec2d;
        string str;
        getline(findex, str, '\n');

        //last entry in forward_index.txt is endl so when str is empty the loop breaks
        if (str == "") break;

        //first entry is always docID
        int docID = stoi(str);

        while (true) {
            //temp vector to store rows of 2d vector from forward index
            vector<int> temp;

            while (true) {
                getline(findex, str, '\n');
                
                if (str == "." || str =="_")
                    break;
                
                int x = stoi(str);
                temp.push_back(x);
            }

            //every 2d vector ends with _ so once it is reached must be pushed into vec2d
            if (str == "_")
                break;
            
            vec2d.push_back(temp);
        }

        //once vec2d finalized for a docID, it is inserted into findex
        forwardIndex.insert({docID, vec2d});

    }
    
    findex.close();
    cout << "forward index file read." << endl;
    
    return forwardIndex;
}

void writeInvertedIndex (ofstream& outputfile, ofstream& shortIndex, map<int, vector<vector<int>>> invertedIndex) {
    
    for(map<int, vector<vector<int>>>:: iterator itr = invertedIndex.begin(); itr != invertedIndex.end(); itr++) {
        bool insertion = true;
        outputfile << itr->first << endl;
        for (int j = 0; j < itr->second.size(); j++) {
            for (int k = 0; k < itr->second[j].size(); k++) {
                outputfile << itr->second[j][k] << endl;
            }
            //every entry of the vector is separated by a fullstop
            outputfile << "." << endl;
            
            int count = 1;
            if(itr->second[j][count] == -1) {
                count++;
                
                while(itr->second[j][count] == -1)
                    count++;
                
                if(insertion) {
                    shortIndex << itr->first << endl;
                    insertion = false;
                }
                
                shortIndex << itr->second[j][0] << endl << count-1 << endl;
            }
            
        }
        
        outputfile << "_" << endl;
        
        if(!insertion)
            shortIndex << "_" << endl;
        
    }
    
}

