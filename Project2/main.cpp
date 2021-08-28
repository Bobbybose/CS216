/*
 * Course: CS216
 * Project: Project 2
 * Purpose: 
 * Author: Bobby Bose
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <map>
#include <sstream>
#include "imdb.h"

using namespace std;

void analyzeMovies(const IMDB& imdb);
void analyzeCoActors(const IMDB& imdb);

int main(int argc, char* argv[]){
	// Check whether the number of command line arguments is exactly one 
	if (argc != 2)
	{
		cout << "Warning: need exactly one command line argument." << endl;
		cout << "Usage: " << argv[0] << " inputfile_name" << endl;
		return 1;
	}

	ifstream dataIn;
	dataIn.open(argv[1]);

	// Check whether the input file can be open successfully or not
	if (dataIn.fail())
	{
		cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
		return 2;
	}
	
	// Read data from the input file, assume "good data" from the input file
	// each line of the input file: actorName, movie1, movie2, ..., movieN
	// read one line at a time then tokenize it:
	// create a pair <actorName, the set of movieTitles which the actor was in>
	//        and insert to IMDB object
	IMDB movieList;

	while (!dataIn.eof()){
		string line;
		getline(dataIn, line);
		string actorName, movieTitle;

		// check if the text line is not empty then tokenize it
		if (line.length() != 0)	{
			istringstream iss(line);
			getline(iss, movieTitle, ';');

			// Extract extra white space
			iss >> ws;

			// Create a new set of actors associated with movieTitle
			set<string> actors;

			while (getline(iss, actorName, ':')){
				actors.insert(actorName);
				// extract white space 
				iss >> ws;
			}
			// insert the pair to IMDB object: cs216_imdb
			movieList.insert_a_movie(movieTitle, actors);
		}

	}
	// close the input file
	dataIn.close();



	int userAnswer;

	while (true){
		cout << "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
		cout << "1. Actors in Movies" << endl;
		cout << "2. Actors and co-actors" << endl;
		cin >> userAnswer;
		cin.ignore(256, '\n');

		if (cin.fail()){
			string input;
			cin.clear();
			cin >> input;
			if (input == "Q" || input == "q")
				break;
			else{
				cout << "Invalid option!" << endl;
				continue;
			}
		}

		switch (userAnswer){
		case 1: analyzeMovies(movieList);
			break;
		case 2: analyzeCoActors(movieList);
			break;
		default:
			cout << "Invalid option!" << endl;
		}
	}

	cout << "Thank you for using my program, bye..." << endl;

	return 0;
}

// this function asks the user to input two movie titles
// then finds the matched two movies from the map
// and displays all the actors in either of the two movies
// if no matched movie then display "Invalid movie title" and do nothing
// note that using const call by reference is for efficiency purpose:
//           no copy of IMDB object is made and the argument has been protected
void analyzeMovies(const IMDB& imdb)
{
	// Ask the user to input two movie titles to search for
	string movie1, movie2;

	cout << "Please input the first movie title: ";
	getline(cin, movie1);
	cout << "Please input the second movie title: ";
	getline(cin, movie2);

	// Check if both movie1 and movies can be matched with movies in the map
	// If either one is not, quit the program
	// Otherwise display all the actors in either of two movies
	//                   which are actually the union of two sets
	string matchedMovie1, matchedMovie2;
	matchedMovie1 = imdb.matchExistingMovie(movie1);
	matchedMovie2 = imdb.matchExistingMovie(movie2);
	if ((matchedMovie1.length() > 0) && (matchedMovie2.length() > 0)){
		cout << "Your input matches the following two movies: " << endl;
		cout << matchedMovie1 << endl;
		cout << matchedMovie2 << endl;
		cout << "Both movies are in the database, please continue..." << endl;

		while (true) {
			cout << "Please input your menu option (enter Q or q to quit)" << endl;
			cout << "A -- to print all the actors in either of the two movies." << endl;
			cout << "C -- to print all the common actors in both of the movies." << endl;
			cout << "O -- to print all the actors who are in only one movie, but not in both." << endl;

			char userAnswer;
			cin >> userAnswer;
			cin.ignore(256, '\n');

			if (cin.fail()) {
				string input;
				cin.clear();
				cin >> input;
				if (input == "Q" || input == "q")
					return;
				else {
					cout << "Invalid option!" << endl;
					continue;
				}
			}

			set<string> all = imdb.find_actors_in_a_movie(matchedMovie1);   // to store the union of actors_in_movie1 and actors_in_movie2
			set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);
			
			switch (userAnswer) {
				case 'a':
				case 'A':	
					for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
						all.insert(*i);
					// Display all the actors in either one movie
					cout << "All the actors in either of the two movies:" << endl;
					for (auto i = all.begin(); i != all.end(); i++)
						cout << *i << endl;
					break;

				case 'c': 
				case 'C': 
					cout << "Common actors in both movies:" << endl;
					for (auto i = all.begin(); i != all.end(); i++) {
						if (actors_in_movie2.find(*i) != actors_in_movie2.end())
							cout << *i << endl;
					}
					break;

				case 'o': 
				case 'O':	
					cout << "Actors only in one of two movies:" << endl;
					for (auto i = all.begin(); i != all.end(); i++) {
						if (actors_in_movie2.find(*i) == actors_in_movie2.end())
							cout << *i << endl;
					}
					for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++) {
						if (all.find(*i) == all.end())
							cout << *i << endl;
					}
					break;
			
				case 'q':
				case 'Q':
					return;

				default:
					cout << "Invalid option!" << endl;
			}
		}

	}
	else{
		cout << "Invalid movie title." << endl;
		return;
	}
}

// The function asks the user to type an actor's name
// then check if the user-input name is valid(it is valid if it is in the database stored in the passing in object
// if it is valid, display in each movie which this actor is in, the co-actors who appeared in the same movie
void analyzeCoActors(const IMDB& imdb)
{
	string actor_name;
	cout << "Finding the co-actors of the actor by typing his/her name: ";
	getline(cin, actor_name);
	if (!imdb.isExistingActor(actor_name))
	{
		cout << "The actor name you entered is not in the database." << endl;
		return;
	}

	set<string> movies_of_actor;
	movies_of_actor = imdb.find_movies_for_an_actor(actor_name);
	set<string> actors_in_a_movie;
	for (auto i = movies_of_actor.begin(); i != movies_of_actor.end(); i++)
	{
		cout << "The co-actors of " << actor_name << " in the movie \"" << *i << "\" are: " << endl;
		// Display all the co-actors in one movie
		actors_in_a_movie = imdb.find_actors_in_a_movie(*i);
		for (auto j = actors_in_a_movie.begin(); j != actors_in_a_movie.end(); j++)
		{
			if (*j != actor_name)
				cout << *j << endl;
		}
		cout << "***********************************" << endl;
	}
}
