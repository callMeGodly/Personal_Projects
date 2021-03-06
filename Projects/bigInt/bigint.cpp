#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    
    if(input < 0){
      isPositive = false;
      input *= -1;
    }
    else{
      isPositive = true;
    }
    base = setbase;
    if(input == 0){
      vec.push_back(0);
    }
    else{
      while(input > 0){
        vec.push_back(input % setbase);
        input/=setbase;
      }
    }
}

BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    int i = 0;
    if(s[0] == '-'){
       isPositive = false;
       i = 1;
    }
    else{
       isPositive = true;
    }
    base = setbase;
    for(int j = s.length() - 1; j >= i; --j){
      if((int)s[j] >= 65){
        vec.push_back((int)s[j] - 55);
      }
      else{
        vec.push_back((int)s[j] - 48);
      }
    }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
    vec = b.vec;
    base = b.base;
    isPositive = b.isPositive;
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  Overriding a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/
    base = b.base;
    vec = b.vec;
    isPositive = b.isPositive;
    return *this;
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    string output = "";
  
    if(!isPositive){
      output += '-';
    }
  
    for(int i = vec.size()-1; i >= 0; --i){
      if(vec[i] > 9){
        output += (char)(vec[i]+55);
      }
      else{
        output += (char)(vec[i]+48);
      }
    }
    return output;
}

int BigInt::to_int() const{

    /************* You complete *************/
    int output = 0;
    for(unsigned int i = 0; i < vec.size(); ++i){
        if(isPositive){
          if(output + pow((double)base, (double)i)*vec[i] >= INT_MAX){
            return INT_MAX;
          }
          else{
            output += pow((double)base, (double)i)*vec[i];
          }
        }
        else{
          if(output - pow((double)base, (double)i)*vec[i] <= INT_MIN){
            return INT_MIN;
          }
          else{
            output -= pow((double)base, (double)i)*vec[i];
          }
        }
    }
  return output;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************


int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    
    if(isPositive != b.isPositive){
      if(isPositive){
        return 1;
      }
      else{
        return -1;
      }
    }
    else if(vec.size() > b.vec.size()){
      if(isPositive){
        return 1;
      }
      else{
        return -1;
      }
    }
    else if(vec.size() < b.vec.size()){
      if(isPositive){
        return -1;
      }
      else{
        return 1;
      }
    }
    else{
       for(int i = vec.size() - 1; i >= 0; --i){
         if(vec[i] > b.vec[i]){
           if(isPositive){
             return 1;
           }
           else{
             return -1;
           }
         }
         else if(vec[i] < b.vec[i]){
           if(isPositive){
             return -1;
           }
           else{
             return 1;
           }
         }
       }
    }
    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    if(!a.compare(b)){
      return true;
    }
  return false;
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  

    if(a.compare(b)){
      return true;
    }
  return false;
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  

    if(!a.compare(b) || (a.compare(b) == -1)){
      return true;
    }
  return false;
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  

    if(!a.compare(b) || (a.compare(b) == 1)){
      return true;
    }
  return false;
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    if(a.compare(b) == 1){
      return true;
    }
  return false;
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    if(a.compare(b) == -1){
      return true;
    } 
  return false;
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt test(a);
  test += b;
  return test;
}


const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
  
  int value_of_a = 0;
  int value_of_b = 0;
  int max = b.base;
  unsigned int s = 0;
  int carry = 0;
  bool pass = true;
  bool barrel = false;
  bool side = false;
  vector <int> output;
  if(vec.size() > b.vec.size()) s = vec.size();
  else s = b.vec.size();
  
  for(unsigned int i = 0; i < s; ++i){
    if(i < vec.size()) value_of_a = vec[i];
    else value_of_a = 0;
    if(i < b.vec.size()) value_of_b= b.vec[i]; 
    else value_of_b = 0;
    
    if(isPositive == b.isPositive){
      int check = value_of_a + value_of_b;
      if(check + carry >= max){
        output.push_back(carry + check - max);
        carry = 1;
      }
      else{
        output.push_back(carry + check);
        carry = 0;
      }
    }
    else{
      if(pass){
        pass = false;
        if(isPositive) isPositive = false;
        else isPositive = true;

        if(*this == b){
          output.push_back(0);
          isPositive = true;
          break;
        }
        else if(*this > b){
          if(!isPositive){
            side = true;
          }
        }
        else if(*this < b){
          if(isPositive && b.isPositive){
            side = true;
          }
        }
        if(isPositive) isPositive = false;
        else isPositive = true;
      }
      int check = 0;
      if(side) check = value_of_b - value_of_a - barrel;
      else check = value_of_a - value_of_b - barrel;
      
      if(check < 0){
        output.push_back(check + base);
        barrel = true;
      }
      else{
        output.push_back(check);
        barrel = false;
      }
    }
  }
  if(!pass && side){
    if(b.isPositive) isPositive = true;
    else isPositive = false;
  }
  if(carry) output.push_back(1);
  int j = 1;
  int scale = output.size();
  while(output[scale-j] == 0 && output.size() > 1){
    output.pop_back();
    ++j;
  }
  vec = output;
  return *this;
}

