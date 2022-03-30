#include "bigint.h"

BigInt::BigInt(string s){
  for(int i = s.length() - 1; i >= 0; --i){
    representation.push_back(s[i] - '0');
  }
}

string BigInt::to_string(){
  
  string output;
  for(int i = representation.size() - 1; i >= 0; --i){
    output += (char)('0' + representation[i]);
  }
  return output;
}

void BigInt::add(BigInt b){
  int carry = 0;
  if(b.representation.size() < representation.size()){
    for(int i = 0; i < representation.size() - b.representation.size(); ++i){
      b.representation.push_back(0);
    }
  }
  for(int i = 0; i < b.representation.size(); ++i){
    int check = representation[i] + b.representation[i];
    if(check + carry >= 10){
      representation[i] = carry + check - 10;
      carry = 1;
    }
    else{
      representation[i] = carry + check;
      carry = 0;
    }
  }
  if(carry){
    representation.push_back(1);
  }
}
