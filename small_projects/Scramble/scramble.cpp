// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

void permute(char items[], int len);

int main(int argc, char* argv[]) {
  srand(time(0));
  char guess[80];
  string w;
  
  if(argc <= 1){
    cout << "Not enough arguments" << endl;
    return 1;
  }
  ifstream myfile;
  myfile.open(argv[1]);
  if (myfile.fail()){
    cout << "Unable to open file";
    return 1;
  }
  int numWords; myfile >> numWords;
  string wordBank[numWords];

  bool wordGuessed = false;
  int numTurns = 10;
  
  /* Add code to declare the wordBank array, read in each word
     and store it */
  int numWords; myfile >> numWords;
  string wordBank[numWords];
  for(int i = 0; i < numWords; ++i){
    //not copying over strings correctly into array
    myfile >> w;
    wordBank[i] = w;
  }
  
  myfile.close();
  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = wordBank[target].length();

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target].c_str());
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    /* Complete the next line of code */
    if(guess == wordBank[target]){
      wordGuessed = true;
    }  
   // ADD code to check if the guess is equal to the chosen word.
   // wordGuessed should be true if they are equal, and false otherwise
        
    numTurns--;   // Every guess counts as a turn
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  /* Free up any necessary memory */
    
  delete [] word;
  
  return 0;
}

// Scramble the letters. See "Knuth shuffle".
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}
