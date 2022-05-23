#include <iostream>
#include "stack.h"
using namespace std;

int main(){
    
    Stack<int> s;
    for(int i = 0 ; i < 100; ++i){
        s.push(i);
    }
    for(int i = 0; i < 101; ++i){
        try{
            cout << s.top() << endl;
        }
        catch(const std::underflow_error& e){
            cout << e.what() << endl;
        }
        cout << s.size() << endl;
        try{
            s.pop();
        }
        catch(const std::underflow_error& e){
            cout << e.what() << endl;
        }
    }
    cout << s.size() << endl;
    try{
        s.pop();
    }
    catch(const std::underflow_error& e){
        cout << e.what() << endl;
    }
    
    
    return 0;
}
