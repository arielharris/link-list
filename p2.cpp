// Ariel Harris
// Programming Assingment 2
// Purpose: Create an organized linked list and print it to a text file. Then,
// delete three values and re-print the list.
// Input: No input
// Process: Randomly generate numbers for the link list, use the insert function
// to organize in ascending order using an insert function. Using a delete
// fucntion, find and delete the lowest & highest values as well as some value
// in the middle. Print the origianl list as well as the list after deleting
// using a print function.  
// Output: Two text files, one with original list and one after deletion

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

struct Node
{
  int data;
  Node* next;
};

void printList(Node* list, ostream& outs);
//prints data values
//pre: none
//post: none

void insertNode(Node*& list, Node*& tail, int val);
//instert node in none descending order
//pre: on first call, list is nullptr
//post: list is updated to contain organized (l-h) values

void delNode(Node*& list, int val);
//deletes a node containing val from list
//pre: none
//post: list is updated

int main()
{
  const int listSize = 50;
  const int max = 100;
  const string outOne = "P2OutputA.txt";
  const string outTwo = "P2OutputB.txt";
  Node* head = nullptr; //keep track of front of list
  Node* tail = nullptr; //keep track of end of list
  Node* delPtr = nullptr;
  ofstream outfile;
  srand(time(0));
  int in = 0;
  int low = 0;
  int high = 0;
  int mid = 0;

  cout << "Welcome to programing assingment two!" << endl;

  //create linked list filled with random values & organized (l-h)
  cout << "Now filling linked list" << endl;
  for (int i = 0; i < listSize; i++){
    in = rand() % max;
    insertNode(head, tail, in);
    if( in > 10 && in < 90){ //some number in middle of list stored
      mid = in; 
    }
  }

  //print the orginal list to txt file
  cout << "Now printing to first output file" << endl;
  outfile.open(outOne);
  printList(head, outfile);
  outfile.close();

  //find lowest & highest values
  low = head->data;
  high = tail->data;

  //delete low, mid, high
  delNode(head, low);
  cout << "Now deleting the lowest value" << endl;
  delNode(head, mid);
  cout << "Now deleting a middle value" << endl;
  delNode(head, high);
  cout << "Now deleting the highest value" << endl;

  //print updated list to txt file
  cout << "Now printing to second output file" << endl;
  outfile.open(outTwo);
  printList(head, outfile);
  outfile.close();

  //deallocate memory
  while (head != nullptr){
    delPtr = head;
    head = head->next;
    delete delPtr;
  }
  cout << "Memory deallocated" << endl;

  cout << "Thank you, goodbye!" << endl;
  return 0;
}

void printList(Node* list, ostream& outs)
{
  Node* temp = list;

  while (temp != nullptr){
    outs << temp->data << endl;
    temp = temp->next;
  }
}

void insertNode(Node*& list, Node*& tail, int val)
{
  Node* temp = new Node;
  Node* ptr;
  Node* prv; //previous pointer
  
  temp->data = val;
  temp->next = nullptr;
    
  if (list == nullptr){ // if list has no items
    temp->next = list;
    list = temp;
    tail = temp;
  }
  else {
    ptr = list;
    prv = nullptr;
    
    while(ptr != nullptr && val > ptr->data){ 
      prv = ptr;
      ptr = ptr->next;
    }

    if (prv == nullptr){ //if val  is lower than head, prv will never update
      list = temp; //so val goes at head 
      temp->next = ptr;
    } else if(ptr == nullptr){ //if reached the end of list
      prv->next = temp;
      tail = temp; //tail is only updated when something is added to end of list
    } else { //inster btwn two  nodes
      prv->next = temp;
      temp->next = ptr;
    }
 
  }
}

void delNode(Node*& list, int val)
{
  Node* delPtr, *ptr;

  if (list->data == val) {//if first val is desired val
    delPtr = list;
    list = list->next;
    delete delPtr;
  } else { //find the node to be deleted

    ptr = list;
    while (ptr->next != nullptr && ptr->next->data < val) {
      ptr = ptr->next; //walk the list
    }
    
    if (ptr ->next != nullptr && ptr->next->data == val){
      //if we didn't reach end of list && the next val is desired val
      delPtr = ptr->next; 
      ptr->next = delPtr->next;
      delete delPtr; //remove val
    }
  }
}
