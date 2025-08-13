/*
Name: Sushruit Chandra

This file has the code for the functions to manage the priority queue
The strucutre use for a priority queue is a binary search tree.
Each Node ofthe BST contains the priority and string values along
with a left and right pointers

This file includes functions to enqueue, dequeue, peek the priority queue
and also get its size 
additinally it includes memory management functions to free the name list,
clear all dynamically allocated memory, get highest priority element, 
remove elements in a priority range and change the priority

The valid sequence of call is to have init as the first call, and 
clear as the last call before ending use of the priority queue

*/

#include <stdlib.h>
#include <string.h>
#include "prio-q.h"

/* Helper function prototypes */
/* insert(): Helper function for enqueue to inserts a node in the BST */
static int insert(Node **root, const char new_element[],
		  unsigned int priority);

/* traverse(): Helper function for get_all_elements to traverse BST */
static void traverse(Node *root, char **str_copies, int *index);

/* traverse_clear(): Helper function to traverse BST and clear all nodes */
static void traverse_clear(Node *root);


/* get_priority_helper: this returns the highest priority in the BST that
   matches the string element
   The function first searches the right subtree for element 
   if not found, checks the root for the element 
   If not found on the root, searches left subtree */
int get_priority_helper(Node *root, char element[]);

/* free_node : Helper function to free a node */
static void free_node(Node **root);

/* count_elements: counts number of nodes that match element in the BST */
int count_elements(Node *root, char element[]);

/* count_priority: counts number of nodes that match priority in the BST */
int count_priority(Node *root, int priority);


/* change_priority_helper: changes the priority in the BST for element */
void change_priority_helper(Node *root, char element[], int new_priority);

/* init: initialzies the priority queue 
   if input parameter is NULL, the function does nothing */
unsigned int remove_elements_helper(Node **root, unsigned int low,
				    unsigned int high);

/* swap: Swaps root with its successor */
Node **swap(Node **root);

/* init: initializes the priority queue */ 
void init(Prio_que *const prio_q) {
  if (prio_q != NULL) {
    prio_q->head = NULL;  /* Initialize head to NULL */
    prio_q->size = 0;     /* Initialize priority queue size to 0 */
  }

  return;
}

/* enqueue(): Adds an element to the priority queue */
unsigned int enqueue(Prio_que *const prio_q, const char new_element[],
                     unsigned int priority) {
  unsigned int ret_val = 0;

  /* check for valid function parameters and insert element in BST */
  if (prio_q != NULL && new_element != NULL && priority >= 0)
    ret_val = insert(&(prio_q->head), new_element, priority); 

  /* If successfully inserted, increment priority queue size */
  if (ret_val == 1) 
    prio_q->size = prio_q->size + 1;

  return ret_val;
}

/* insert(): inserts element into BST using priority */
static int insert(Node **root, const char new_element[],
		  unsigned int priority){
  Node *new = NULL; /* New node to be inserted */
  int result = 0;

  /* Ensure valid root pointer */
  if (root != NULL) {

    /* base case for an empty BST */
    if (*root == NULL) {
      new = malloc(sizeof(*new));

      /* allocate new node and make its parent point to it */
      if (new != NULL) {
	new->priority = priority;
	new->str = malloc(strlen(new_element) + 1);
	strcpy(new->str, new_element);
        new->left= new->right= NULL;
        *root = new;

        result = 1;
      }

    } else
      /* recursive case: check if insert into left or right sub-trees */
      if (priority < (*root)->priority)
        result = insert(&((*root)->left), new_element, priority);
      else
	if (priority > (*root)->priority)
	  result = insert(&((*root)->right), new_element, priority);
	else
	  result = 0;
  }

  return result;
}

/* is_empty: this function return 1 if the queue is empty else 0
   incase of an ivalid parameter returns 0 */
unsigned int is_empty(const Prio_que prio_q) {
  unsigned int ret_val = 0;
  
  /* check size of priority queue */
  if( prio_q.size == 0)
    ret_val = 1;
  else 
    ret_val = 0;
  
  return ret_val;
}

/* size(): Returns the size of the priority queue */
unsigned int size(const Prio_que prio_q) {
  return  prio_q.size;
}

/* peek(): return element with the highest priority */
char *peek(Prio_que prio_q) {
  char *ret_str = NULL;
  Node *high_node;
 
  /* Check for empty priority queue */
  if (prio_q.head != NULL) {
    high_node = prio_q.head;
    while (high_node->right != NULL) 
      high_node = high_node->right;
    
    /* Allocate memory and copy element with highest priority */
    ret_str = malloc(strlen(high_node->str) + 1);
    strcpy(ret_str, high_node->str);
  }

  return ret_str;
}

