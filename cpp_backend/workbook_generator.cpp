#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {

    //creating a csv file reader
    ifstream file;

    //creating a file writer
    ofstream fileout;

    //opening file using reader
    file.open("articles1.csv");

    //checking whether file is opened sucessfully
    if (file.fail()) {
        cout << "The file that is being opened does not exist." << endl;
        system("pause");
        return -1;
    }

    //creating a string to read file into
    string str;
    vector<string> fileread;

    while (!file.eof()) {
        getline(file, str, '\n');
        fileread.push_back(str);
    }

    int x = 0;
    string path = "E:\\workbooks\\";
    string path2 = ".csv";
    string final;

    while (x != fileread.size() - 1) {
        final = path + to_string(x) + path2;
        fileout.open(final);
        fileout << fileread[x];
        fileout.close();
        x++;
    }

    system("pause");
}
