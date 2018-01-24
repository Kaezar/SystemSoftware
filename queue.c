#include <stdlib.h>
#include <stdio.h>


typedef struct Node *node;

struct Node {
  node next;
  node previous;
  int data;
};


node last;
node first;

int enqueue (int n) {
  node temp;
  temp = (node)malloc(sizeof(struct Node));
  temp->data = n;
  if (last == NULL) {
    printf("I am working.");
    temp->next = NULL;
    temp->previous = NULL;
    last = temp;
    first = temp;
  }
  else {
    /*
    printf("YAY!");
    node saveLast = last;
    last -> next = temp;
    temp->previous = saveLast;
    last = temp;
    */

    last->next = temp;
    temp->previous = last;
    last = temp;
  }
  return 1;
} // enqueue

int dequeue () {
  // catch empty queue
  if (first == NULL) {
    return -1;
  }

  // catch only one item
  if (last = first) {
    return -1;
  }
  
  node result = first;

  // delete the node
  first = first -> next;

  return result->data;
}

void print() {
  //int count = 0;
  while (first != NULL) {
    //printf("%d", count);
    printf("%d\n", first -> data);
    //printf("hello");
    first = first -> next;
    //count = count + 1;
    //printf("%p",first);
  }
}


void iterate(){
  node thing = first;
  while(thing != NULL){
    printf("%d", thing->data);
    thing = thing->next;
  }
}
int main (int argv, char** argc) {
  enqueue(5);
  enqueue(12);
  enqueue(20);
  iterate();
  return 1;
}

  
  
