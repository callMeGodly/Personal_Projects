#include <iostream>
#include "heap.h"
using namespace std;

int main(){
    
    Heap<int> h(4);
    
    vector<int> t = {220, 219, 449, 447, 241, 383, 115, 331, 477, 211, 169, 352,
        324, 322, 420, 447, 455, 108, 500, 274, 162, 157, 101, 473, 433, 218, 402, 296, 390, 433, 267, 242,
        389, 89, 304, 98, 343, 122, 133, 495, 277, 497, 383, 30, 85, 356, 467, 387, 424, 367};
    for(size_t i = 0; i < t.size(); ++i){
        h.push(t[i]);
    }
    
    for(size_t i = 0; i < t.size(); ++i){
        cout << h.top() << endl;
        h.pop();
    }

    return 0;
}
