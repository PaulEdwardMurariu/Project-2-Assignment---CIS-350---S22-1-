/*
*File: QuadraticProbing.cpp

*Description: File contains isPrime, nextPrime, and hash1 functions. 
*
*Name: Paul Murariu
*
*Date Created: 5/19/2022
*Last Modified: 6/12/2022
*/

#include "QuadraticProbing.h"
#include <iostream>
using namespace std;

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2) //for loop runs for n times
        if (n % i == 0)
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime(int n)
{
    if (n <= 0)
        n = 3;

    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2) //for loop runs for n times
        ;

    return n;
}

/**
 * A hash routine for string objects.
 */
int hash1(const string& key)
{
    int hashVal = 0;

    for (unsigned int i = 0; i < key.length(); i++) //for loop runs for n times
        hashVal = 37 * hashVal + key[i];

    return hashVal;
}

/**
 * A hash routine for ints.
 */
 //Constant function
 //Single statement that is running
int hash1(int key)
{
    return key;
}