/* dequeue(): remove highest priority node and return its element */
char *dequeue(Prio_que *const prio_q) { 
  char *ret_str = NULL;
  Node **high_node;
  Node *del_node; /*pointer to node to be deleted */

  /* Check for empty priority queue */
  if (prio_q != NULL && prio_q->head != NULL) {
    high_node = &(prio_q->head);
    while ((*high_node)->right != NULL)
      high_node = &((*high_node)->right);

    ret_str = malloc(strlen((*high_node)->str) + 1);
    strcpy(ret_str, (*high_node)->str);

    /* delete highest priority node*/
    /*if left child is NULL then delete node else parent points to left child*/
    if ((*high_node)->left == NULL) {
      free_node(high_node);
    }
    else {
      del_node = *high_node;
      *high_node = (*high_node)->left;
      free_node(&del_node);
    }
    /*decrement priority queue size*/
    prio_q->size = prio_q->size - 1;
  }

  return ret_str;
}

/* get_all_elements(): returns elements of priority queue */
char **get_all_elements(Prio_que prio_q) {
  int index = 0;
  char **str_copies = malloc((prio_q.size + 1) * sizeof(*str_copies));

  /* set last element of array to NULL*/
  str_copies[prio_q.size] = NULL;
  
  /* recursively traverse priority queue and set element value*/
  traverse(prio_q.head, str_copies, &index);
  
 return str_copies;
}

/* traverse(): Traverse BST and get element value at each node */
static void traverse(Node *root, char **str_copies, int *index) {
  char *str;
  
  if (root != NULL) {
    /* traverse right subtree */
    if (root->right != NULL) 
      traverse(root->right, str_copies, index);
    
    /* process root. Extract element from root node and copy to str_copies*/
    str = malloc(strlen(root->str) + 1);
    strcpy(str, root->str);
    str_copies[*index] = str;
    *index = *index + 1;
    
    /* traverse left subtree */
    if (root->left != NULL)
      traverse(root->left, str_copies, index);
  }

  return;
}

/* free_name_list: This function traverses the name_list and releases memory 
   for all the array elements till it reaches a NULL element 
   Does nothing if name_list is null */
void free_name_list(char *name_list[]) {
  char **curr; /* points to the current string being processed */
  
  if (name_list != NULL) {
    curr = name_list;
    /* traverse array till NULL value */
    while (*curr != NULL) {
      free(*curr);
      curr++;
    }
    
    free(name_list);
  }
}

/* clear: traverses the priority queue and frees memory for every node */
void clear(Prio_que *const prio_q) {
  if (prio_q != NULL) {
    traverse_clear(prio_q->head);
    prio_q->head = NULL;
    prio_q->size = 0;
  }

  return;
}

/* get_priority: traverses BST and returns highest priority for element
   traversing right tree, root, left tree ensures highest priority returned
   first */
int get_priority(Prio_que prio_q, char element[]) {
  int priority = -1;

  if (element != NULL && prio_q.head != NULL) 
    priority = get_priority_helper(prio_q.head, element);

  return priority;
}

/* remove_elements_between: removes elements with priority between the given 
   low and high priorities. traverses the BST to remove these priorities */
unsigned int remove_elements_between(Prio_que *const prio_q, unsigned int low,
                                     unsigned int high) {
  unsigned int elements_removed = 0;

  /* validate parameters and nonempty priority queue */
  if (prio_q != NULL && prio_q->head != NULL && low >=0 && high>= 0)
    elements_removed = remove_elements_helper(&(prio_q->head), low, high);
  
  /* decrement priority queue size*/
  prio_q->size = prio_q->size - elements_removed;
  
  return elements_removed;
}

/* remove_elemets_helper: Removes nodes with priority between low and high
   First this recursively removed elemets from the left and right subtrees
   Then the root node is handled */
