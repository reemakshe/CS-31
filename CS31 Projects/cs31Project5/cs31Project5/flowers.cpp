//
// Reema Kshetramade
// SID: 205328402
// CS 31 Project 5

#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;

//Constants for the max words that can be filled into the array and the max length of each word filled
const int MAXWORDS = 10000;
const int MAXWORDLENGTH = 6;
const int MAXTRIALLENGTH = 100;

//File with words to be chosen from for each round of game
const char WORDFILENAME[] = "/Users/reemakshetramade/Documents/proj5WordList.txt";

//Function prototypes
int playOneRound(const char words[][MAXWORDLENGTH + 1], int nWords, int wordnum);

int isValidWord(const char word[], const char wordList[][MAXWORDLENGTH + 1], int numWords);

void countFlowersBees(char trial[], char word[]);

int main()
{
    //The word list will be a two dimensional array with MAXWORDS elements which have MAXWORDLENGTH letters
    char w[MAXWORDS][MAXWORDLENGTH + 1];

    //Fill the array with words from the file and terminate program if less than one word is filled
    int numWordsFilled = getWords(w, MAXWORDS, WORDFILENAME);
    if (numWordsFilled < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }

    //Prompt user for how many rounds to play and store their answer
    cout << "How many rounds do you want to play? ";
    int numRounds;
    cin >> numRounds;
    //Ignore the characters after entering the number
    cin.ignore(10000, '\n');


    //If the number of rounds is less than 0, print an error message and terminate the program
    if (numRounds <= 0)
    {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }


    //Intialize variables for the index of the random word to be chosen from the array and the score stats
    int randIndex = 0;
    int avgTotal = 0;
    int minScore = 10000;
    int maxScore= 0;

    //Loop through process of playing a round, for the number of rounds the player entered
    for (int i = 1; i <= numRounds; i++)
    {
        cout << endl;
        int wordLen = 0;
        //Generate random index from 0 to number of words filled in array minus 1 (the last index of array)
        randIndex = randInt(0, numWordsFilled - 1);
        wordLen = strlen(w[randIndex]);
        cout << "Round " << i << endl;
        cout << "The mystery word is " << wordLen << " letters long." << endl;
        
        //Call playOneRound to play a round which returns the number of tries it took to win
        int roundResult = playOneRound(w, numWordsFilled, randIndex);
        //If the player won in 1 try, print a different message than if it was multiple tries
        if (roundResult != -1)
        {
            if (roundResult == 1)
                cout << "You got it in 1 try." << endl;
            else
                cout << "You got it in " << roundResult << " tries." << endl;
        }
        else if (roundResult == -1)
        {
            cout << "Unable to play a round of the game." << endl;
            return 0;
        }
        
        //Determine the sum of the number of tries (used to calculate avg) and determine min and max score
        avgTotal += roundResult;
        if (roundResult > maxScore)
            maxScore = roundResult;
        if (roundResult < minScore)
            minScore = roundResult;
        //Output the game stats at the end of each round (each number has precision of 2 decimal places)
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << static_cast<double>(avgTotal)/i << ", ";
        cout << "minimum: " << minScore << ", ";
        cout << "maximum: " << maxScore << endl;
    }

}

int playOneRound(const char words[][MAXWORDLENGTH + 1], int nWords, int wordnum)
{
    
    //If the number of words is negative or if the index is out of the bounds of the array, return -1
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
        return -1;

    //The mystery word is a word of max length 6 (plus 1 for the 0 byte) which is at index wordnum in words
    char mystWord[MAXWORDLENGTH + 1];
    strcpy(mystWord, words[wordnum]);

    //trialWord is a C string of max length 100 letters
    char trialWord[MAXTRIALLENGTH + 1] = {'\0'};
    int numTries = 1;

    //Infinite loop which will be broken out of when trialWord is equal to mystWord (user guesses correctly)
    for (;;)
    {
        //Prompt user for trial word and store it
        cout << "Trial word: ";
        cin.getline(trialWord, MAXTRIALLENGTH + 1);

        //Check whether the word is valid and print an error message depending on what is wrong with it
        int isValidWordResult = isValidWord(trialWord, words, nWords);

        if (isValidWordResult == 1)
        {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        else if (isValidWordResult == 2)
        {
            cout << "I don't know that word." << endl;
            continue;
        }
        else if (strcmp(trialWord, mystWord) == 0)
        {
            //If the trialWord is the same as the mystWord, break from the loop
            break;
        }
        else
        {
            //If there is no error and the user has not guessed correctly, count and print the number of
            //flowers and bees in the guess and increment num tries
            countFlowersBees(trialWord, mystWord);
            numTries++;
        }
        
    }

    //Return the number of tries it took to guess the word
    return numTries;
}

int isValidWord(const char word[], const char wordList[][MAXWORDLENGTH + 1], int numWords)
{
    //Return error code 1 if the word is not between 4 and 6 letters
    if (strlen(word) < 4 || strlen(word) > 6)
        return 1;

    //Return error code 1 if the characters in the string are not all lowercase letters
    for (int j = 0; j < strlen(word); j++)
    {
        if (!(isalpha(word[j])) || !(islower(word[j])))
            return 1;
    }

    //Return normal code 0 if the word is found in the list of words
    for (int i = 0; i < numWords; i++)
    {
        if (strcmp(word, wordList[i]) == 0)
            return 0;
    }

    //Return 2 because if the function has not already returned 0, then the word is not in the word list array
    return 2;
}

void countFlowersBees(char trial[], char word[])
{
    int numBees = 0;
    int numFlowers = 0;
    
    //Create copies of the mystery and trial words that can be altered without changing the original
    char wordCopy[MAXWORDLENGTH + 1];
    strcpy(wordCopy, word);
    char trialCopy[MAXTRIALLENGTH + 1];
    strcpy(trialCopy, trial);
      
    //Set length variable to the length of the smaller word
    int length;
    if (strlen(trial) < strlen(word))
        length = strlen(trial);
        
    length = strlen(word);
        
    //Loop through each letter in both words for number of times equal to length of smaller word
    //so the loop does not access a position outside the array if one word is bigger than the other
    for (int i = 0; i < length; i++)
    {
        //If the letters at corresponding positions in the trial and mystery word match, increment numFlowers
        if (trialCopy[i] == wordCopy[i])
        {
            numFlowers++;
            //Set the character in each word to space so it is easy to identify that they have already
            //been assigned later and they do not get reassigned
            trialCopy[i] = ' ';
            wordCopy[i] = ' ';
        }
    }
    
    //After finding all the flowers, find the bees
    for (int k = 0; k < strlen(trial); k++)
    {
        for (int j = 0; j < strlen(word); j++)
        {
            //If the letter in the trial word is equal to a letter in the mystery word and they are not space
            //characters (meaning they were already assigned) then increment numBees
            if (trialCopy[k] == wordCopy[j] && trialCopy[k] != ' ')
            {
                numBees++;
                //Set the letter in each word to space char so they are not reassigned later
                trialCopy[k] = ' ';
                wordCopy[j] = ' ';
                //Break from the inner loop to go to the next iteration of the outer loop
                //so that the letter in trial word is not matched with any other letter in the mystery word
                break;
            }
        }
    }
    
    //Print out the number of flowers and bees int the word
    cout << "Flowers: " << numFlowers << ", Bees: " << numBees << endl;
}

