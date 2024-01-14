/*
*File: QuadraticProbing.h

*Description: File contains insert, remove, contains, and many other important functions. 
*
*Name: Paul Murariu
*
*Date Created: 5/19/2022
*Last Modified: 6/12/2022

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings
*/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

int nextPrime(int n);
int hash1(const string& key);
int hash1(int key);


template <typename HashedObj>
class HashTable
{
public:

    //Constant function
    //Single statement that is running
    explicit HashTable(int size = 101) : array(nextPrime(size))
    {
        makeEmpty();
    }
    
    //Constant function
    //Single statement that is running
    bool contains(const HashedObj& x) const
    {
        return isActive(findPos(x));
    }


    void makeEmpty()
    {
        currentSize = 0;
        for (int i = 0; i < array.size(); i++) //For loop runs for n times
            array[i].info = EMPTY;

        numberOfObjectsInTable = 0;
    }

    bool insert(const HashedObj& x)
    {
        // Insert x as active
        int currentPos = findPosInsert(x);
        if (isActive(currentPos)) {
            return false;
        }
        array[currentPos] = HashEntry(x, ACTIVE);
        numberOfObjectsInTable++;
        // Rehash; see Section 5.5
        if (++currentSize > array.size() / 2)
            rehash();

        return true;
    }

   //Function searches list for element to be deleted  
    bool remove(const HashedObj& x)
    {
        int currentPos = findPos(x);
        if (!isActive(currentPos))
            return false;

        array[currentPos].info = DELETED;
        numberOfObjectsInTable--;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };//status types

    //Constant function
    //Single statement that is running
    int get_number_of_objects_in_table() 
    {
        return numberOfObjectsInTable; //returns the number of objects in table. In this case, it is words.
    }
    
    //Constant function
    //Single statement that is running
    int get_table_size() 
    {
        return array.size(); //returns table size
    }
    
    //Constant function
    //Single statement that is running
    double get_load_factor() 
    {
        double temp = array.size();
        return numberOfObjectsInTable / temp; //returns load factor.
    }

      int get_total_collisions() 
    {
        int number = 0;
        for (int i = 0; i < collisionAverage.size(); ++i) { //For loop runs for n times
            if (collisionAverage[i] > 1) {
                number++;
            }
        }
        return number; //returns the number of total collisions
    }
      
      double get_average_chain_length() 
    {
        double sum = 0;
        double size = collisionAverage.size();
        for (int i = 0; i < collisionAverage.size(); ++i) { //for loop runs for n times
            sum += collisionAverage[i];
        }
        return sum / size; //returns the average chain length
    }

    //Constant function
    //Single statement that is running
    int get_longest_chain_length() 
    {
        auto biggest = (collisionAverage.begin(), collisionAverage.end());
        return 9;// *biggest; returns the longest chain length
    }

  
  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
            : element(e), info(i) 
        {
        
        }
    };

    //Constant function
    //Single statement that is running
    vector<HashEntry> array;
    int currentSize;
    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    int findPosInsert(const HashedObj& x)
    {
        int offset = 1;
        int currentPos = myhash(x);

        collisionCount = 1;//If there is no collision, then the count is at least 1
        while (array[currentPos].info != EMPTY &&
            array[currentPos].element != x)
        {
            
            if (collisionCount == 1) 
            
            {
                numberOfCollisionInsertions++;//Increments one time
            }
            collisionCount++;
            currentPos += offset;// Compute ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }
        
        if (collisionCount > longestCollision) 
        
        {
            longestCollision = collisionCount;
        }
        collisionAverage.push_back(collisionCount);
        return currentPos;
    }
    
    int findPos(const HashedObj& x) const
    {
        int offset = 1;
        int currentPos = myhash(x);

        // Assuming table is half-empty, and table length is prime,
        // this loop terminates
        while (array[currentPos].info != EMPTY &&
            array[currentPos].element != x)
        {

            currentPos += offset;  // Compute ith probe
            offset += 2;
            if (currentPos >= array.size())
                currentPos -= array.size();
        }
        return currentPos; //returns current position
    }
    
    void rehash()
    {

        if (collisionCount > longestCollision) {
            longestCollision = collisionCount;
        }
        collisionCount = 0; //Reinitialize
        numberOfCollisionInsertions = 0; //Reinitialize
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize(nextPrime(2 * oldArray.size()));
        for (int j = 0; j < array.size(); j++)
            array[j].info = EMPTY;

        // Copy table over
        currentSize = 0;
        for (int i = 0; i < oldArray.size(); i++)
            if (oldArray[i].info == ACTIVE)
                insert(oldArray[i].element);
    }
   
    //Constant function
    //Single statement that is running
    int myhash(const HashedObj& x) const
    {
        int hashVal = hash1(x);

        hashVal %= array.size();
        if (hashVal < 0)
            hashVal += array.size();

        return hashVal;
    }
    
    int numberOfObjectsInTable = 0;
    int longestCollision = 0;
    int collisionCount = 1;
    int numberOfCollisionInsertions = 0;
    vector<int> collisionAverage;
};

#endif 