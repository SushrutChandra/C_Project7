#if !defined(PRIO_Q_DATASTRUCTURE_H)
#define PRIO_Q_DATASTRUCTURE_H
/* 
Name: Sushruit Chandra 

This file is the header file for the data structure of the priority queue
The strucutre use for a priority queue is a binary search tree 
The data in each node is the priority and a dynamically allocated string 
it has a left and right node pointer 
The priority queue itself stores the pointer to the head of the BST
The structure also keeps the size of the priority queue
*/

/* Node of a BST 
   The data in each node is the priority and a string 
   it also has a left and right node pointers 
 */
typedef struct node {
  unsigned int priority;
  char *str;
  struct node *left;
  struct node *right;
} Node;

/* priority queue structure
   The head points to the root of the BST 
   The size keeps track of the size of the priorit queue
*/
typedef struct prio_que {
  Node *head;
  int size;  /* size of the queue*/
} Prio_que;

#endif
