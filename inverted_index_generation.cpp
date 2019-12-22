#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
	ifstream lex, forwardindex;
	ofstream mainIndex, shortIndex;

	lex.open("lexicon.txt");
	forwardindex.open("forward_index.txt");
	mainIndex.open("inverted_index.txt");
    	shortIndex.open("small_inverted_index.txt");

	if (lex.fail() || forwardindex.fail()) {
        	(lex.fail()) ? cout << "Error: Cannot open lexicon file" << endl : cout << "Error: Cannot open forward index file." << endl;
        	return -1;
    	}
	
	auto start = high_resolution_clock::now();

	map<string, int> lexicon;
	map<int, map<int,vector<int>>> findex;
	
	while (true) {
		string str, word;
		getline(lex, word, '\n');

		if (word == ".") 
			break;

		getline(lex, str, '\n');
		lexicon.insert({word,stoi(str)});
	}
	
	lex.close();
    	cout << "lexicon read" << endl;

	while (!forwardindex.eof()) {
		map<int,vector<int>> hits;
		string str;
		getline(forwardindex, str, '\n');

		if (str == "") 
			break;

		int docID = stoi(str);

		while (true) {
			getline(forwardindex, str, '\n');
			
            		if (str == "_") 
				break;
			
            		int wordID = stoi(str);
            		vector<int> temp;
            
            		while (true) {
                		getline(forwardindex, str, '\n');
				
                		if (str == "." || str == "_") 
					break;
				
                		temp.push_back(stoi(str));
            		}
            
            		hits.insert({wordID,temp});
        	}
        
        	findex.insert({docID, hits});
	}
	
	forwardindex.close();
    	cout << "forward index read" << endl;
	
	map<int, vector<vector<int>>>::iterator top = findex.begin();
	map<string, int>::iterator lexi;
	
	for (lexi = lexicon.begin(); lexi != lexicon.end(); lexi++) {
		map<int,vector<int>> updatedhits;
		map<int,int> temp;
        
        	while (top != findex.end()) {
            		map<int,vector<int>>::iterator target = top->second.find(lexi->second);
            		if (target != top->second.end()) {
                		updatedhits.insert({top->first, target->second});
                		top->second.erase(target);
            		}
            		top++;
        	}

        	int count = 0;
        	mainIndex << lexi->second << endl;
        	bool insertion = true;

        	for(map<int,vector<int>>::iterator itr = updatedhits.begin(); itr != updatedhits.end(); itr++) {
            		itr != updatedhits.end(); itr++) {
            		mainIndex << itr->first << endl;
            
            		for(int i = 0; i < itr->second.size(); i++)
                		mainIndex << itr->second[i] << endl;
				
			if(itr->second.size() != 0) {
                		count = 0;
                		if(itr->second[count] == -1) {
                    			count++;
                
                    			while(itr->second[count] == -1)
                        			count++;
                    
                    			if(insertion) {
                        			shortIndex << lexi->second << endl;
                        			insertion = false;
                   			}
                    
                    			shortIndex << itr->first << endl << count << endl;
                		}
                
            		}
            
             		mainIndex << "." << endl;
        	}
        
        	mainIndex << "_" << endl;
        
        	if(!insertion)
            		shortIndex << "_" << endl;
			
		top = findex.begin();
	}
	
	auto stop = high_resolution_clock::now();
    	auto duration = duration_cast<seconds>(stop - start);
    
    	cout << "Time taken: " << (duration.count()) << " seconds" << endl;
	
	findex.clear();
	mainIndex.close();
    	shortIndex.close();
		
	cout << "Inverted index generated." << endl;
	cout << "Small Inverted index generated." << endl;
	return 0;
}
