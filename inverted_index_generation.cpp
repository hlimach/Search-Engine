#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

map<int, vector<vector<int>>> genForwardIndex (ifstream& findex);
void writeInvertedIndex (ofstream& outputfile, map<int, vector<vector<int>>> invertedIndex); 
map<int, vector<vector<int>>> genInvertedIndex (map<int, vector<vector<int>>> findex);

int main() {
	ifstream lex, fi1, fi2, fi3, fi4;
    	ofstream ii1, ii2, ii3, ii4;

	lex.open("lexicon.txt");
    	fi1.open("f1_index.txt");
    	fi2.open("f2_index.txt");
    	fi3.open("f3_index.txt");
    	fi4.open("f4_index.txt");
    	ii1.open("inverted_index1.txt");
    	ii2.open("inverted_index2.txt");
    	ii3.open("inverted_index3.txt");
    	ii4.open("inverted_index4.txt");

	if (lex.fail() || fi1.fail() || fi2.fail() || fi3.fail() || fi4.fail()) {
        	(lex.fail()) ? cout << "Error: Cannot open lexicon file" << endl : cout << "Error: Cannot open forward index files." << endl;
        	return -1;
    	}
	
	auto start = high_resolution_clock::now();

	map<string, int> lexicon;
    	map<int, vector<vector<int>>> i1index;
    	map<int, vector<vector<int>>> i2index;
    	map<int, vector<vector<int>>> i3index;
    	map<int, vector<vector<int>>> i4index;
    	map<int, vector<vector<int>>> f1index = genForwardIndex(fi1);
    	map<int, vector<vector<int>>> f2index = genForwardIndex(fi2);
    	map<int, vector<vector<int>>> f3index = genForwardIndex(fi3);
    	map<int, vector<vector<int>>> f4index = genForwardIndex(fi4);
	
	while (true) {
		string str, word;
		getline(lex, word, '\n');

		if (word == ".") 
			break;

		getline(lex, str, '\n');
		lexicon.insert({word,stoi(str)});
	}
	lex.close();
    	cout << "lexicon generated." << endl;

    	i4index = genInvertedIndex(f4index);
    	i3index = genInvertedIndex(f3index);
    	i2index = genInvertedIndex(f2index);
    	i1index = genInvertedIndex(f1index);	
	
	writeInvertedIndex(ii1, i1index);
    	writeInvertedIndex(ii2, i2index);
    	writeInvertedIndex(ii3, i3index);
    	writeInvertedIndex(ii4, i4index);
	
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
                if (str == "." || str =="_") break;
                int x = stoi(str);
                temp.push_back(x);
            }

            //every 2d vector ends with _ so once it is reached must be pushed into vec2d
            if (str == "_") break;
            vec2d.push_back(temp);
        }

        //once vec2d finalized for a docID, it is inserted into findex
        forwardIndex.insert({docID, vec2d});

    }
    
    findex.close();
    cout << "forward index file read." << endl;
    
    return forwardIndex;
}

void writeInvertedIndex (ofstream& outputfile, map<int, vector<vector<int>>> invertedIndex) {
    for(map<int, vector<vector<int>>>:: iterator itr = invertedIndex.begin(); itr != invertedIndex.end(); itr++) {
        outputfile << itr->first << endl;
        for (int j = 0; j < itr->second.size(); j++) {
            for (int k = 0; k < itr->second[j].size(); k++) {
                outputfile << itr->second[j][k] << endl;
            }
            //every entry of the vector is separated by a fullstop
            outputfile << "." << endl;
        }
        outputfile << "_" << endl;
    }
}
