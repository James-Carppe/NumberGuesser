#include <iostream>
#include <random>

int gamePower, possibleGuesses, totalPossibleGuesses, globalLowerNumber, globalUpperNumber;

int generateRandomNumber() {
    int lowerNumber, upperNumber, targetNumber;
    std::random_device device;

    std::default_random_engine numberGenerator(device());

    std::uniform_int_distribution<int> lowerGenerator(1, 100);
    lowerNumber = lowerGenerator(numberGenerator);

    std::uniform_int_distribution<int> upperGenerator(1000, 10000);
    upperNumber = upperGenerator(numberGenerator);

    std::uniform_int_distribution<int> targetGenerator(lowerNumber, upperNumber);
    targetNumber = targetGenerator(numberGenerator);

    globalLowerNumber = lowerNumber;
    globalUpperNumber = upperNumber;

    return targetNumber;
}

int calculateGuessDistance(int numberGuess, int targetNumber) {
    int closestRange, guessDifference, numberComputation;
    bool found;

    guessDifference = abs(targetNumber - numberGuess);

    found = false;
    numberComputation = 0;

    while (!found) {
        if (guessDifference <= pow(gamePower, numberComputation)) {
            found = true;
            closestRange = numberComputation;
        } else {
            numberComputation++;
        }
    }

    return closestRange;
}

int getUserResponse(const std::string& prompt) {
    int result;

    std::cout << prompt;
    std::cin >> result;
    std::cout << std::endl;

    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "This input is restricted to integers only. PLEASE TRY AGAIN." << std::endl;

        std::cout << prompt;
        std::cin >> result;
        std::cout << std::endl;
    }

    return result;
}

int gameLoop() {
    int targetNumber, numberGuess, guessDifference;
    bool stopGame;

    gamePower = getUserResponse("What base would you like to use for hints?");
    gamePower = abs(gamePower);

    if (gamePower == 1) {
        possibleGuesses = 500;
        totalPossibleGuesses = 500;
    } else {
        possibleGuesses = gamePower * 5;
        totalPossibleGuesses = gamePower * 5;
    }

    std::cout << std::endl;
    std::cout << "You have chosen a base of " << gamePower << ". You have " << possibleGuesses << " guesses." << std::endl;
    std::cout << std::endl;

    targetNumber = generateRandomNumber();
    stopGame = false;

    std::cout << "Your number is between " << globalLowerNumber << " and " << globalUpperNumber << "." << std::endl;

    while (!stopGame) {
        if (possibleGuesses <= 0) {
            std::cout << "You ran out of guesses. The number was " << targetNumber << ", better luck next time!" << std::endl;
            stopGame = true;
        } else {
            numberGuess = getUserResponse("Please guess a number: ");

            if (numberGuess == targetNumber) {
                stopGame = true;
                std::cout << "You guessed the number in " << (totalPossibleGuesses - possibleGuesses) << " guesses." << std::endl;
            } else {
                possibleGuesses--;
                guessDifference = calculateGuessDistance(numberGuess, targetNumber);
                std::cout << "Your guess (" << numberGuess << ") is within " << pow(gamePower, guessDifference) << " of the number. You have "<< possibleGuesses << " guesses remaining." << std::endl;
            }
        }

    }

    return 0;
}

int main() {
    bool playing;
    std::string response;

    playing = true;
    while (playing) {
        gameLoop();

        std::cout << "Do you want to play again?";
        std::cin >> response;
        std::cout << std::endl;

        if (response == "Yes" || response == "yes") {
            playing = true;
            std::cout << "Game is being reset." << std::endl;
        } else {
            playing = false;
            std::cout << "Game will now exit." << std::endl;
        }
    }

    return 0;
}
