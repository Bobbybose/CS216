/*
* Name: Bobby Bose
* File: main.cpp
* Course: CS216-007
* Project: Project 3
*  Purpose: main function for the project 
*/

#include "WordLadder.h"     
#include <iostream>
#include <string>
#include <vector>
#include <stack>        //To flip ladder order
#include <fstream>
#include <algorithm>    //For transform function
#include <map>

using namespace std;

int main(int argc, char* argv[]){
    
    //Check whether the number of command line arguments is exactly one
    if(argc != 2){
        cout << "Warning: need exactly one command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }

    
    //Opening the input file (dictionary.txt)
    ifstream dataIn;
    dataIn.open(argv[1]);

    //Check whether the input file can be open successfully or not
    if(dataIn.fail()){
        cout << "Warning: cannot open file named " << argv[1] << "!"<< endl;
        return 2;
    }

    //For the ladder of words
    WordLadder ladder;    

    //Until the end of the file has been reached
    while(!dataIn.eof()){

        //Variable to hold content of current line
        string line;

        //Retrieve the word from the current line
        getline(dataIn, line);
        
        //Adding the word into the ladder
        ladder.insertWord(line);
    }


    //Strings to hold user's inputs
    string word1, word2;

    //Loop runs until user wants to quit
    while(true){

        //Displaying beginning message
        cout << endl << "Welcome to CS216 Word Ladder!" << endl;
        cout << "Please give me two English words, and I will convert the first into the second by modifying one letter at a time." << endl;

        //Asking the user for their first word
        cout << "Please type the FIRST word (or type Enter to quit): ";

        //Retrieving the user's first word input
        getline(cin,word1);

        //If the user entered nothing
        if (word1 == "")
            //Break out of loop to end program
            break;

        //Asking the user for their second word
        cout << "Please type the SECOND word (or type Enter to quit): ";

        //Retrieving the user's second word input
        getline(cin,word2);

        //If the user entered nothing
        if(word2 == "")
            //Break out of loop to end program
            break;
        
        //Turning both words into lowercase
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);

        //Vector holds the ladder (path) for the two words
        vector<string> ladderOfWords = ladder.getLadder(word1, word2);
        

        //If words were both different and there is a path
        if(ladderOfWords.size() != 0){

            //Display how far the words are
            cout << "The ladder distance from " << word1 << " to " << word2 << " is " << ladderOfWords.size()+1 << "-word long" << endl;
            
            //Displaying the ladder
            cout << "A ladder form [" << word1 << "] to [" << word2 << "]: " << endl;    
          
            //Stack needed to flip output order
            stack<string> values;

            //Cycling through all the words in the ladder
            for(string x: ladderOfWords){
                //Don't want to push the first word, or the path will be out of order
                if(x!=word1)
                    //Pushing the word onto the stack
                    values.push(x);
            }

            //Printing the source word
            cout << word1 << " ---> ";

            //Until the stack is empty
            while(!values.empty()){
                //Print the current word at the top
                cout << values.top() << " ---> ";

                //Pop the word at the top
                values.pop();
            }

            //Printing out the destination word
            cout << word2 << endl;

         }

    }

    //Goodbye message when program ends
    cout << "Have a beautiful day. See you next time..." << endl;
}
