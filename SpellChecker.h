/*
*File: SpellChecker.h

*Description: File contains member functions which connect to other files.
*
*Name: Paul Murariu
*
*Date Created: 5/19/2022
*Last Modified: 6/12/2022
*/

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "QuadraticProbing.h"
using namespace std;

class SpellChecker {

    struct Word 
    
    { //stores word and line number elements. 
        string word;
        int lineNumber;
        Word(string w, int lineNum) 
        
        {
            word = w;
            lineNumber = lineNum;
        }
    };

private:
    HashTable<string> dictionary;
    //for input file operations.
    ifstream input; 
    //for output file operations.
    ofstream output; 
    vector<pair<Word, vector<string>>>incorrectWords;


public:
    SpellChecker();
    //member functions
    //stores the characters(words).
    vector<string> spellCheck(string word); 
    //function for reading file.
    void read_file(string inputFilename); 
    //function for dictionary statistics.
    void write_cerr(); 
    //function for word corrections.
    void write_corrections(); 
    //function for filling hash table with elements.
    void fill_hash_table(int numWords, string dictionaryFilename); 
    //produces word and line number from file.
    friend ostream& operator<<(ostream& out, Word& w) {
        out << w.word << "(" << w.lineNumber << ")";  
        return out;
    }
};