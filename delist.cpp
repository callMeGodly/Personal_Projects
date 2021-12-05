#include <iostream>
#include "delist.h"

DEItem::DEItem(int v){
  val = v;
  next = NULL;
  prev = NULL;
}

DEList::DEList(){
  head = NULL;
  tail = NULL;
}

DEList::~DEList(){
  while(!empty()){
    pop_front();
  }
}

bool DEList::empty(){
  return head == NULL;
}

int DEList::size(){
  int count = 0;
  DEItem* temp = head;
  while(temp != NULL){
    temp = temp -> next;
    ++count;
  }
  return count;
}

int DEList::front(){
  if(empty()){
    return -1;
  }
  return head -> val;
}

int DEList::back(){
  if(empty()){
    return -1;
  }
  
  DEItem* temp = tail;  
  return temp -> val;
}

void DEList::push_front(int new_val){
  DEItem* newItem = new DEItem(new_val);
  newItem -> next = head;
  if (head != NULL){
    head->prev = newItem;
  }
  if(head == NULL){
    tail = newItem;
  }
  head = newItem;
}

void DEList::push_back(int new_val){
  if(empty()){
    push_front(new_val);
  }
  else{
    DEItem* newItem = new DEItem(new_val);
    DEItem* temp = tail;
    newItem -> prev = temp;
    newItem -> next = NULL;
    temp -> next = newItem;
    tail = newItem;
  }
}

void DEList::pop_front(){
  if(!empty()){
    DEItem* temp = head;
    if(head == tail){
      tail = NULL;
    }
    else if(head != NULL){
      DEItem* temp2 = head -> next;
      temp2 -> prev = NULL;
    }
    head = head -> next;
    delete temp;
  }
}

void DEList::pop_back(){
  if(!empty()){
    DEItem* temp = tail;
    if(head == tail or head == NULL){
      pop_front();
    }
    else{
      DEItem* temp2 = temp -> prev;
      temp2 -> next = NULL;
      tail = temp2;
      delete temp;
    }
  }
}
