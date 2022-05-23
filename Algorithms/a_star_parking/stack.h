#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>
#include <iostream>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

//   constructor
template <typename T>
Stack<T>::Stack(){
}

//  destructor
template <typename T>
Stack<T>::~Stack(){
    
}

//  if heap is empty returns true else false
template <typename T>
bool Stack<T>::empty() const{
    return std::vector<T>::empty();
}

//  returns the size of the stack as unsigned int
template <typename T>
size_t Stack<T>::size() const{
    return std::vector<T>::size();
}

//  pushes item to the back of the stack
template <typename T>
void Stack<T>::push(const T& item){
    this->push_back(item);
}

//  removes the last element in the stack
template <typename T>
void Stack<T>::pop(){
    if(empty()) throw std::underflow_error("stack is empty");
    this->pop_back();
}

//  returns the first element in the stack
template <typename T>
const T& Stack<T>::top() const{
    
    if(empty()) throw std::underflow_error("stack is empty");
    return this->back();
}


#endif
