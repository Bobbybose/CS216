/*
 * Name: Bobby Bose
 * File: WordLadder.cpp
 * Course: CS216-007
 * Project: Project 3
 * Purpose: Provide the implementation of WordLadder class 
*/

#include "WordLadder.h"

using namespace std;

//default constructor
WordLadder::WordLadder(){
}

//alternative constructor
WordLadder::WordLadder(const vector<string>& words){
}

//to add a new word in the collection
void WordLadder::insertWord(string newword){
    //Adding a new word into the vector in wordsByLength for this length of word
    wordsByLength[newword.length()].push_back(newword);

}

//return a graph from the group of words with the same lengths = length
//there is an edge between two words
//                 if two words are only different in a single letter
Graph<string> WordLadder::WordsGraph(int length) const{
    //Graph to store the words with the same length
    Graph<string> graphedWords;

    //Map to hold the buckets for the words
    map<string, vector<string>> buckets;
   
    //Going through every word in wordsByLength that's the right length
    for(string word: this->wordsByLength.at(length)){
        //Going through every character in the current word
        for(int i=0; i<length; i++){
            //New variable to modify word
            string newword = word;
            //Replacing the current char position with a *
            newword = newword.replace(i, 1, "*");
            //Creating a new bucket for the subword, or adding the subword to the right bucket
            buckets[newword].push_back(word);
        }
    }

    //i is vector in buckets
    for(auto i=buckets.begin(); i!=buckets.end(); i++){
        //j is a word (string) in i (vector)
        for(auto j=i->second.begin(); j!=i->second.end(); j++){
            //k is another word (string) in i (vector)
            for(auto k=i->second.begin(); k!=i->second.end(); k++){
                //If the words are different
                if(*j != *k){
                    //Add an edge between them
                    graphedWords.addEdge(*j, *k);
                }
            }
        }
    }

    return graphedWords;
}

//return a vector of words
//which represents a word ladder from word1 to word2
//any two adjacent words along the ladder differ in only one character
vector<string> WordLadder::getLadder(string word1, string word2) const{

    //Store distance from the source word
    map<string, int> distanceFrom;
    //What you must go through at each word to reach the destination
    map<string, string> go_through;
     
    //Graph holds the words of the right length
    Graph<string> words = this->WordsGraph(word1.length());

    //Vector to hold the path of words
    vector<string> ladder;

    //If the words are not the same length
    if(word1.length() != word2.length()){
        //Inform the user and return
        cout << "The two words must be the same length!" << endl;
        cout << "There is no ladder from [" << word1 << "] to [" << word2 << "] " << endl;
        return ladder;
    }

    //Calling Graph's BFS and storing the distance to the source word form the destination word
    int dis = words.BFS(word1, word2, distanceFrom, go_through);

    //If there is no path from the source word to the destination word
    if(dis == NOPATH || dis == INVALID_VERTEX){
        //Inform the user and return
        cout << "These is no ladder from [" << word1 << "] to [" << word2 << "] " << endl;
        return ladder;
    }
    //If both words were the same
    else if (dis==0){
        //Inform the user and return
        cout << "The two words must be different!" << endl;
        return ladder;
    }
    

    //Next word to look for
    string nextVertex = word2;
    
    //Add the source word to the path vector
    ladder.push_back(word1);

    //Until we reach the source word
    while(go_through[nextVertex] != word1){
        //Add the current word to the path vector
        ladder.push_back(go_through[nextVertex]);
        //Next vertex is the word you must go through to reach the source word
        nextVertex = go_through[nextVertex];
    }

    //Returning the path
    return ladder;

}

