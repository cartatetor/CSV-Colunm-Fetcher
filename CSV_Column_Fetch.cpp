/*
CSV Column Fetcher
Copyright (C) 2026  Carter Hertter (cartatetor)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <map>
#include <bits/stdc++.h>

//returns
#define SUCSESS 1
#define LACKING_OPTION -1
#define UNKOWN_CMD -2
#define OPEN_FILE_ERROR -3
#define OUT_FILE_ERROR -4
#define PARSE_ERROR -5

using namespace std;

int main(int argc, char* argv[]) {

//Vars
    vector<string> lines;
    vector<string> albums;
    string line;

    map<string, string> ParsedArgs;
    char Delim = ',';
    string DelimS(1, Delim);
    string ArgList[] = {
        "of",           //Out File
        "if",           //In File
        "delim",        //Delimination
        "column",       //CSV column to pull data from
        //"q"             //Quietness leval (not implemnted)
    };
    string defualts[] = {
        "OutFile.txt",
        "",
        DelimS,
        "",
        //""
    };
    uint8_t ArgListLength = sizeof(ArgList)/sizeof(ArgList[0]);
//

//debuging help
    cout << "Arg Count: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "\tArg ";
        cout << i << ": " << argv[i] << "\n";
    }
//

    for (uint8_t i = 0; i < ArgListLength; i++) {
        ParsedArgs[ArgList[i]] = defualts[i];
    }

//Parse arguments
    for (uint8_t i = 1; i < argc; i++) {
        string ToParse = argv[i];
        string arg = "";
        string cmd = "";
        bool EqualFound = false;
        for (char CHAR : ToParse) {
            switch (EqualFound) {
                case true:
                    arg += CHAR;
                    break;
                case false:
                    if (CHAR == '=') {
                        EqualFound = true;
                        break;
                    }
                    cmd += CHAR;
            }
        }
        cout << "Command: \"" << cmd << "\"\nWith argument: \"" << arg << "\"\n";

        for (string s: ArgList) {
            if (cmd == s) {
                ParsedArgs[cmd] = arg;
            }
        }
    }
    int ColNum = stoi(ParsedArgs["column"]);
//==========

    //Checking for lacking arguemnt errors
    for (uint8_t i = 0; i < ArgListLength; i++) {
        if(ParsedArgs[ArgList[i]] == "" || ParsedArgs[ArgList[i]] == "\n") {
            cerr << "lacking " << ArgList[i] << " option.\n";
            return LACKING_OPTION;
        }
    }

//get file lines 
    ifstream file(ParsedArgs["if"]);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << ParsedArgs["if"] << endl;
        return OPEN_FILE_ERROR;
    }

    while (getline(file, line)) {
        lines.push_back(move(line));
    }

    file.close();
//==========

//get albums
    for (string& song : lines) {

        uint8_t DelimCounter = 0;
        uint8_t check = ColNum - 1;
        string currentAlbum = "";

        for (char c : song) {
            if ((ParsedArgs["delim"])[0] == c) {
                DelimCounter ++;
                continue;
            }
            
            if (DelimCounter == check && c != '\"') {
                currentAlbum += c;
            }
            else if (DelimCounter > ColNum) {
                break;
            }
        }

        if (!currentAlbum.empty()) {
            bool found = false;
            currentAlbum += '\n';
            for (string s : albums) {
                if (currentAlbum == s) {
                    found = true;
                }
            }
            if (!found) {
                albums.push_back(currentAlbum);
            }
        }
        else {
            cerr << "Failed to Parse: " << song << "\nGot :" << currentAlbum << endl;
            return PARSE_ERROR;
        }
    }
//==========

//put albums in file
    ofstream MyFile(ParsedArgs["of"]);

    if (!MyFile.is_open()) {
        cerr << "Unable to create or open output file\n";
        return OUT_FILE_ERROR;
    }

    for (const string& s : albums) {
        MyFile << s;
    }

    MyFile.close();
    cout << "Wrote albums to \"" << ParsedArgs["of"] << "\"\n";
//==========
    return SUCSESS;
}