unsigned int remove_elements_helper(Node **root, unsigned int low,
				    unsigned int high) { 
  unsigned int elements_removed = 0;
  Node **del_node; /* Address of pointer to node to be deleted */
  Node *tmp_node;

  /* Process only if the curr_node is not NULL */
  if (*root != NULL) {
    /* remove nodes that match from the left and right subtree */
    elements_removed += remove_elements_helper(&((*root)->left), low, high);
    elements_removed += remove_elements_helper(&((*root)->right), low, high);

    /* now handle the current node */
    if ((*root)->priority >= low && ((*root)->priority <= high)) {
      /* delete root*/
      /* If root has both left & right child, swap it with succesor  node */

      del_node = root;
      if ((*del_node)->left != NULL && (*del_node)->right != NULL)
	del_node = swap(del_node);

      /*Case 1: left and right pointers are NULL */
      if ((*del_node)->left == NULL && (*del_node)->right == NULL)
	free_node(del_node);
      /*Case 2: only right pointers is NULL */
      else if ((*del_node)->right == NULL) {
	tmp_node = *del_node;
	*del_node = (*del_node)->left;
	free_node(&tmp_node);
      }
      /*Case 3: only left pointers is NULL */
      else {
	tmp_node = *del_node;
	*del_node = (*del_node)->right;
	free_node(&tmp_node);
      }

      /*Increment nodes removed countere*/
      elements_removed += 1;
    }
  }

  return elements_removed;
}

/* swap: Swaps root with its successor */
Node **swap(Node **root){
  Node **next = &((*root)->right);
  
  /* Traverse left in root's right sub-tree to find succesor */
  while ((*next)->left != NULL)
    next = &((*next)->left);
  
  /* Copy successors data to root */
  (*root)->priority = (*next)->priority;
  free((*root)->str);
  (*root)->str = malloc(strlen((*next)->str) + 1);
  strcpy((*root)->str, (*next)->str);
  
  /* root pointer becomes next */
  return next;
} 

/* change_priority: Changes the priority for a given element to the new
   priority */
unsigned int change_priority(Prio_que *prio_q, char element[],
                             unsigned int new_priority) {
  int ret_val = 0;
  
  /* validate parameters */
  if (prio_q != NULL && element != NULL && new_priority >= 0) {
    /* change priority only if element is present once and priority not used */
    if (count_elements(prio_q->head, element) == 1 && 
	count_priority(prio_q->head, new_priority) == 0) {
      change_priority_helper(prio_q->head, element, new_priority);
      ret_val = 1;
    }
  }

  return ret_val;
}

/* count_elements: counts number of nodes that match element in the BST */
int count_elements(Node *root, char element[]) {
  int count = 0;
  
  if (root != NULL){
    if(strcmp(root->str, element) == 0) 
      count = 1;
    
    count += count_elements(root->left, element) +
      count_elements(root->right, element);
  }

  return count;
}

/* count_priority: counts number of nodes that match priority in the BST */
int count_priority(Node *root, int priority) {
  int count = 0;
  
  if (root != NULL){
    if (root->priority == priority) 
    count = 1;
    
    count += count_priority(root->left, priority) +
      count_priority(root->right, priority);
  }

  return count;
}

/* change_priority_helper: changes the priority in the BST for element */
void change_priority_helper(Node *root, char element[], int new_priority) {
  
  if (root != NULL){
    if (strcmp(root->str, element) == 0) 
      root->priority = new_priority;
    else {
      change_priority_helper(root->left, element, new_priority);
      change_priority_helper(root->right, element, new_priority);    
    }
  }

  return;
}

/* traverse(): Traverse BST and free each node */
static void traverse_clear(Node *root) {
  
  if (root != NULL) {
    /* traverse right subtree */
    if (root->right != NULL) 
      traverse_clear(root->right);
    
    /* traverse left subtree */
    if (root->left != NULL)
      traverse_clear(root->left);

    /* process root. free memory for string and the Notes*/
    free_node(&root);
  }

  return;
}

/* free_node : Helper function to free a node */
static void free_node(Node **root){
  /* free memory for the string element */ 
  free((*root)->str);
  (*root)->str = NULL;

  /* Free memory for the node */
  free((*root));
  (*root) = NULL;

  return;
}

/* get_priority_helper: this returns the highest priority in the BST that
   matches the string element
   The function first searches the right subtree for element 
   if not found, checks the root for the element 
   If not found on the root, searches left subtree */
int get_priority_helper(Node *root, char element[]) {
  int priority = -1; 

  /* search right subtree */
  if (root->right != NULL) 
    priority = get_priority_helper(root->right, element);
  
  /* if not found, search the root node */
  if (priority == -1 && strcmp(root->str, element) == 0) 
    priority = root->priority;

  /* if not found, search the left subtree */
  if (priority == -1 && root->left != NULL)
    priority = get_priority_helper(root->left, element);
  
  return priority;
}
