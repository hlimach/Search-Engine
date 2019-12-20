#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>


using namespace std;

int main() {
	
	ifstream file;
	ofstream outputfile;
	ofstream outputlex;
	
	outputfile.open("forward_index.txt");
	outputlex.open("lexicon.txt");
	
	int docID = 1;
	string path = ".txt";
	string filename;
	map<string, int> lexicon;
	int fancy = -1;
	int lastWordID = 0;
	
	while (docID < 16) {
		
		filename = to_string(docID) + path;
		file.open(filename);
		
		if (file.fail()) {
			cout << "Error: Cannot open file";
			return -1;
		}
		
		outputfile << docID << endl;
		cout << docID << endl; //temp
		
		vector<string> temp;
		vector<vector<int>> vec2d;
		int plain = 0, count = 0;
		string str, word;
		
		while (getline(file, str, '\n')) {
			
			stringstream str1(str);
			while (getline(str1, word, ' ')) {
				
				int wordID = 0;
				map<string, int>::iterator itr;
				itr = lexicon.find(word);
				
				if (itr != lexicon.end())
					wordID = itr->second;
				else {
					wordID = lastWordID + 1;
					lexicon.insert({ word, wordID });
					
					outputlex << word << endl << wordID << endl;
					lastWordID++;
				}
				
				int idchecker = 0;
				bool idfound = false;
				
				while (idchecker != vec2d.size()) {
					if (vec2d[idchecker][0] != wordID)
						idchecker++;
					else {
						idfound = true;
						break;
					}
				}
				
				if (idfound == false) {
					vec2d.push_back(vector<int>());
					vec2d[idchecker].push_back(wordID);
				}
				
				if (count == 0 || count == 1 || count == 2) {
					vec2d[idchecker].push_back(fancy);
				}
				
				else {
					vec2d[idchecker].push_back(plain);
					plain++;
				}
			}
			count++;
			
		}
		outputfile << docID << endl;
		for (int i = 0; i < vec2d.size(); i++) {
			for (int j = 0; j < vec2d[i].size(); j++) {
				outputfile << vec2d[i][j] << endl;
			}
			outputfile << "." << endl;
		}
		outputfile << "_" << endl;

		docID++;
		file.close();
	}
	outputfile.close();
	cout << "Forward index file finalized." << endl;
	outputlex << ".";
	outputlex.close();
	cout << "Lexicon file finalized." << endl;
	return 0;
}
