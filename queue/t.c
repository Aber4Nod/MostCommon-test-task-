char* pblPriorityQueueTest_c_id =
        "$Id: pblPriorityQueueTest.c,v 1.13 2016/06/03 21:13:30 peter Exp $";

#include <stdio.h>
#include <memory.h>
#include "./src/pbl.h"

int main()
{
   int i;
   int rc;
   char * data;

   PblPriorityQueue * priorityQueue;
   priorityQueue = pblPriorityQueueNew();
   rc = pblPriorityQueueIsEmpty( priorityQueue );
   rc = pblPriorityQueueInsert( priorityQueue, 1, "1" );
   rc = pblPriorityQueueInsert( priorityQueue, 2, "2" );
   rc = pblPriorityQueueInsert( priorityQueue, 3, "3" );
   rc = pblPriorityQueueSize( priorityQueue );

   rc = pblPriorityQueueIsEmpty( priorityQueue );
    fprintf( stdout, "pblPriorityQueueIsEmpty( priorityQueue ) rc = %d\n", rc );

    /*
     * Retrieve the value with the highest priority, should be "5" with priority 5.
     */
    data = (char*)pblPriorityQueueGetFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueGetFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    /*
     * Remove the value with the highest priority, should be "5" with priority 5.
     */
    data = (char*)pblPriorityQueueRemoveFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueRemoveFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    /*
     * Retrive and remove the entries one after another.
     */
    data = (char*)pblPriorityQueueGetFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueGetFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueRemoveFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueRemoveFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueGetFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueGetFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueRemoveFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueRemoveFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueGetFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueGetFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueRemoveFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueRemoveFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueGetFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueGetFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueRemoveFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueRemoveFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    /*
     * Test if the queue is empty, should be true now!
     */
    rc = pblPriorityQueueIsEmpty( priorityQueue );
    fprintf( stdout, "pblPriorityQueueIsEmpty( priorityQueue ) rc = %d\n", rc );

    /*
     * Insert the string "1" with a priority value of 1.
     */
    rc = pblPriorityQueueInsert( priorityQueue, 1, "1" );
    fprintf( stdout, "pblPriorityQueueInsert( priorityQueue, 1, 1 ) rc = %d\n",
             rc );

    /*
     * Insert the string "21" with a priority value of 2.
     */
    rc = pblPriorityQueueInsert( priorityQueue, 2, "21" );
    fprintf( stdout,
             "pblPriorityQueueInsert( priorityQueue, 2, 21 ) rc = %d\n", rc );

    /*
     * Insert the string "22" with a priority value of 2, note this is a case of two entries having the same priority.
     */
    rc = pblPriorityQueueInsert( priorityQueue, 2, "22" );
    fprintf( stdout,
             "pblPriorityQueueInsert( priorityQueue, 2, 22 ) rc = %d\n", rc );

    /*
     * Insert the string "23" with a priority value of 2, note this is a case of more than two entries having the same priority.
     */
    rc = pblPriorityQueueInsert( priorityQueue, 2, "23" );
    fprintf( stdout,
             "pblPriorityQueueInsert( priorityQueue, 2, 23 ) rc = %d\n", rc );

    /*
     * Insert the string "24" with a priority value of 2, note this is a case of more than two entries having the same priority.
     */
    rc = pblPriorityQueueInsert( priorityQueue, 2, "24" );
    fprintf( stdout,
             "pblPriorityQueueInsert( priorityQueue, 2, 24 ) rc = %d\n", rc );

    rc = pblPriorityQueueInsert( priorityQueue, 2, "25" );
    fprintf( stdout,
             "pblPriorityQueueInsert( priorityQueue, 2, 25 ) rc = %d\n", rc );

    rc = pblPriorityQueueInsert( priorityQueue, 3, "3" );
    fprintf( stdout, "pblPriorityQueueInsert( priorityQueue, 3, 3 ) rc = %d\n",
             rc );

    /*
     * Retrieve the current capacity of the queue, i.e. the capacity of the underlying array list.
     */
    rc = pblPriorityQueueGetCapacity( priorityQueue );
    fprintf( stdout, "pblPriorityQueueGetCapacity( priorityQueue ) rc = %d\n",
             rc );

    /*
     * Trim the queue to its current size.
     */
    rc = pblPriorityQueueTrimToSize( priorityQueue );
    fprintf( stdout, "pblPriorityQueueTrimToSize( priorityQueue ) rc = %d\n",
             rc );

    /*
     * Retrieve the current capacity of the queue, i.e. the capacity of the underlying array list.
     */
    rc = pblPriorityQueueGetCapacity( priorityQueue );
    fprintf( stdout, "pblPriorityQueueGetCapacity( priorityQueue ) rc = %d\n",
             rc );

    /*
     * Retrieve and then remove the entries one after another
     */
    data = (char*)pblPriorityQueueGetFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueGetFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueRemoveFirst( priorityQueue, &rc );
    fprintf(
             stdout,
             "pblPriorityQueueRemoveFirst( priorityQueue, &prio ) rc = %d, data = %s\n",
             rc, data );

    data = (char*)pblPriorityQueueGetFirst( priorityQueue, &rc );
}
