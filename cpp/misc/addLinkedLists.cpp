#include <iostream>
using namespace std;

struct LinkedListNode{
  int val;
  LinkedListNode* next = NULL;
};

LinkedListNode* add_integers(
    LinkedListNode* integer1, 
    LinkedListNode* integer2) {
  //TODO: Write - Your - Code
  int sum = 0;
  int carry = 0;
  LinkedListNode* result;

  LinkedListNode *r;
  if ((integer1 != NULL) && (integer2 != NULL)){
    r = new LinkedListNode();
    result = r;
  }
  while((integer1 != NULL) && (integer2 != NULL)){
    //Load in default values
    int a = 0;
    int b = 0;
    // Read in actual values, if they exist
    if(integer1 != NULL)
      a = integer1->val;
    if(integer2 != NULL)
      b = integer2->val;
    // Perform computation
    sum = (a+b+carry) % 10;
    carry = (a+b+carry) / 10;
    // Store result
    r->val = sum;
    r->next = new LinkedListNode();
    integer1 = integer1->next;
    integer2 = integer2->next;
    r = r->next;
  }

  return result;
}

int linkedListToInteger(LinkedListNode* start){
  int sum = 0;
  int tens = 1;
  while(start != NULL){
    sum += start->val * tens;
    tens *= 10;
    start = start->next;
  }
  return sum;
}

int main(int argc, char **argv){
  LinkedListNode *a = new LinkedListNode;
  a->val = 1;
  a->next = new LinkedListNode;
  a->next->val = 0;
  a->next->next = new LinkedListNode;
  a->next->next->val = 1;

  LinkedListNode *b = new LinkedListNode;
  b->val = 1;
  b->next = new LinkedListNode;
  b->next->val = 0;
  b->next->next = new LinkedListNode;
  b->next->next->val = 0;

  cout << "Value of a is " << linkedListToInteger(a) << endl;
  cout << "Value of b is " << linkedListToInteger(b) << endl;

  LinkedListNode* r = add_integers(a,b);

  cout << "Value of a+b is " << linkedListToInteger(r) << endl;

}