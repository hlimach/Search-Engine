#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

int main() {
	//creating file readers and writers
	ifstream file;
	ofstream workbook;

	//declaring variables
	int docID = 1;
	string path = ".csv";
	string path2 = ".txt";
	string filename;
	string p = "E:\\dataset2\\";

	//loop for first 15 docs
	while (docID < 16) {
		filename = to_string(docID) + path;
		file.open(filename);
		filename = p + to_string(docID) + path2;
		workbook.open(filename);

		//checking whether workbook is opened sucessfully
		if (workbook.fail()) {
			cout << "Error: Cannot open workbook";
			return -1;
		}

		//checking whether file is opened sucessfully
		if (file.fail()) {
			cout << "Error: Cannot open file";
			return -1;
		}

		cout << docID << endl;
		//variables
		vector<string> temp;
		int comma_count = 0, base = 0, length = 0;
		string str, word;

		//tokenizing document
		getline(file, str); //extracting first line
		const char *mystart = str.c_str();    //pointer to beginning of line
		bool instring{ false }; //check whether comma in text
		for (const char* p = mystart; *p; p++) {   //iterate through the line

			 //toggle flag if we're btw double quotes
			if (*p == '"') {
				instring = !instring;
				mystart++;
			}

			//if comma OUTSIDE double quotes
			else if (*p == ',' && !instring) {
				//required fields of author title and publishers
				if (comma_count == 2 || comma_count == 3 || comma_count == 4) {
					temp.push_back(str.substr(base, length));
				}
				//and start parsing next one
				mystart = p + 1;
				base += length + 1;
				length = 0;
				comma_count++;
			}

			//if it is last content field
			else if (comma_count == 9) {
				//iterate pointer to end of content and push it into temp vector
				while (*p != '\0') { p++; length++; }
				temp.push_back(str.substr(base, length - 1));
				break;
			}

			//to increment till where the string must be broken
			else length++;
		}

		//for parsing sentences in temp vec (size always 4 because only 4 fields extracted from each doc)
		for (int i = 0; i < 4; i++) {
			//get string at ith pos of them vec and start breaking down words
			str = temp[i];
			const char *start = str.c_str();
			const char *p = start;
			base = 0; length = 0;

			while (true) {
				/*
				start points to the starting position of text where the exceptions do not exist.
				p iterates through the text until it finds one of the exception.
				the index of start and the length of text is tracked using base and length variables.
				*/
				while (*start == '"' || *start == ',' || *start == ' ' || *start == '-' || *start == ':' || *start == ';' ||
										*start == '!' || *start == '?' || *start == ')' || *start == '(' || *start == '_' || *start == '/' || 
										*start == '.' || *start == '€' || *start == 'â' || *start == '™' || *start == '˜' || *start == 'œ'
										|| *start == '[' || *start == ']' || *start == '¦' || *start == '”') { start++; base++; }
						p = start;
				while (*p != '"' && *p != ',' && *p != ' ' && *p != '-'  && *p != ':'  && *p != ';'   && *p != '.' && *p != '!'
										&& *p != '?'  && *p != '('  && *p != ')'  && *p != '_'  && *p != '/' && *p != '€'  && *p != 'â'  &&
										*p != '™' && *p != '˜' && *p != 'œ' && *p != '[' && *p != ']' && *p != '¦' && *p != '”' &&
										*p != '\0') { p++; length++; }
	
				//once p hits an exception the string is broken into substring and passed into a temporary word variable
				word = str.substr(base, length);
				//transforms word into lowercase to eliminate multiple storage of same word
				transform(word.begin(), word.end(), word.begin(), ::tolower);
				workbook << word << " ";

				//once p reaches end of line then we break out of this loop*/
				if (*p == '\0') break;

				//else we keep breaking the words in the line.
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
