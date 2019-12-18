#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

int main() {
	ifstream file;
	ofstream workbook;

	int docID = 1;
	string path = ".csv";
	string path2 = ".txt";
	string filename;
	string p = "E:\\dataset2\\";

	while (docID < 16) {
		filename = to_string(docID) + path;
		file.open(filename);
		filename = p + to_string(docID) + path2;
		workbook.open(filename);

		if (workbook.fail()) {
			cout << "Error: Cannot open workbook";
			return -1;
		}

		if (file.fail()) {
			cout << "Error: Cannot open file";
			return -1;
		}

		cout << docID << endl;
		vector<string> temp;
		int comma_count = 0, base = 0, length = 0;
		string str, word;

		getline(file, str);
		const char *mystart = str.c_str();
		bool instring{ false };
		for (const char* p = mystart; *p; p++) {
			if (*p == '"') {
				instring = !instring;
				mystart++;
			}
			else if (*p == ',' && !instring) {
				if (comma_count == 2 || comma_count == 3 || comma_count == 4) {
					temp.push_back(str.substr(base, length));
				}
				mystart = p + 1;
				base += length + 1;
				length = 0;
				comma_count++;
			}
			else if (comma_count == 9) {
				while (*p != '\0') { p++; length++; }
				temp.push_back(str.substr(base, length - 1));
				break;
			}
			else length++;
		}
        
		for (int i = 0; i < 4; i++) {
			str = temp[i];
			const char *start = str.c_str();
			const char *p = start;
			base = 0; length = 0;

			while (true) {
				while (*start == '"' || *start == ',' || *start == ' ' || *start == '-' || *start == ':' || *start == ';' ||
										*start == '!' || *start == '?' || *start == ')' || *start == '(' || *start == '_' || *start == '/' || 
										*start == '.' || *start == '€' || *start == 'â' || *start == '™' || *start == '˜' || *start == 'œ'
										|| *start == '[' || *start == ']' || *start == '¦' || *start == '”') { start++; base++; }
						p = start;
				while (*p != '"' && *p != ',' && *p != ' ' && *p != '-'  && *p != ':'  && *p != ';'   && *p != '.' && *p != '!'
										&& *p != '?'  && *p != '('  && *p != ')'  && *p != '_'  && *p != '/' && *p != '€'  && *p != 'â'  &&
										*p != '™' && *p != '˜' && *p != 'œ' && *p != '[' && *p != ']' && *p != '¦' && *p != '”' &&
										*p != '\0') { p++; length++; }
	
				word = str.substr(base, length);
				transform(word.begin(), word.end(), word.begin(), ::tolower);
				workbook << word << " ";

				if (*p == '\0') break;

				start = p + 1;
				p = start;
				base += (length + 1);
				length = 0;

			}

			workbook << endl;
			cout << "c" << endl;
		}
		workbook.close();
		docID++;
		file.close();
		cout << "d" << endl;

	}
	system("pause");
}
