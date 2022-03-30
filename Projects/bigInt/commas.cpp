#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  long long n;
  cout << "Enter an integer:" << endl;
  cin >> n;
  
  long long count = 0;
  if(n < 0){
    n *= -1;
    cout << "-";
  }
  while(n % (long long)pow(10, count) != n){
    count++;
  }
  
  if(count == 0){
    cout << n << endl;
    return 0;
  }
  
  for(int i = count - 1; i >= 0 ; i--){
    
    long long current = (long long)pow(10, i);
    cout << (n - (n % current))/(current);
    n = n % current;
    if(i % 3 == 0 and i != 0){
      cout << ",";
    }
  }
  
  cout << endl;
  
  return 0;
}
