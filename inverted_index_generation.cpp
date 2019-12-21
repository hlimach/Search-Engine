#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	ifstream lex, forwardindex;
	ofstream outputfile;

	lex.open("lexicon.txt");
	forwardindex.open("forward_index.txt");
	outputfile.open("inverted_index.txt");

	if (lex.fail() || forwardindex.fail()) {
        	(lex.fail()) ? cout << "Error: Cannot open lexicon file" << endl : cout << "Error: Cannot open forward index file." << endl;
        	return -1;
    	}

	map<string, int> lexicon;
	map<int, map<int,vector<int>>> findex, invertedIndex;
	
	while (true) {
		string str, word;

		getline(lex, word, '\n');

		if (word == ".") break;

		getline(lex, str, '\n');
		
		lexicon.insert({word,stoi(str)});
	}

	while (!forwardindex.eof()) {
		map<int,vector<int>> hits;
		string str;
		getline(forwardindex, str, '\n');

		if (str == "") break;

		int docID = stoi(str);

		while (true) {
			getline(forwardindex, str, '\n');
            		if (str == "_") break;
            		int wordID = stoi(str);
            		vector<int> temp;
            
            		while (true) {
                		getline(forwardindex, str, '\n');
                		if (str == "." || str == "_") break;
                		temp.push_back(stoi(str));
            		}
            
            		hits.insert({wordID,temp});
        	}
        
        	findex.insert({docID, hits});
	}
	
	map<int, vector<vector<int>>>::iterator top = findex.begin();
	map<string, int>::iterator lexi;
	
	for (lexi = lexicon.begin(); lexi != lexicon.end(); lexi++) {
		map<int,vector<int>> updatedhits;
        
        	while (top != findex.end()) {

            		if (top->second.find(lexi->second) != top->second.end())
                		updatedhits.insert({top->first, top->second.find(lexi->second)->second});
            
            		top++;
        	}

        	invertedIndex.insert({ lexi->second, updatedhits});

        	outputfile << lexi->second << endl;
        	for(map<int,vector<int>>::iterator itr = updatedhits.begin(); itr != updatedhits.end(); itr++) {
            		outputfile << itr->first << endl;
            
            		for(int i = 0; i < itr->second.size(); i++)
                		outputfile << itr->second[i] << endl;
            
             		outputfile << "." << endl;
        	}
        
        	outputfile << "_" << endl;
		top = findex.begin();
	}

	findex.clear();
	outputfile.close();
	cout << "Inverted index generated." << endl;

	return 0;
}
