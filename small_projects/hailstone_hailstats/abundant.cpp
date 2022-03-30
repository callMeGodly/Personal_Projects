#include <iostream>
using namespace std;

int main()
{
  unsigned int n1 = 0, n2 = 0, n3 = 0;
  int a1 = 0, a2 = 0, a3 = 0;

  int num_abundant = 0;

  cout << "Enter a sequence of natural numbers, separated by spaces, ";
  cout << "and ending with 0."<< endl;

  while(true){
    int count = 0;
    bool isAbundant = false;
    int inp; cin >> inp;
    if(inp == 0){
      break;
    }
    
    for(int i = 1; i < inp; i++){
      if(inp % i == 0){
        count += i;
      }
    }
    
    if(count > inp){
      num_abundant++;
      isAbundant = true;
    }
    
    if(isAbundant){
      if(count > a1){
        a3 = a2;
        n3 = n2;
        a2 = a1;
        n2 = n1;
        a1 = count;
        n1 = inp;
      }
      else if(count > a2){
        a3 = a2;
        n3 = n2;
        a2 = count;
        n2 = inp;
      }
      else if(count > a3){
        a3 = count;
        n3 = inp;
      }
    }
  }
  
  cout << "Abundant number count: " << num_abundant << endl;
  cout << "Top 3 most abundant numbers: " << endl;
  cout << n1 << " : " << a1 << endl;
  cout << n2 << " : " << a2 << endl;
  cout << n3 << " : " << a3 << endl;


  return 0;

}
