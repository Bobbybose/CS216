/*
 * Course: CS216-00x
 * Project: Lab 10 Bonus Part
 * Purpose: testing two member functions, named magicString::wordFormat()
 *          and magicString::removeExtraSpace()
 * Author: Yi Pike
 * ### Please Do Not Change This File. ###
 */
#include <iostream>
#include "magicString.h"

using namespace std;

int main()
{
    string to_test = "\t  hi,  \t   yI\tl\t    pIKe :)   ";
    magicString magic(to_test);

    cout << to_test << endl;
    magic.removeExtraSpace();
    cout << magic.getMagicString() << endl;
    cout << magic.wordFormat() << endl;

    return 0;
}


