/*
 *course: CS216-00x
 *Project: Lab 12 (as part of Project 3)
 *Purpose: to demonstrate a simple Word Ladder, using four-letter words as examples 
 *         create a graph from given set of vertices and edges
 *         repeatedly ask the user to choose a source vertex(word1), then a destination vertex(word2) (type enter to quit)
 *         each vertex is labeled with a four-letter word. If two words are only different by a single letter, there is an edge between them.
 *         and calculate how many steps of the "Word Ladder" from word1 to word2, 
 *         which is the distance of the shortest path from the source to the destination in the Graph
 *         then display the "Word Ladder" from word1 to word2, which is
 *         the shortest path from the source to the destination in the Graph
 *         It is a sub-problem of Project 3.
 *Author: Bobby Bose
 */

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>     // for transform() function
#include "Graph.h"

using namespace std;

int main()
{
    // Create a graph given by a group of words
    // if two words are only different by a single letter, there is an edge between them
    Graph<string> words;
    words.addEdge("fail", "fall");
    words.addEdge("fail", "foil");
    words.addEdge("foul", "foil");
    words.addEdge("foul", "fool");
    words.addEdge("fool", "pool");
    words.addEdge("cool", "pool");
    words.addEdge("pool", "poll");
    //words.addEdge("poll", "pole");
    //words.addEdge("poll", "pall");
    words.addEdge("fall", "pall");
    words.addEdge("pall", "pale");
    words.addEdge("pole", "pale");
    words.addEdge("pole", "pope");
    words.addEdge("pale", "sale");
    words.addEdge("pale", "page");
    words.addEdge("page", "sage");
    words.addEdge("sale", "sage");
    words.addEdge("cool", "fool");
    words.addEdge("foil", "fool");

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

        map<string,int> distance;
	    map<string, string> go_through;
        int dis = words.BFS(word1, word2, distance, go_through);
        // Display the ladder distance from word1 to word2
        // Display the shortest path on the word ladder from word1 to word2
        // the ladder distance is defined as the number of edges on the shortest path from one vertex to another
        // the ladder distance of the same vertex to itself is 0 
        // if word1 and word2 are the same word, your program should display "Two words should be different." 
        // there is no path from word1 to word2 if its ladder distance is -1
        // there is no path from word1 to word2 if its ladder distance is -2, which means either word1 or/and word2 is invalid
        // your code starts here...

        //If there is no path
        if(dis == NOPATH || dis == INVALID_VERTEX)
            cout << "These is no path from [" << word1 << "] to [" << word2 << "] " << endl;

        //If both words were the same
        else if (dis==0){
            cout << "Two words should be different." << endl;
        }

        //If words were both different and there is a path
        else{

            //Display how far the words are
            cout << "The ladder distance from [" << word1 << "] to [" << word2 << "] is " << dis << "-step away" << endl;
            //Displaying the ladder
            cout << "A ladder form [" << word1 << "] to [" << word2 << "]: " << endl;    
            
            //Go through path backwards in function, so nextVertex is word2 here
            string nextVertex = word2;

            //Displaying the first word
            cout << word1;

            //Stack to hold values for path
            stack<string> values;

            //Working backwards from destination to source
            while(go_through[nextVertex] != word1){
               
                //Adding the next vertex along the path to the stack
                values.push(go_through[nextVertex]);

                //nextVertex is now the new vertex we are at along the path
                nextVertex = go_through[nextVertex];
            }

            //Until the stack is empty
            while(!values.empty()){
                
                //Prting the current top value
                cout << " ---> " << values.top();

                //Pop the top
                values.pop();
            }
            
            //Printing the final word
            cout << " ---> " << word2 << endl;
        }
    
    }

    cout << "Thank you for using this program, bye..." << endl;
    return 0;
}

