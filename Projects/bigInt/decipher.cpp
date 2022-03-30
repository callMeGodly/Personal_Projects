#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/
  
  int base;
  string output;
  string secret_code;
  string d;
  string n;
  ifstream myfile(argv[1]);
  if(myfile.is_open()){
    myfile >> base;
    myfile >> d;
    myfile >> n;
  }
  
  try{
    BigInt test(d, base);
  }
  catch(const exception& e){
    cout<<e.what()<<endl;
    return -1;
  }
  BigInt dod(d, base);
  BigInt mod(n, base);
  BigInt result(base);
  
  try{
    if(n == "0"){
      dod /= mod;
    }
  }
  catch(const exception& e){
    cout<<e.what()<<endl;
    return -1;
  }
  
  try{
    BigInt test(1, base);
    test.modulusExp(dod, mod);
  }
  catch(const exception& e){
    cout<<e.what()<<endl;
    return -1;
  }
  
  while(getline(myfile, secret_code)){
    BigInt sc(secret_code, base);
    result = modPow(sc,dod,mod);
    int decode = result.to_int();
    output += (char)decode;
  }
  cout << output << endl;
	return 0;
}
