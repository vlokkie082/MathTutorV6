#include "math_tutor.h"
#include <iostream>
#include <string>
#include <tuple>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <iomanip> // For setprecision and setw

using namespace std;

void DisplayGameIntro() {
    cout << "***************************************************************************************************" << endl;
    cout << "                      __  __       ___  _        _____       __                                 " << endl;
    cout << "                     |  \\/  | __ __|  |_| |__    |_   _|   _|  |_ ___    _ __                  " << endl;
    cout << "                     | |\\/| |/ _  |  __| '_  \\    | || | | |  __/  _ \\ | '__|               " << endl;
    cout << "                     | |  | | (_|  |  |_| | | |    | || |_| |  || (_) | | |                     " << endl;
    cout << "                     |_|  |_|\\__,_ |\\___|_| |_|    |_| \\__,_|\\__ \\____/ |_|                " << endl;
    cout << "***************************************************************************************************" << endl;
    cout << "*                              Welcome to Silly Simple Math Tutor                                *" << endl;
    cout << "***************************************************************************************************" << endl;
    cout << "Fun Math Facts:" << endl;
    cout << "* The word “hundred” actually comes from the old Norse term “hundrath,” which means 120, not 100." << endl;
    cout << "* In a room of 75 people, there’s a 99.9% chance that two people share the same birthday." << endl;
    cout << "* A palindrome number reads the same forwards and backwards like (121, 1331, or 12321)." << endl;
    cout << "* 111,111,111 × 111,111,111 = 12,345,678,987,654,321. It forms a beautiful pattern!" << endl;
    cout << "* 40 is the only number with its letters in alphabetical order when spelled out." << endl;
    cout << "* Zero is the only number that cannot be represented in Roman numerals." << endl;
    cout << "***************************************************************************************************" << endl;
}

string GetUserName() {
    string userName;
    cout << "What is your name: ";
    getline(cin, userName);
    return userName;
}

int GetNumericValue() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover characters
    return value;
}

bool AskToPlayAgain() {
    string input;
    while (true) {
        cout << "Do you want to continue (y=yes | n=no)? ";
        getline(cin, input);

        for (char &c : input) c = tolower(c);

        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;

        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
    }
}

tuple<int, int, char, int> GenerateRandomQuestion(int range) {
    int leftNum = rand() % range + 1;
    int rightNum = rand() % range + 1;
    char mathSymbol;
    int correctAns;

    int operation = rand() % 4;
    switch (operation) {
        case 0:
            mathSymbol = '+';
            correctAns = leftNum + rightNum;
            break;
        case 1:
            mathSymbol = '-';
            if (rightNum > leftNum) swap(leftNum, rightNum);
            correctAns = leftNum - rightNum;
            break;
        case 2:
            mathSymbol = '/';
            leftNum *= rightNum; // Ensure divisibility
            correctAns = leftNum / rightNum;
            break;
        case 3:
            mathSymbol = '*';
            correctAns = leftNum * rightNum;
            break;
        default:
            mathSymbol = '?';
            correctAns = 0;
    }
    return make_tuple(leftNum, rightNum, mathSymbol, correctAns);
}

void CheckForLevelChange(int &level, int &correct, int &incorrect, int &range) {
    if (correct == MAX_ATTEMPTS) {
        level++;
        range += LEVEL_RANGE_CHANGE;
        correct = incorrect = 0;
        cout << "🎉 Level up! You're now at level " << level << " 🎉" << endl;
        cout << "The range of numbers has increased to 1 - " << range << endl;
    } else if (incorrect == MAX_ATTEMPTS && level > 1) {
        level--;
        range -= LEVEL_RANGE_CHANGE;
        correct = incorrect = 0;
        cout << "😢 Level down. You're now back at level " << level << " 😢" << endl;
        cout << "The range of numbers has decreased to 1 - " << range << endl;
    }
}

void DisplaySummary(const vector<vector<int>>& questions, int totalCorrect, int totalIncorrect, int totalAttempts) {
    cout << "===================================\n";
    cout << "            Summary Report          \n";
    cout << "===================================\n\n";
    cout << "Level       Question       Attempts\n";
    cout << "-----------------------------------\n";

    // Iterate through the questions vector and display details
    for (const auto& row : questions) {
        int mathLvl = row[0];
        int leftNum = row[1];
        char mathSymbol = static_cast<char>(row[2]);
        int rightNum = row[3];
        int correctAns = row[4];
        int numAttempt = row[5];

        cout << setw(10) << left << mathLvl
             << setw(8) << leftNum
             << setw(3) << mathSymbol
             << setw(8) << rightNum
             << "= " << setw(10) << correctAns
             << setw(12) << numAttempt
             << endl;
    }

    // Display summary totals
    cout << "\n-----------------------------------" << endl;
    cout << "Total Questions: " << questions.size() << endl;
    cout << "Total Correct: " << totalCorrect << endl;
    cout << "Total Incorrect: " << totalIncorrect << endl;
    if (totalAttempts > 0) {
        cout << "Accuracy: " << fixed << setprecision(2)
             << (static_cast<float>(totalCorrect) / totalAttempts) * 100
             << "%" << endl;
    } else {
        cout << "Accuracy: N/A (No questions answered)" << endl;
    }
    cout << "-----------------------------------" << endl;

    // Goodbye message
    cout << "This is the end of the program, see you soon for more training! :)" << endl;
}

