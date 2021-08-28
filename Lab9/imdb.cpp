/*
 * File: imdb.cpp
 * Course: CS216-00x
 * Project: Lab8 (as part of Project 2)
 * Purpose: Provide the implementation of the class named IMDB
 *          This class represents a movie-actor database
 */
#include <regex>  // needs c++11 standard
#include "imdb.h"

using namespace std;

// default constructor
IMDB::IMDB()
{
    //do nothing
    //since map class contains a default contructor
    //      which constructs an empty container, with no elements
}

// insert a pair<actorName, the set of movieTitle of this actor>
void IMDB::insert_an_actor(string actorName, set<string> movieTitles)
{
    /* First upgrade actors_db */
    // if the key actorName does not exist
    //        add the key to the map actors_db
    // if the key actorName does exist
    //        modify its associated set of movies in the map actors_db
    
    if(actors_db.find(actorName) == actors_db.end()){   //If the actor isn't in the map
        actors_db[actorName] = movieTitles;     //Add the new actor and their movies
    }
    else{
        set<string>::iterator i;    //Otherwise actor is in the map
        for(i = movieTitles.begin(); i != movieTitles.end(); i++){
            actors_db[actorName].insert(*i);    //Add each new movie
        }
    }      

    
    /* Second upgrade movies_db */
    // for each movieTitle in the set of movieTitles,
    // insert actorName to its associated set of actors in the map, movies_db

    set<string>::iterator j;
    for(j = movieTitles.begin(); j != movieTitles.end(); j++){
        movies_db[*j].insert(actorName);    //Adding the new actor to their movies
    }

}


// insert a pair <movieTitle, the set of actor names in this movie>
// this function is optional to this Lab8 assignment
// however it is required in Project 2
void IMDB::insert_a_movie(string movieTitle, set<string> actorNames)       
{
    /* First upgrade movies_db */
    // if the key, movieTitle, does not exist
    //        add the key to the map, movies_db
    // if the key, movieTitle, does exist
    //        modify its associated set of actors in the map movies_db





    /* Second upgrade actors_db */
    // for each actorName in the set of actorNames
    // insert movieTitle to its associated set of movies in the map, actors_db





}

// use passing-in parameter, movieTitle, as the pattern to match 
// one existing movie in the map
// return the matched movie title from the map
// otherwise return empty string
string IMDB::matchExistingMovie(string movieTitle) const
{
    string matchedMovie;
    bool found = false;
    // generate the regular expression to match 
    // which contains movieTitle as a substring
    // note that it performs case insensitive matching
    regex reg(movieTitle, regex_constants::icase);
    auto it = movies_db.begin();
    while (!found && it != movies_db.end())
    {
        if (regex_search(it->first, reg))
        {
            found = true;
            matchedMovie = it->first;
        }
        else
            it++;
    }
    return matchedMovie;
}

// check if a movieTitle does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingMovie(string movieTitle) const
{
    if(movies_db.find(movieTitle) != movies_db.end()) //If movie title is in map
        return true;    //Return true
    else            //If movie title is not in the map
        return false;   //Return false
}

// check if an actorName does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingActor(string actorName) const
{
    if(actors_db.find(actorName) != actors_db.end()) //If actor name is in map    
        return true;    //Return true
    else            //If actor name is not in map
        return false;   //Return false
}

// return a set of movie titles which actorName was in
// if the passing-in parameter: actorName, is not in the map, 
//                   display message andreturn an empty set
set<string> IMDB::find_movies_for_an_actor(string actorName) const
{
    set<string> titles;     //Empty string in case actor is not in movies
    
    if(actors_db.find(actorName) != actors_db.end()){   //If actor is in a movie
        return actors_db.at(actorName); //Return the set of their movies
    }
    else{                       //If actor is not in a movie                                
        cout << "Actor name is not in the map" << endl; //Tell the user
        return titles;  //Return an empty set
    }


}

// return a set of actor names which were all in the movieTitle
// if the passing-in parameter: movieTitle is not in the map, 
//                   display message and return an empty set
set<string> IMDB::find_actors_in_a_movie(string movieTitle) const
{
    if(movies_db.find(movieTitle) != movies_db.end()){  //If movie is in map
        return movies_db.at(movieTitle);    //Return the set of actors in movie
    }
    else{                       //If movie is not in map
        cout << "Movie title is not in the map" << endl;    //Tell the user
        set<string> s;      //Empty set to return
        return s;           //Return empty set
    }

}
