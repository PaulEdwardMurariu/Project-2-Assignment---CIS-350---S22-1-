/*
*File: TestQuadraticProbing.cpp

*Description: File contains a simple main function.
*
*Name: Paul Murariu
*
*Date Created: 5/19/2022
*Last Modified: 6/12/2022
*/

#include <iostream>
#include <string>
#include "QuadraticProbing.h"
#include "SpellChecker.h"
#include <stdlib.h>
#include <filesystem>
#include <fstream>
using namespace std;


// Simple main function
int main(int argc, char* argv[])
{
    int numberOfWords = atoi(argv[1]);
    //int numberOfWords = 638,670;
    string dictionaryFileName =  argv[2];
    //string dictionaryFileName = "C:\\Users\\17347\\OneDrive\\Desktop\\Prog2CIS350\\x64\\Debug\\hugedict.txt";
    string textFileName = argv[3];
    //string textFileName = "C:\\Users\\17347\\OneDrive\\Desktop\\Prog2CIS350\\x64\\Debug\\test.txt";


    //Constant function
    //Single statement that is running
    SpellChecker sc;
    sc.fill_hash_table(numberOfWords, dictionaryFileName);
    sc.read_file(textFileName);
    sc.write_cerr();
    sc.write_corrections();

    ofstream myfile;
    myfile.open("hugedict test 1_jabber.txt"); //opens file.
    myfile << "Huge Dictionary Spell Check Results For Test1_jabber.\n"; //produces text file.
    myfile.close(); //closes file.

    return 0;
}

//HashTable<int> H;
  //const int NUMS = 4000;
  //const int GAP = 37;
  //int i;
  //cout << "Checking... (no more output means success)" << endl;
  //for (i = GAP; i != 0; i = (i + GAP) % NUMS) //for loop runs for n times
  //    H.insert(i);
  //
  //for (i = 1; i < NUMS; i += 2)
  //    H.remove(i);

  //for (i = 2; i < NUMS; i += 2)
  //{
  //    if (!H.contains(i))
  //        cout << "Contains fails " << i << endl;
  //}
  //for (i = 1; i < NUMS; i += 2)
  //{
  //    if (H.contains(i))
  //        cout << "OOPS!!! " << i << endl;
  //}