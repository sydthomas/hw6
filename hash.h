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
        // array to store w values 
        HASH_INDEX_T w[5] = {0};

        size_t index = k.length();

        size_t wIndex = 4;

///power function substitute 
        // ui base = 36;
        // size_t exp = 6;



        while(index>0)
        {
            HASH_INDEX_T tempW = 0;
            size_t power = 0;
            for(int i = 0; i < 6 && index>0; ++i, --index)
            {
                tempW += letterDigitToNumber(k[index-1])*pow(36,power++); 
            }
            //std::cout << "W index = " << wIndex << std::endl;
            w[wIndex--] = tempW;
        }



        HASH_INDEX_T hashVal = 0;
        for(size_t i = 0; i < 5; ++i)
        {
            hashVal += rValues[i] * w[i];
            std::cout << "W[" << i << "] " << w[i] << std::endl;
        }    



        return hashVal;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if(letter >= '0' && letter <= '9')
        {
            return letter - 22;
        }
        else{
            return std::tolower(letter) -'a'; 
        }

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
