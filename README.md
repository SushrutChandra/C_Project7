# Dynamic Priority Queue with Memory-Safe BST in C

This project implements a **priority queue** in C using a **binary search tree (BST)** as the underlying data structure. Each node in the BST stores a **priority** and a dynamically allocated **string**, allowing efficient insertion, deletion, and retrieval based on priority. Memory safety is emphasized through careful allocation and deallocation.

## Features

- **Enqueue / Dequeue**: Add and remove elements based on priority.  
- **Peek**: Access the element with the highest priority without removal.  
- **Change Priority**: Modify the priority of a specific element.  
- **Remove Elements in Range**: Remove all elements whose priority falls within a given range.  
- **Memory Management**: All dynamically allocated memory is properly managed and cleared.  
- **Get All Elements**: Retrieve a list of all elements sorted by priority.  
- **Size and Emptiness Checks**: Query the size of the queue or whether it is empty.

## Data Structures

- **Node**: Represents each element in the priority queue. Contains:
  - `priority` (unsigned int)
  - `str` (dynamically allocated string)
  - `left` and `right` child pointers

- **Prio_que**: Represents the priority queue. Contains:
  - `head` (pointer to the root of the BST)
  - `size` (current number of elements in the queue)

## Usage

1. **Initialize the queue**
```c
Prio_que prio_q;
init(&prio_q);
Add elements

c
Copy
Edit
enqueue(&prio_q, "Task A", 50);
enqueue(&prio_q, "Task B", 80);
Access highest priority element

c
Copy
Edit
char *top = peek(prio_q);
// Use `top` as needed, then free it
free(top);
Remove elements

c
Copy
Edit
char *removed = dequeue(&prio_q);
free(removed);
Change priority

c
Copy
Edit
change_priority(&prio_q, "Task A", 90);
Clear the queue

c
Copy
Edit
clear(&prio_q);
Tests
The project includes two test programs:

test1.c: Validates clear() and ensures the queue can be reinitialized.

test2.c: Adds elements, checks size, clears the queue, and verifies memory safety.

Both tests print a confirmation message when successful:

bash
Copy
Edit
Yet another test worked right!
Memory Safety
All string data is dynamically allocated.

Functions like clear() and free_name_list() free all memory to prevent leaks.

enqueue() and dequeue() manage allocations carefully to avoid dangling pointers.

Priority queue operations are designed to prevent memory corruption even under repeated insertions and deletions.

Proper handling of node swaps and recursive clearing ensures every node and string is freed.
