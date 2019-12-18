#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
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
			break;
		}

		vector<string> temp;
		vector<vector<int>> vec2d;
		int base, length, plain = 0;
		string str, word;

		while (!file.eof()) {
			getline(file, str, '\n');
			temp.push_back(str);
		}

		for (int i = 0; i < 4; i++) {
			str = temp[i];
			const char *start = str.c_str();
			const char *p = start;
			base = 0; length = 0;
			
			while (true) {
				while (*start == '"' || *start == ',' || *start == ' ' || *start == '-' || *start == ':' || *start == ';' ||
					*start == '!' || *start == '?' || *start == ')' || *start == '(' || *start == '_' || *start == '/' ||
					*start == '.' || *start == '�' || *start == '�' || *start == '�' || *start == '�' || *start == '�'
					|| *start == '[' || *start == ']' || *start == '�' || *start == '�') { start++; base++; }

				p = start;
				while (*p != '"' && *p != ',' && *p != ' ' && *p != '-'  && *p != ':'  && *p != ';'   && *p != '.' && *p != '!'
					&& *p != '?'  && *p != '('  && *p != ')'  && *p != '_'  && *p != '/' && *p != '�'  && *p != '�'  &&
					*p != '�' && *p != '�' && *p != '�' && *p != '[' && *p != ']' && *p != '�' && *p != '�' &&
					*p != '\0') { p++; length++; }

				word = str.substr(base, length);
				transform(word.begin(), word.end(), word.begin(), ::tolower);

				int wordID = 0;
				map<string, int>::iterator itr;
				itr = lexicon.find(word);

				if (itr != lexicon.end())
					wordID = itr->second;
				else {
					wordID = lastWordID + 1;
					lexicon.insert({ word,wordID });
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

				if (i == 0 || i == 1 || i == 2) {
					vec2d[idchecker].push_back(fancy);
				}
				else {
					vec2d[idchecker].push_back(plain);
					plain++;
				}
				
				if (*p == '\0') break;

				start = p + 1;
				p = start;
				base += (length + 1);
				length = 0;
			}
		}

		outputfile << docID << endl;
		for (int i = 0; i < vec2d.size(); i++) {
			for (int j = 0; j < vec2d[i].size(); j++) {
				outputfile << vec2d[i][j] << endl;
			}
			outputfile << "." << endl;
		}
		outputfile << "_" <<endl;

		docID++;
		file.close();
	}

	outputfile.close();
	cout << "Forward index file finalized." << endl;
	outputlex << "."; 
	outputlex.close();
	cout << "Lexicon file finalized." << endl;

	system("pause");
}