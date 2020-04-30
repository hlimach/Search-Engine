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

    while (docID < 50001) {
        file.open(to_string(docID) + ".csv");
        workbook.open(to_string(docID) + ".txt");

        if (workbook.fail() || file.fail()) {
            (file.fail()) ? cout << "Error: Cannot open reading file " : cout << "Error: Cannot open writing file ";
            return -1;
        }

        cout << docID << endl;
        vector<string> temp;
        int ccount = 0, base = 0, length = 0;
        string str, word;

        getline(file, str);
        const char *mystart = str.c_str();
        bool instring{ false };
        for (const char* p = mystart; *p; p++) {
            if (*p == '"') {
                instring = !instring;
                length++;
            }
            else if (*p == ',' && !instring) {
                if (ccount == 2 || ccount == 3 || ccount == 4 || ccount == 5 || ccount == 6 || ccount == 7) {
                    temp.push_back(str.substr(base, length));
                }
                mystart = p + 1;
                base += length + 1;
                length = 0;
                ccount++;
            }
            else if (ccount == 9) {
                while (*p != '\0') { p++; length++; }
                temp.push_back(str.substr(base, length - 1));
                break;
            }
            else length++;
        }

        for (int i = 0; i < 7; i++) {

            if (i == 3 || i == 4 || i == 5) {
                workbook << temp[i] << " " << endl;
                continue;
            }

            str = temp[i];
            const char *start = str.c_str();
            const char *p = start;
            base = 0; length = 0;

            while (true) {
                while (*start == '"' || *start == ',' || *start == ' ' || *start == '-' || *start == ':' || *start == ';' ||
                    *start == '!' || *start == '?' || *start == ')' || *start == '(' || *start == '_' || *start == '/' ||
                    *start == '.' || *start == '€' || *start == 'â' || *start == '™' || *start == '˜' || *start == 'œ'
                    || *start == '[' || *start == ']' || *start == '¦' || *start == '”') {
                    start++; base++;
                }

                p = start;

                while (*p != '"' && *p != ',' && *p != ' ' && *p != '-'  && *p != ':'  && *p != ';'   && *p != '.' && *p != '!'
                    && *p != '?'  && *p != '('  && *p != ')'  && *p != '_'  && *p != '/' && *p != '€'  && *p != 'â'  &&
                    *p != '™' && *p != '˜' && *p != 'œ' && *p != '[' && *p != ']' && *p != '¦' && *p != '”' &&
                    *p != '\0') {
                    p++; length++;
                }

                word = str.substr(base, length);
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                workbook << word << " ";

                if (*p == '\0')
                    break;

                start = p + 1;
                p = start;
                base += (length + 1);
                length = 0;
            }
            workbook << endl;
            cout << "." << endl;
        }
        workbook.close();
        docID++;
        file.close();
        cout << "done" << endl;
    }
    return 0;
}
