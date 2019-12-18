#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	ifstream lex;
	ifstream forwardindex;
	ofstream outputfile;

	lex.open("lexicon.txt");
	forwardindex.open("forward_index.txt");
	outputfile.open("inverted_index.txt");

	if (lex.fail()) {
		cout << "Error: Cannot open lexicon file";
		system("pause");
		return 0;
	}

	if (forwardindex.fail()) {
		cout << "Error: Cannot open forward index file.";
		system("pause");
		return 0;
	}

	map<string, int> lexicon;
	map<int, vector<vector<int>>> findex;
	map<int, vector<vector<int>>> invertedIndex;
	
	while (true) {
		string str, word;

		getline(lex, word, '\n');

		if (word == ".") break;

		getline(lex, str, '\n');
		int wordID = stoi(str);

		lexicon.insert({word,wordID});
	}

	while (!forwardindex.eof()) {
		vector<vector<int>> vec2d;
		string str;
		getline(forwardindex, str, '\n');

		if (str == "") break;

		int docID = stoi(str);

		while (true) {
			vector<int> temp;
			while (true) {
				getline(forwardindex, str, '\n');
				if (str == "." || str =="_") break;
				int x = stoi(str);
				temp.push_back(x);
			}
			if (str == "_") break;
			vec2d.push_back(temp);
		}
		findex.insert({docID, vec2d});
	}
	
	map<int, vector<vector<int>>>::iterator top = findex.bgin();
	map<string, int>::iterator lexi;
	
	for (lexi = lexicon.begin(); lexi != lexicon.end(); lexi++) {
		vector<vector<int>> updated2dvec; 
		while (top != findex.end()) {
			for (int i = 0; i < top->second.size(); i++) {
				if (top->second[i][0] == lexi->second) {
					top->second[i][0] = top->first;
					updated2dvec.push_back(top->second[i]);
					top->second.erase(top->second.begin() + i);
					break;
				}
			}
			top++;
		}

		invertedIndex.insert({ lexi->second, updated2dvec});


		outputfile << lexi->second << endl;
		for (int j = 0; j < updated2dvec.size(); j++) {
			for (int k = 0; k < updated2dvec[j].size(); k++) {
				outputfile << updated2dvec[j][k] << ",";
			}
			outputfile << "." << endl;
		}
		outputfile << "." << endl;

		top = findex.begin();
	}

	findex.clear();
	outputfile.close();
	cout << "Inverted index generated." << endl;

	system("pause");
}