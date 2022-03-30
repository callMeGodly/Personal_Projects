#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

void shuffle(int cards[])
{
  for(int i = NUM_CARDS-1; i >= 1; --i){
    int swap = rand() % (i+1);
    int temp = cards[swap];
    cards[swap] = cards[i];
    cards[i] = temp;
  }
}

void printCard(int id)
{
  char sign = suit[(int)floor(id/13.0)];
  cout << type[id%13] << "-" << sign;
}

int cardValue(int id)
{
  return value[id%13];

}

void printHand(int hand[], int numCards)
{
  for(int i = 0; i < numCards; ++i){
     printCard(hand[i]);
     cout << " ";
  }


}

int getBestScore(int hand[], int numCards)
{
  int s = 0;
  for(int i = 0; i <= numCards; ++i){
    s += value[hand[i] % 13];
  }
  if(s > 21){
    for(int i = 0; i <= numCards; ++i){
      if(value[hand[i] % 13] == 11){
        s -= 10;
        if(s == 21){
          break;
        }
      }
    }
  }
  
  return s;
    
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);
  int cards[52];
  int dhand[9];
  int phand[9];
  while(true){
    for(int i = 0; i <52; ++i){
      cards[i] = i;
    }
    shuffle(cards);
    int current = 0;
    int dealer_current = 1;
    phand[0] = cards[current]; phand[1] = cards[current + 2];
    dhand[0] = cards[current + 1]; dhand[1] = cards[current + 3];
    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: ";
    printCard(phand[0]);
    cout << " ";
    printCard(phand[1]);
    cout << endl;
    
    if(getBestScore(phand, 1) == 21){
      while(getBestScore(dhand, current + 1) < 17){
        ++current;
        dhand[current + 1] = cards[current + 3];
        if(getBestScore(dhand, current+1) > 21){
          break;
        }
        else if(getBestScore(dhand, current+1) == 21){
          cout << "Tie 21 21" << endl;
          cout << endl << endl;
          cout << "Play again? [y/n]" << endl;
          char go; cin >> go;
          if(go == 'n'){
            return 0;
          }
          else{
            break;
          }
        }
      }
      cout << "Dealer: ";
      printHand(dhand, current + 2);
      cout << endl;
      cout << "Win 21 ";
      cout << getBestScore(dhand, current + 1);
      cout << endl << endl;
      cout << "Play again? [y/n]" << endl;
      char go; cin >> go;
      if(go == 'n'){
        return 0;
      }
      else{
        break;
      }
    }
    else{
      current += 3;
      while(true){
        cout << "Type 'h' to hit and 's' to stay:" << endl;
        char cmd; cin >> cmd;
        if(cmd == 'h'){
          ++current;
          phand[current-2] = cards[current];
          cout << "Player: ";
          printHand(phand, current - 1);
          cout << endl;
          if(getBestScore(phand, current - 2) > 21){
            cout << "Player busts" << endl;
            cout << "Lose " << getBestScore(phand, current-2) << " " << getBestScore(dhand, dealer_current);
            cout << endl << endl;
            cout << "Play again? [y/n]" << endl;
            char go; cin >> go;
            if(go == 'n'){
              return 0;
            }
            else{
              break;
            }
          }
          if(getBestScore(phand, current - 2) == 21){
            int pscore = getBestScore(phand, current - 2);
            while(getBestScore(dhand, dealer_current) < 17){
              ++dealer_current;
              ++current;
              dhand[dealer_current] = cards[current];
            }
            int dscore = getBestScore(dhand, dealer_current);
            if(dscore > pscore){
              cout << "Dealer: ";
              printHand(dhand, dealer_current+1);
              cout << endl << "Lose " << pscore << " " << dscore;
            }
            else if(dscore == pscore){
              cout << "Dealer: ";
              printHand(dhand, dealer_current+1);
              cout << endl << "Tie " << dscore << " " << dscore;
            }
            else{
              cout << "Dealer: ";
              printHand(dhand, dealer_current+1);
              cout << endl << "Win " << pscore << " " << dscore;
            }
            cout << endl << endl;
            cout << "Play again? [y/n]" << endl;
            char go; cin >> go;
            if(go == 'n'){
              return 0;
            }
            else{
              break;
            }
          }
        }
        else{
          int pscore = getBestScore(phand, current - 2);
          while(getBestScore(dhand, dealer_current) < 17){
            ++dealer_current;
            ++current;
            dhand[dealer_current] = cards[current];
          }
          int dscore = getBestScore(dhand, dealer_current);
          cout << "Dealer: " << endl;;
          printHand(dhand, dealer_current+1);
          cout << endl;
          if(dscore > 21){
            cout << "Dealer busts";
          }
          if(dscore > pscore and dscore <= 21){
            cout << endl << "Lose " << pscore << " " << dscore;
          }
          else if(dscore == pscore){
            cout << endl << "Tie " << dscore << " " << dscore;
          }
          else{
            cout << endl << "Win " << pscore << " " << dscore;
          }
          cout << endl << endl;
          cout << "Play again? [y/n]" << endl;
          char go; cin >> go;
          if(go == 'n'){
            return 0;
          }
          else{
            break;
          }
        }
      }
    }
  }
  return 0;
}
