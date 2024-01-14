/*
*File: SpellChecker.cpp

*Description: File contains multiple SpellChecker functions.
*
*Name: Paul Murariu
*
*Date Created: 5/19/2022
*Last Modified: 6/12/2022
*/

#include <iostream>
#include <stdio.h>
#include "SpellChecker.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//Default Constructor
SpellChecker::SpellChecker() {}

//Constant function
//Single statement that is running
void SpellChecker::write_cerr()
{
    cerr << "Number of words: " << dictionary.get_number_of_objects_in_table()
        << ", Table Size: " << dictionary.get_table_size() << ", Load Factor: " << setprecision(6) << dictionary.get_load_factor() << endl;
    cerr << "Collisions: " << dictionary.get_total_collisions()
        << ", Average Chain Length: " << setprecision(6) << dictionary.get_average_chain_length()
        << ", Longest Chain Length: " << dictionary.get_longest_chain_length() << endl;
}
//setprecision() can get the desired precise value of a floating-point or a double value by providing the exact number of decimal places.
//dictionary.get_number_of_objects_in_table() returns number of words of inputted text files.
//dictionary.get_array_size() returns size of the table of contents.
//dictionary.get_load_factor() returns the load factor. Load factor is a measurement of how full the hash table is 
//allowed to get before its capacity is automatically increased.
//dictionary.get_total_collisions() returns the total amount of collisions from running the text files.
//dictionary.get_average_chain_length() returns the average chain length.
//dictionary.get_longest_chain_length() returns the longest chain length.

vector<string> SpellChecker::spellCheck(string word) 

{
    vector<string> permutations;
    
    for (int i = 0; i < word.length(); ++i) 
    {
        for (char j = 'a'; j != 'z'; ++j) 
        {
            string temp = word;
            temp[i] = j;
            if (dictionary.contains(temp)) 
            {
                permutations.push_back(temp);
            }
        }
    }
    
    
    for (int i = 1; i < word.length(); ++i) 
    {
        string temp = word;
        swap(temp[i - 1], temp[i]);
        if (dictionary.contains(temp)) 
        {
            permutations.push_back(temp);
        }
    }
    
    for (int i = 0; i < word.length(); ++i) 
    
    {   
        string temp = word.substr(0, i) + word.substr(i + 1);
        if (dictionary.contains(temp)) 
        {
            permutations.push_back(temp);
        }
    }
    
    
    for (int i = 0; i < word.length() + 1; ++i) 
    {
        for (char j = 'a'; j != 'z'; ++j) 
        {
            string temp = word;
            temp = word.substr(0, i) + j + word.substr(i);
            if (dictionary.contains(temp)) 
            {
                permutations.push_back(temp);
            }
        }
    }
    
    return permutations;
}

void SpellChecker::read_file(string inputFilename) 
{
    int count = 0;
    string line;
    //opens file
    input.open(inputFilename);
    //memory management
    stringstream buffer;
    string tempWord;
    //getline accepting and reading single and multiple line strings from the input stream. 
    while (getline(input, line)) 
    
    {
        //removes the punctuations and other control characters
        for (int i = 0; i < line.length(); i++)//nested for loop runs for n^3 times 
        {                                     
            if (!isalpha(line[i]))
                line[i] = ' ';
        }
       
        count++;
        stringstream buffer(line);
        while (buffer >> tempWord) 
        
        {
            if (!dictionary.contains(tempWord)) {//Check if present
                string tempWordLowerCase = tempWord;
                for (int i = 0; i < tempWord.length(); ++i) 
                
                {   //Convert to lowercase
                    tempWordLowerCase[i] = tolower(tempWordLowerCase[i]);
                }
                //if dictionary contains a lowercase word, the spellCheck will produce suggested corrections.
                if (!dictionary.contains(tempWordLowerCase)) {//Check if present once again
                    //push_back() inserts new element at the end of vector and increases size of vector by one.
                    incorrectWords.push_back(make_pair(Word(tempWord, count), spellCheck(tempWord)));
                }
            }
        }
    }
    //closes file.
    input.close(); 
}


void SpellChecker::write_corrections() {
    for (int i = 0; i < incorrectWords.size(); ++i) { //nested for loop runs for n^2 times.
        //produces colon symbol for each line of word.
        cout << incorrectWords[i].first << ": "; 
        //produces the number of word lines.
        if (incorrectWords[i].second.size() > 0) 
        
        {
            //produces suggested corrections for words that are not found in dictionary.
            for (int j = 0; j < incorrectWords[i].second.size(); ++j) { 
                cout << incorrectWords[i].second[j] << " "; 
            }
        }
        cout << endl;
    }
    cout << endl;
}


void SpellChecker::fill_hash_table(int numWords, string inputFilename) {
    try //defines a block of code to be tested for errors while it is being executed.

    {
        //creates a dictionary hash table
        dictionary = HashTable<string>(numWords * 2); 
        string line;
        //opens file
        input.open(inputFilename); 
        while (input >> line) { //while loop runs for n times
           //inserts item into hash table
            dictionary.insert(line); 
        }
        //closes file
        input.close(); 
    }
    catch(...) // defines a block of code to be executed, if an error occurs in the try block.
    { }

}