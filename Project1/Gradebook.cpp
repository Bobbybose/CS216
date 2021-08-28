/*
 * File:   Gradebook.h
 * Course: CS216
 * Project: Project 1
 * Purpose: provide the implementation of the member functions of the class named Gradebook
 *
 * Author: Bobby Bose
 *
 */

#include <iostream>
#include "Gradebook.h"


 // default constructor
 Gradebook::Gradebook(){

 }

// return the size of the current vector: scores,
// which represents current gradebook
 int Gradebook::getSize() const{
	 return scores.size();													//Returns the size of scores vector
 }

 // insert a FinalGrade object, newFG,
// into the end of the current gradebook
 void Gradebook::insert(FinalGrade newFG){
	 scores.push_back(newFG);												//Adding a new FinalGrade to the end of scores
 }

 // return a FinalGrade object,
// which holds the maximum score in the current gradebook
 FinalGrade Gradebook::getMax() const{
	 double max_score=scores[0].getScore();									//Assuming the first score is the max

	 for(int i=1; i<getSize(); i++){										//Starting at the second score
		 if(scores[i].getScore()>max_score)									//If the current score is larger than the current max
			 max_score=scores[i].getScore();									//Make the current score the max
	 }

	 return max_score;														//Return the max score

 }

 // return a FinalGrade object,
// which holds the minimum score in the current gradebook
 FinalGrade Gradebook::getMin() const{
	 double min_score=scores[0].getScore();									//Assuming the first score is the min

	 for(int i=1; i<getSize(); i++){										//Starting at the second score
		 if(scores[i].getScore()<min_score)									//If the current score is smaller than the current min
			 min_score=scores[i].getScore();									//Make the current score the min
	 }

	 return min_score;														//Return the min score
 }

 // return the average score among all scores in the current gradebook
 double Gradebook::getAverage() const{
	 double sum = 0;														//Variable for the sum of scorss													

	 for(int i=0; i<getSize(); i++){										
		sum+=scores[i].getScore();											//Adding each score to sum		
	 }

	 return (sum/getSize());												//Returning the sum divided by the number of scores
 }

 // For each FinalGrade object in the current gradebook,
// its score will be increased by the given value
 // If the score reaches MAX_SCORE, it does not go beyond
 void Gradebook::incrementScore(double value){

	 for (int i = 0; i < getSize(); i++) {									//Cycling through all the FinalGrades
		 if (scores[i].getScore() + value > MAX_SCORE)						//If a grade with the curve added goes over the maximum grade
			 scores[i].setScore(MAX_SCORE);										//Set the grade to the max grade
		 else
			 scores[i].setScore(scores[i].getScore() + value);				//Incrementing each score by the given value
		 
	 }
 }

 // print the FinalGrade objects in the current gradebook
 void Gradebook::print() const {
	 for (int i = 0; i < getSize(); i++) {
		 scores[i].print();													//Printing each FinalGrade in scores.
	 }
 }