BigInt operator - (const  BigInt &a, const BigInt & b){

  BigInt test(a);
  test -= b;
  return test;
}

const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }

    int value_of_a = 0;
    int value_of_b = 0;
    bool side = false;
    bool barrel = false;
    vector <int> output;
    
    if(*this == b){
      output.push_back(0);
      vec = output;
      isPositive = true;
      return *this;
    }
    else if(isPositive && b.isPositive){
      if(*this < b){
        side = true;
      }
    }
    else if(isPositive && !b.isPositive){
      isPositive = false;
      *this += b;
      isPositive = true;
      return *this;
    }
    else if(!isPositive && !b.isPositive){
      if(*this > b){
        side = true;
      }
    }
    else{
      isPositive = true;
      *this += b;
      isPositive = false;
      return *this;
    }
  
  unsigned int s = 0;
  if(vec.size() > b.vec.size()) s = vec.size();
  else s = b.vec.size();
  for(unsigned int i = 0; i < s; ++i){
    if(i < vec.size()) value_of_a = vec[i];
    else value_of_a = 0;
    if(i < b.vec.size()) value_of_b= b.vec[i]; 
    else value_of_b = 0;
    
    int check = 0;
    if(side) check = value_of_b - value_of_a - barrel;
    else check = value_of_a - value_of_b - barrel;
    if(check < 0){
      output.push_back(check + base);
      barrel = true;
    }
    else{
      output.push_back(check);
      barrel = false;
    }
  }
  int j = 1;
  int scale = output.size();
  while(output[scale-j] == 0 && output.size() > 1){
    output.pop_back();
    ++j;
  }
  if(side) isPositive = false;
  if(side && !isPositive && !b.isPositive) isPositive = true;
  vec = output;
  return *this;
}

BigInt operator * (const  BigInt &a, const BigInt & b){

    BigInt test(a);
    test *= b;
    return test;
}

const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    BigInt total(0, base);
    vector <int> output;
    if(vec.size() == 1 && vec[0] == 0){
      vec.clear();
      vec.push_back(0);
      isPositive = true;
      return *this;
    }
    else if(b.vec.size() == 1 && b.vec[0] == 0){
      vec.clear();
      vec.push_back(0);
      isPositive = true;
      return *this;
    }
    
    int carry = 0;
    for(unsigned int i = 0; i < b.vec.size(); ++i){
      BigInt temp(b.base);
      for(unsigned int k = 0; k < i; ++k) temp.vec.push_back(0);
      for(unsigned int j = 0; j < vec.size(); ++j){
        int check = b.vec[i] * vec[j] + carry;
        if(check >= base) carry = check/base;
        else carry = 0;
        temp.vec.push_back(check - carry*base);
      }
      if(carry) temp.vec.push_back(carry);
      carry = 0;
      total += temp;
    }
    
    if(isPositive != b.isPositive) total.isPositive = false;    
    *this = total;
    return *this;
}

BigInt operator / (const  BigInt &a, const BigInt & b){

    BigInt test(a);
    test /= b;
    return test;
}

