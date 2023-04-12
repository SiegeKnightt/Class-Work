/*
 * Name: Reeves Farrell
 * Date Submitted:
 * Lab Section: 005
 * Assignment Name: Lab 1: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){

  mySize = 0;
  start = nullptr;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){

  // Creates a start node
  Node<T> *n = start;

  // Loops through the entire list
  // Deletes each node until n = nullptr (end of list)
  while (n != nullptr) {

    n = n->next;

    delete n;

    n = start;

    delete start; 
  }
}

//Return the size of this list
template <class T>
int List<T>::size(){

  // Initilizes the size of the list
  mySize = 0;

  Node<T> *n = start;

  // Counts each node in the list
  while (n != nullptr) {

    ++mySize;
    n = n->next;
  }

  return mySize;
 }

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){

  // Returns true if start != nullptr
  // else it returns false
  if (start == nullptr) {

    return true;
  }
  else {

    return false;
  }
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){

  // Creates a new node with value
  // and sets the value of the node
  Node<T> *n = new Node<T>(value);
  n->value = value;

  // Points the node to the next node
  n->next = start;

  // start now points to the new node
  start = n;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){

  // Create a new node with a value
  Node<T> *n = new Node<T>(value);
  n->value = value;

  if (start == nullptr) {

    start = n;
  }
  else {

    // Creates a second node
    Node<T> *n2 = start;

    // Loops until node 2 is before
    // the nullptr (the final node)
    while (n2->next != nullptr) {

      n2 = n2->next;
    }

    // Adds the new node to the end of the list
    n2->next = n;
  }
}

//Create a new node with value <value>, and insert that new node at position j
// 0 = start of the list
template <class T>
void List<T>::insertAt(T value, int j){

  // Creates a new node = to the start of the list
  Node<T> *n = start;
  Node<T> *n2;

  // Counter variable
  int count = 0;

  // Creates a third node with the value input
  // Assigns value to the node
  Node<T> *n3 = new Node<T>(value);
  n3->value = value;

  // Loops to find the node at position j
  while (j > count && n->next != nullptr) {

    n2 = n;

    n = n->next;

    ++count;
  }

  if (n == start) {

    // Sets the next position of the 3rd
    // node to start
    n3->next = start;

    // Makes node 3 the head of the list
    start = n3;
  }
  else {

    // Sets the node next to n2
    // equal to n3
    n2->next = n3;

    // Sets the node next to n3
    // equal to n
    n3->next = n;
  }
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){

  // Creates a new node equal to start
  Node<T> *n = start;

  // Removes the starting node
  // if start != nullptr
  if (start != nullptr) {

    start = start->next;

    delete n;
  }
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){

  // Creates a node equal to the
  // start of the list
  Node<T> *n = start;

  // Loops until the node is before
  // the nullptr (the final node)
  while (n->next->next != nullptr) {

    n = n->next;

  }

  // Deletes the second to last node
  delete n->next;
  n->next = nullptr;
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){

  // Creates a new node equal to start
  Node<T> *n = start;

  // Counter variable
  int count = 0;

  // Loops to find the node at position j
  while (j > count && n->next != nullptr) {

    n = n->next;

    ++count;
  }

  // Removes the node at position j
  delete n;
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){

  // Returns nullptr if the first node doesn't exist
  if (start == nullptr) {

    return T();
  }
  else {
  
    // Returns the value of the first node
    return start->value;
  }
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){

  // Returns T() if no first node exists
  if (start == nullptr) {

    return T();
  }

  // Makes a node equal to the start of the list
  Node<T> *n = start;

  // Loops until the node is before
  // the nullptr (the final node)
  while (n->next != nullptr) {

    n = n->next;
  }

  // Returns the value of the last node
  return n->value;
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){

  // Creates a new node equal to start
  Node<T> *n = start;

  // Counter variable
  int count = 0;

  // Loops to find the node at position j
  while (j > count && n->next != nullptr) {

    n = n->next;

    ++count;
  }

  // Returns the node at position j
  return n->value;
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){

  // Creates a new node = to the start of the list
  Node<T> *n = start;

  // Creates a count variable
  int count = 0;

  // While the node is not the nullptr
  // and the node doesn't equal the key
  // loop to find the correct node
  while (n != nullptr) {

    if (n->value == key) {

      // Returns count if correct node is found
      return count;
    }
    // Goes to the next node
    n = n->next;

    // Increments the count
    ++count;
  }

  // Returns -1 if key not found in the list
  return -1;
}