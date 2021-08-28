/*
 *course: CS216-00x
 *Project: Lab 13 (as part of Project 3)
 *Purpose: to demonstrate a simple Word Ladder, using four-letter words as examples 
 *         create a graph from given set of vertices and edges
 *         repeatedly ask the user to choose a source vertex(word1), then a destination vertex(word2) (type enter to quit)
 *         each vertex is labeled with a four-letter word. If two words are only different by a single letter, there is an edge between them.
 *         and calculate how many words on the "Word Ladder" from word1 to word2, 
 *         which is one more than the distance of the shortest path from the source(word1) to the destination(word2) in the Graph
 *         then display the "Word Ladder" from word1 to word2, which is
 *         the shortest path from the source to the destination in the Graph
 *         It is a sub-problem of Project 3.
 *Author: (your name)
 */

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>     // for transform() function
#include "Graph.h"
#include "WordLadder.h"
#include <stack>

using namespace std;

int main()
{
    // Create a graph given by a group of four-letter words (match Figure 1 in Lab12)
    // if two words are only different by a single letter, there is an edge between them
    string word;
    vector<string> words;

    words.push_back("fail");
    words.push_back("fall");
    words.push_back("foil");
    words.push_back("foul");
    words.push_back("fool");
    words.push_back("fall");   // insert a duplicate word
    words.push_back("cool");
    words.push_back("pool");
    words.push_back("poll");
    words.push_back("fall");    // insert one more time
    words.push_back("pall");
    words.push_back("pole");
    words.push_back("pope");
    words.push_back("pale");
    words.push_back("sale");
    words.push_back("page");
    words.push_back("sage");

    WordLadder cs216_wordLadder(words);

    string word1, word2;

    while (true)
    {
        cout << endl << endl;
        cout << "Welcome to CS216 Word Ladder!" << endl;
        cout << "Please give me two English words, and I will convert the first into the second by modifying one letter at a time." << endl;
        cout << "For the Demo purpose, let us try four-letter words only." << endl;
        cout << "Please type the FIRST four-letter word (or type Enter to quit): " << endl;
	    getline(cin, word1);
        
        if (word1 == "")
            break;
        
        cout << "Please type the SECOND four-letter word (or type Enter to quit): " << endl;
	    getline(cin, word2);
        
        if (word2 == "")
            break;

        // convert both word1 and word2 to all lower-case letters
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
        
        vector<string> ladder = cs216_wordLadder.getLadder(word1, word2);

        // Display the ladder distance from word1 to word2
        // Display the shortest path on the word ladder from word1 to word2
        // the ladder distance is defined as the number of vertices(word) on the shortest path from one vertex to another
        // the ladder distance of the same vertex to itself is 1-word
        // for simplicity purpose, if the ladder distance is <= 1, this program does nothing, no display
        if ( ladder.size() != 0)
        {
            cout << "The ladder from " << word1 << " to " << word2 << " is " << ladder.size() << "-word long." << endl;
            cout << "A ladder from [" << word1 << "] to [" << word2 << "]:" << endl;
             
            stack<string> values;

            for(string x: ladder){
                if(x!=word1)
                    values.push(x);
            }
            
            cout << word1 << " ---> ";
            
            while(!values.empty()){
                cout << values.top() << " ---> ";
                values.pop();
            }

            cout << word2 << endl;
            
        }
    }

    cout << "Thank you for using this program, bye..." << endl;
    return 0;
}