const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }

    bool reverse = false;
    BigInt divisor(b);
    vector <int> output;
    if(*this == b){
      vec.clear();
      vec.push_back(1);
      if(isPositive != b.isPositive) isPositive = false;
      else isPositive = true;
      return *this;
    }
    else if(b.vec.size() == 1 && b.vec[0] == 1){
      if(isPositive != b.isPositive) isPositive = false;
      else isPositive = true;
      return *this;
    }
    else if(vec.size() == 1 && vec[0] == 0){
      vec.clear();
      vec.push_back(0);
      return *this;
    }
    divisor.isPositive = true;
    if(isPositive != b.isPositive){
      reverse = true;
      isPositive = true;
    }
    if(!isPositive) isPositive = true;
    if(divisor > *this){
      vec.clear();
      isPositive = true;
      vec.push_back(0);
      return *this;
    }
    
    int sz = vec.size()-1;
    int pos = sz;
    BigInt dividend_seq(vec[pos], base);
    while(dividend_seq < divisor && pos > 0){
        pos--;
        dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos]);
    }
    while(pos >= 0){
      int times = 0;
      while(dividend_seq >= divisor){
        dividend_seq -= divisor;
        ++times;
      }
      output.insert(output.begin(), times);
      if(dividend_seq.vec.size() == 1 && dividend_seq.vec[0] == 0){
        dividend_seq.vec.clear();
      }
      if(pos > 0) dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos-1]);
      --pos;
    }
    if(reverse) isPositive = false;
    vec = output;
    return *this;
}

BigInt operator % (const  BigInt &a, const BigInt & b){

    BigInt test(a);
    test %= b;
    return test;
}

const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }

    bool reverse = false;
    BigInt divisor(b);
    vector <int> output;
    if(*this == b){
      vec.clear();
      vec.push_back(0);
      isPositive = true;
      return *this;
    }
    else if(b.vec.size() == 1 && b.vec[0] == 1){
      vec.clear();
      vec.push_back(0);
      isPositive = true;
      return *this;
    }
    else if(vec.size() == 1 && vec[0] == 0){
      vec.clear();
      vec.push_back(0);
      isPositive = true;
      return *this;
    }
    divisor.isPositive = true;
    if(!isPositive){
      reverse = true;
      isPositive = true;
    }
    if(divisor > *this){
      if(reverse) isPositive = false;
      return *this;
    }
    
    int sz = vec.size()-1;
    int pos = sz;
    BigInt dividend_seq(vec[pos], base);
    while(dividend_seq < divisor && pos > 0){
        pos--;
        dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos]);
    }
    while(pos >= 0){
      int times = 0;
      while(dividend_seq >= divisor){
        dividend_seq -= divisor;
        ++times;
      }
      output.insert(output.begin(), times);
      if(dividend_seq.vec.size() == 1 && dividend_seq.vec[0] == 0){
        dividend_seq.vec.clear();
      }
      if(pos > 0) dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos-1]);
      --pos;
    }
    if(reverse) isPositive = false;
    if(dividend_seq.vec.empty()){
      vec.clear();
      vec.push_back(0);
      isPositive = true;
    }
    else{
      vec = dividend_seq.vec;
    }
    return *this;
}

void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

}

BigInt pow(const  BigInt &a, const BigInt & b){

    BigInt test(a);
    test.exponentiation(b);
    return test;//for now
}

const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }

    BigInt d(2, base);
    BigInt full(0, base);
    BigInt x(*this);
    if(b.vec.size() == 1 && b.vec[0] == 0){
      vec.clear();
      vec.push_back(1);
      isPositive = true;
      return *this;
    }
    int time = b.to_int()-1;
    for(int i = 0; i < time; ++i) *this *= x;
    return *this;
}

BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    BigInt test(a);
    test.modulusExp(b, m);
    return test;
}

const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }

    BigInt n(b);
    BigInt d(2, base);
    BigInt minus(1, base);
    BigInt test(0, base);
    BigInt result(1, base);
    if(vec.size() == 1 && vec[0] == 0){
      vec.clear();
      vec.push_back(0);
      return *this;
    }
    while(!(n.vec.size() == 1 && n.vec[0] == 1)){
      if(n % d == test){
        *this *= *this;
        n /= d;
        *this %= m;
      }
      else{
        n -= minus;
        result *= *this;
      }
    }
    *this *= result;
    *this %= m;
    return *this;
}
