#ifndef MATH_TUTOR_H
#define MATH_TUTOR_H

#include <string> // Provides support for string operations.
#include <tuple>  // Allows returning multiple values in a single function.
#include <vector> // Used for storing details of questions.

using namespace std;

// Constants
const int MAX_ATTEMPTS = 3;         // Maximum attempts allowed for each question.
const int LEVEL_RANGE_CHANGE = 10; // Amount by which the number range changes when leveling up or down.

// Function Prototypes

void DisplayGameIntro(); // Displays the introductory screen with fun math facts.

string GetUserName(); // Prompts the user to input their name and returns it.

int GetNumericValue(); // Validates user input to ensure it is numeric and returns the integer.

bool AskToPlayAgain(); // Asks the user if they want to play another round and returns true or false.

tuple<int, int, char, int> GenerateRandomQuestion(int range); // Generates a random math question and returns a tuple containing operands, operator, and the answer.

void CheckForLevelChange(int &level, int &correct, int &incorrect, int &range); // Adjusts the user's level and range based on correct and incorrect answers.

void DisplaySummary(const vector<vector<int>>& questions, int totalCorrect, int totalIncorrect, int totalAttempts); // Displays a summary report of the user's performance.

#endif // MATH_TUTOR_H
