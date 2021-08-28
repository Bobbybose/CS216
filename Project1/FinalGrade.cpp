/* 
 * File:   FinalGrade.cpp
 * Course: CS216
 * Project: Lab 4
 * Purpose: provide the implementation of the member functions of the class named FinalGrade
 *
 * Author: Bobby Bose
 *
 */
#include <iostream>
#include "FinalGrade.h"

// default constructor
FinalGrade::FinalGrade()
{
    // give initial value to be 0
    score = 0;
}

// constructor: give the initial value to the private data member score 
// to pass-in parameter in_score
FinalGrade::FinalGrade(double in_score)
{
    if (in_score < MIN_SCORE || in_score > MAX_SCORE)
        score = 0;
    else
        score = in_score;
}

// set the private data member: score
// to pass-in parameter in_score
void FinalGrade::setScore(double in_score)
{
    if (in_score < MIN_SCORE || in_score > MAX_SCORE)
        score = 0;
    else
        score = in_score;
}

// return the value of the data member: score
double FinalGrade::getScore() const
{
    return score;
}

    // return the corresponding letter grade from score
    // based on the grading policy in CS216 syllabus
char FinalGrade::decideLetterGrade() const
{
    // your code starts here...
	if (score >= 90) {                      //If the score is above a 90
		return 'A';								//It's an A
	}
	else if (score >= 80) {                 //If the score is above an 80 and below a 90
		return 'B';								//It's a B
	}
	else if (score >= 70) {                 //If the score is above a 70 and below an 80
		return 'C';								//It's a C
	}
	else if (score >= 60) {                 //If the score is above a 60 and below a 70    
		return 'D';								//It's a D
	}
	else									//Otherwise, it's an E        
        return 'E';
}

// print the score and letter grade in the format: (for example)
// Score: 88        Letter Grade: B
void FinalGrade::print() const
{
    cout << "Score: " << score << "\t\tLetter Grade: " << this->decideLetterGrade() << endl;
}

