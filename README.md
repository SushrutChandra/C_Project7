# Dynamic Priority Queue in C (BST Implementation)

This project implements a **priority queue** in C using a **binary search tree (BST)**. Each node contains a **priority** and a dynamically allocated **string**, allowing efficient insertion, removal, and retrieval of elements by priority while maintaining memory safety.

---

## Features

- **Enqueue / Dequeue**: Add and remove elements according to priority.
- **Peek**: Access the highest-priority element without removal.
- **Change Priority**: Update the priority of an existing element.
- **Remove Elements in Range**: Remove all elements with priority within a specified range.
- **Get All Elements**: Retrieve all elements sorted by priority.
- **Memory Management**: Dynamically allocated memory is carefully managed to prevent leaks.
- **Queue Information**: Check queue size and whether the queue is empty.

---

## Data Structures

### Node
Represents an element in the BST:
- `priority` (unsigned int)  
- `str` (dynamically allocated string)  
- `left` and `right` child pointers  

### Prio_que
Represents the priority queue:
- `head` (pointer to the root node of the BST)  
- `size` (current number of elements in the queue)  

---

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
Access the highest-priority element

c
Copy
Edit
char *top = peek(prio_q);
// Use the element, then free memory
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
Retrieve all elements

c
Copy
Edit
char **elements = get_all_elements(prio_q);
// Remember to free each element and the array itself
free_name_list(elements);
Testing
Included test programs:

test1.c: Verifies clear() and queue reinitialization.

test2.c: Tests insertion, size, clearing, and memory safety.

Both tests output:

bash
Copy
Edit
Yet another test worked right!
Memory Safety
All strings are dynamically allocated and freed appropriately.

clear() and free_name_list() ensure no memory leaks.

enqueue() and dequeue() manage memory safely.

Recursive clearing and careful handling of BST node swaps prevent dangling pointers.

Designed to be robust under repeated insertions, deletions, and priority changes.

Example
c
Copy
Edit
Prio_que pq;
init(&pq);

enqueue(&pq, "Low Priority", 10);
enqueue(&pq, "High Priority", 90);

char *top = peek(pq); // "High Priority"
printf("%s\n", top);
free(top);

dequeue(&pq);
clear(&pq);
