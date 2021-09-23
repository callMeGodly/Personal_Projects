#include <iostream>

using namespace std;

void solve(){
  
  cout << "Enter the range that you want to search: ";
 
  int n; int m; cin >> n >> m;
  if(n > m){
    cout << "Invalid range" << endl;
    return;
  }
  
  int min, max, minp, maxp;
  bool first = true;
  for(int i = n; i <= m; i++){
    int count = 0;
    int test = i;
    while(test != 1){
      if(test % 2 == 0){
        test /= 2;
      }
      else{
        test = test*3 + 1;
      }
      count++;
    }
    
    if (first){
      max = count;
      min = count;
      minp = i;
      maxp = i;
      first = false;
    }

    if(count > max){
      max = count;
      maxp = i;
    }
    else if(count < min){
      min = count;
      minp = i;
    }
  }
  
  cout << "Minimum length: " << min << endl;
  cout << "Achieved by: " << minp << endl;
  cout << "Maximum length: " << max << endl;
  cout << "Achieved by: " << maxp << endl;
}


int main(){
  
  solve();
  return 0;
}
