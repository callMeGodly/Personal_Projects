#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{

   AVLTree<int,int> at;
   at.insert(std::make_pair(20,2));
   at.insert(std::make_pair(4,1));
   at.insert(std::make_pair(26,3));
//    at.insert(std::make_pair(21,3));
//    at.insert(std::make_pair(30,3));
   at.insert(std::make_pair(3,3));
   at.insert(std::make_pair(9,3));
//    at.insert(std::make_pair(2,3));
//    at.insert(std::make_pair(7,3));
//    at.insert(std::make_pair(11,3));
   at.insert(std::make_pair(8,3));

   cout << "\nAVLTree contents:" << endl;
   for(AVLTree<int,int>::iterator it = at.begin(); it != at.end(); ++it) {
       cout << it->first << " " << it->second << endl;
   }
//    if(at.find('b') != at.end()) {
//        cout << "Found b" << endl;
//    }
//    else {
//        cout << "Did not find b" << endl;
//    }
//    cout << "Erasing b" << endl;
//    at.remove('b');

    return 0;
}
