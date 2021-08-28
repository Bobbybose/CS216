/*
 *Course: CS216-00x
 *Project: Lab5 (As second part of Project1)
 *Purpose: As part of the Project 1
 to test if the definition of Gradebook class is correct.
 *         it provides THREE testing cases of expected average
 *            to curve the scores based on each expected average.
 *         each student's score is at the range [0,100]
 *         the expected average is at the range (original average, 100]
 *
 *****PLEASE DO NOT CHANG THIS FILE***** 
 *
 */

#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <string>
#include <cmath>        // std::abs
#include "Gradebook.h"

using namespace std;

int main()
{
    // create a static array for testing purpose only
    // the scores in the array are "hard-coded"
    const int SIZE = 6;
    double CS216Final[SIZE] = {98.5, 76, 80.5, 69.5, 87, 57};

    Gradebook CS216gradebook_original;

    for (int i=0; i < SIZE; i++)
    {
        FinalGrade stu_FG(CS216Final[i]);
        CS216gradebook_original.insert(stu_FG);
    }

    // Implement a Grade Curve Calculator:
    // Based on each expected average (there are THREE testing cases)
    // Display the original gradebook and the original average score
    // Then based on each expected average, decide
    //         if adjustment is needed (expected average is close enough to the original average or not);
    //         if adjustment is needed (may not in the valid range)
    //            Display the curved gradebook, the number of scores in the 
    //            gradebook, the maximum score and its letter grade, the 
    //            minimum score and its letter grade and the actual average
    // Note that Since any score cannot be larger than MAX_SCORE, 
    // the "Actual Average" can be less than or equal to "Expected Average"
    cout << fixed << setprecision(2);
    cout << endl << endl;
    cout << "The original gradebook for CS216: " << endl;
    CS216gradebook_original.print();
    cout << "The original average score is:\t" << CS216gradebook_original.getAverage() << endl;

    // create a static array for testing purpose only
    // For three testing cases: 
    //     three expected averages in the array are "hard-coded"
    const int TESTING_CASES = 3;
    double expected_avg[TESTING_CASES] = {56.5, 78.075, 95};

    for (int i = 0; i < TESTING_CASES; i++)
    {
        cout << endl << "Testing case " << i+1 << " :" << endl;
        cout << "The expected average score is:\t" << expected_avg[i] << endl;
        // check if the expected average is close enough to the original average
        double diff = expected_avg[i] - CS216gradebook_original.getAverage();
        const double EPSILON = 1.0e-2;
        if (abs(diff) < EPSILON)
            cout << "The scores are perfect, no need for the grading curve!" << endl;
        else
        {
            // check if the expected average is in the correct range: (original average,100]
            if (diff < MIN_SCORE || expected_avg[i] > MAX_SCORE)
            {
                cout << "The expected average is not in the correct range, please try again..." << endl;
            }
            else  // valid expected average, adjust scores accordingly
            {
                Gradebook CS216gradebook_curved = CS216gradebook_original;
                CS216gradebook_curved.incrementScore(diff);
                cout << "The curved gradebook for CS216: " << endl;
                CS216gradebook_curved.print();
                cout << "The number of scores is:\t" << CS216gradebook_curved.getSize() << endl;
                cout << "The maximum score is:\t";
                CS216gradebook_curved.getMax().print();
                cout << "The minimum score is:\t";
                CS216gradebook_curved.getMin().print();
                cout << "The actual average score is:\t" << CS216gradebook_curved.getAverage() << endl;
            }
        }
    }

    return 0;
}

