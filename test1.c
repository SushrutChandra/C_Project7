#include <stdio.h>
#include <assert.h>
#include "prio-q.h"

/* CMSC 216
 * Test 1
 *
 * Tests that clear() removes all of a priority queue's elements.
 *
 * This test will always unavoidably have memory leaks under valgrind
 * Fixed any other problems that valgrind identifies, but ignored
 * any memory leaks
 */

int main(void) {
  Prio_que prio_q;
  char *elements[]= {"Rocky Racoon", "Wally Walrus", "Aaron Aardvark",
                     "Ginny Giraffe", "Manny Manatee", "Donny Donkey", 
                     "Courtney Koala"};
  int i, priorities[]= {90, 40, 60, 20, 30, 50, 80};

  init(&prio_q);

  for (i= 0; i < (int) (sizeof(elements) / sizeof(elements[0])); i++)
    enqueue(&prio_q, elements[i], priorities[i]);

  assert(size(prio_q) == 7);

  clear(&prio_q);
  init(&prio_q);
  
  assert(is_empty(prio_q));
  assert(size(prio_q) == 0);

  printf("Yet another test worked right!\n");

  return 0;
}
