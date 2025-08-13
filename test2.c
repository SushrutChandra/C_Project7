#include <stdio.h>
#include <assert.h>
#include "prio-q.h"
#include "memory-checking.h"

/* CMSC 216
 * Test 2
 *
 * Tests adding a few elements to a priority queue and checks its size, then
 * clears it and checks that there are no memory leaks or errors in the
 * heap.
 */

int main(void) {
  Prio_que prio_q;
  char *elements[]= {"Rocky Racoon", "Wally Walrus", "Aaron Aardvark",
                     "Ginny Giraffe", "Manny Manatee", "Donny Donkey"};
  int priorities[]= {90, 40, 60, 20, 30, 50};
  int i;

  #if !defined(ENABLE_VALGRIND)
  setup_memory_checking();
  #endif

  init(&prio_q);

  for (i= 0; i < ARRSIZE(elements); i++)
    enqueue(&prio_q, elements[i], priorities[i]);

  assert(size(prio_q) == 6);

  clear(&prio_q);

  #if !defined(ENABLE_VALGRIND)
  check_heap();
  #endif

  printf("Yet another test worked right!\n");

  return 0;
}
