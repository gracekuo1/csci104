#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        size_t w [5];
        for (int i = 0; i < 5; i ++){
            w[i] = 0;
        }

        size_t sectionTot = 0;
        int internalC = 0;
        int j = 4;
        int base = 1;

        for (int i = k.length()-1; i >= 0; i --){
            if (internalC == 6){
                w[j] = sectionTot;
                base = 1;
                j --;
                internalC = 0;
                sectionTot = 0;
            }
            sectionTot = sectionTot + letterDigitToNumber(k[i])*base;
            base = base * 36;
            internalC++;
        }
        if (internalC != 0){
            w[j] = sectionTot;
        }

        HASH_INDEX_T total = 0;
        for (int i = 0; i < 5; i ++){
            total = total + rValues[i] * w[i];
        }
        return total;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        HASH_INDEX_T converted;
        HASH_INDEX_T nletter = (int) letter;
        // Add code here or delete this helper function if you do not want it
        if (nletter >='a' && nletter <= 'z')
            converted = nletter - 'a';
        else if (nletter >= 'A' && nletter <= 'Z')
            converted = nletter - 'A';
        else if (nletter >='0' && nletter <= '9')
            converted = nletter - '0' + 26;
        
        return converted;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
