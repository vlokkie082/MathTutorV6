/************************************************************************************************
Program:     Math Tutor
Section:     4 - 1:00pm
Programmers: Naude Vlok
Date:        20/30/2024
Version:     5
GitHub URL:  https://github.com/vlokkie082/MathTutorV5.git
Description: This program is an easy math tutor that is intended to
            help with what can be known as "quick math". This program will ask the
            user to enter their name, and then ask them to answer a variety of math-related
            questions. The more questions the user gets right, the higher they level up.
            If they get a question wrong a certain number of times, they level back down.
            As the levels increase, so does the range of the numbers in the levels to
            increase difficulty.
**************************************************************************************************/

#include "math_tutor.h"
#include <iostream>
#include <ctime> // For random number generation

using namespace std;

int main() {
    srand(time(nullptr)); // Seed the random number generator
    DisplayGameIntro();   // Display the game intro

    string userName = GetUserName(); // Get the user's name
    cout << "Welcome " + userName + ", Thank you for trying Math Tutor Version 5.0 !!!" << endl;

    int mathLvl = 1, totalCorrect = 0, totalIncorrect = 0, currentRng = LEVEL_RANGE_CHANGE;
    vector<vector<int>> questions; // Vector to store question details
    bool playAgain;

    do {
        auto [leftNum, rightNum, mathSymbol, correctAns] = GenerateRandomQuestion(currentRng);

        int attemptsLeft = MAX_ATTEMPTS;
        bool correct = false; // Tracks whether the question was answered correctly

        while (attemptsLeft > 0 && !correct) {
            cout << "[Level " << mathLvl << "] What does " << leftNum << " " << mathSymbol << " " << rightNum << "? ";
            int userAns = GetNumericValue();

            if (userAns == correctAns) {
                cout << "🎉 Correct! Well done! 🎉" << endl;
                totalCorrect++; // Increment total correct only once per correct answer
                correct = true;
            } else {
                attemptsLeft--;
                if (attemptsLeft > 0) {
                    cout << "❌ Incorrect. Try again! You have " << attemptsLeft << " attempt(s) left. ❌" << endl;
                } else {
                    cout << "❌ Incorrect. The correct answer was " << correctAns << ". ❌" << endl;
                }
            }
        }

        // Increment total incorrect if the question was not answered correctly
        if (!correct) {
            totalIncorrect++;
        }

        // Add question details to the summary
        questions.push_back({
            mathLvl,
            leftNum,
            static_cast<int>(mathSymbol),
            rightNum,
            correctAns,
            MAX_ATTEMPTS - attemptsLeft // Record the number of attempts used
        });

        // Check for level changes
        CheckForLevelChange(mathLvl, totalCorrect, totalIncorrect, currentRng);

        // Ask if the user wants to play again
        playAgain = AskToPlayAgain();

    } while (playAgain);

    // Display the summary report
    DisplaySummary(questions, totalCorrect, totalIncorrect, totalCorrect + totalIncorrect);

    cout << "Thanks for playing! Goodbye!" << endl;
    return 0;
}
