/*
 * File:   PA1.cpp
 * Course: CS216
 * Project: Project 1
 * Purpose: Program caclculates the average of a final and then implements a curve.
 *
 * Author: Bobby Bose
 *
 */

#include <iostream>																		//For cin/cout	
#include <iomanip>                                                                      //For setprecision
#include <string>																		//For strings
#include "Gradebook.h"																	//Gradebook also has FinalGrade included in it

using namespace std;

int main() {

	Gradebook CS216gradebook_original;													//Gradebook for the original grades entered
	Gradebook CS216gradebook_modified;													//Gradebook for modified grades after extra score is added

	double input;																		//Variable to store user's entered answer
	double expectedAverage;																//Variable for debugging if answer is messed up
	double extraScore;																	//Extra score needed to be added to original scores
	

	while (true){

		cout << "Please enter a score (type 'Q' or 'q' to quit): " << endl;				//Asking the user to enter a number
		cin >> input;																	//Storing the user's answer in input		
        cin.ignore(256, '\n');

		if (cin.fail()){																//If the cin function failed for some reason
			string inputtedData;															//Variable to store the inputted data
			cin.clear();																	//Clearing error state flags
			cin >> inputtedData;															//Storing the user's answer in inputtedData
            cin.ignore(256, '\n');

			if (inputtedData == "q" || inputtedData == "Q")								//If the user entered a 'q' or "Q"
				break;																		//Quit the loop
			else {																		//Otherwise
				cout << "Invalid input, please try again." << endl;						//Tell the user they entered an invalid response
				continue;																	//Go back to beginning of loop to re-ask for answer
			}
		}

		if (input < 0 || input > 100){													//If the input is outside a normal grade's range		
			cout << "The score is not in the correct range, please try again." << endl;	//Tell the user it was invalid
		}

		else{																			//If the input was in range
			FinalGrade FGinput(input);													//Store it into a new FinalGrade variable
			CS216gradebook_original.insert(FGinput);										//Store the new FinalGrade in the gradebook
		}
	}

    
    if(CS216gradebook_original.getSize()==0){
        cout << "The gradebook is Empty!" << endl << "Thank you for using the Grade Curve Calculator." << endl;
        return 0;
    }


    cout << fixed << setprecision(2);
	cout << "Scores in the gradebook: " << endl;										//Displaying all the scores in the gradebook		
	CS216gradebook_original.print();
	cout << "There are " << CS216gradebook_original.getSize() << " scores in the gradebook." << endl;//How many scores are in the gradebook

	cout << "The highest score is " << CS216gradebook_original.getMax().getScore() << "\t\tLetter Grade: " << CS216gradebook_original.getMax().decideLetterGrade() << endl;	//Highest score in the gradebook
	cout << "The lowest score is " << CS216gradebook_original.getMin().getScore() << "\t\tLetter Grade: " << CS216gradebook_original.getMin().decideLetterGrade() << endl;	//Lowest score in the gradebook

    cout << "The original average score is " << CS216gradebook_original.getAverage() << "." << endl << endl;//Average score in the gradebook
	
   
    while(true){

        cout << "Please enter your expected average score to curve (type 'Q' or 'q' to quit): ";    //Asking the user to enter their expected average		
	    cin >> expectedAverage;                                                                 
        cin.ignore(256, '\n');

        if(cin.fail()){                                                                 //If the input was invalid             
            string dataInputted;                                                            //Variable to analyze input
            cin.clear();
            cin >> dataInputted;                                                            //Retrieve input
            cin.ignore(256,'\n');

            if(dataInputted == "q" || dataInputted == "Q"){                                 //If the user wanted to quit
                cout << "Thank you for using the Grade Curve Calculator." << endl;              //Quit the program
                return 0;
            }
            else{
                cout << "Invalid input, please try again." << endl;                         //Otherwise inform the user that the input was invalid        
                continue;
            }

        }

	
    	if(expectedAverage>100 || expectedAverage<CS216gradebook_original.getAverage()) 	   //If the expected average is outside the range
	    	cout << "The expected average score is not in the correct range, please try again." << endl;	//Inform user of this mistake
        else
            break;
    }

    double diff = expectedAverage - CS216gradebook_original.getAverage();               //Difference between expected average and actual.
    const double margin = 1.0e-2;                                                       //How far apart the expected and actual average can be to be considered the same
    
    if(abs(diff) < margin){                                                             //If the expected and actual average are the same
        cout << "The scores are perfect, no need for the grading curve!" << endl;        //Inform the user
        return 0;                                                                        //End program
    }    


	extraScore = expectedAverage - CS216gradebook_original.getAverage();				//Calculating the curve score

	CS216gradebook_modified = CS216gradebook_original;									//Setting the modified Gradebook to the original
	CS216gradebook_modified.incrementScore(extraScore);									//Incrementing the scores in the modified gradebook	


	cout << "Scores in the modified gradebook: " << endl;								//Displaying the scores in the modified gradebook
	CS216gradebook_modified.print();
	cout << "There are " << CS216gradebook_modified.getSize() << " scores in the modified gradebook." << endl;//How many scores there are

	cout << "The highest score is " << CS216gradebook_modified.getMax().getScore() << "\t\tLetter Grade: " << CS216gradebook_modified.getMax().decideLetterGrade() << endl;	//Displaying the highest score
	cout << "The lowest score is " << CS216gradebook_modified.getMin().getScore() << "\t\tLetter Grade: " << CS216gradebook_modified.getMin().decideLetterGrade() << endl;	//Displaying the lowest score

	cout << "The new average score is " << CS216gradebook_modified.getAverage() << "." << endl;		//Displaying the average score


	return 0;
}
