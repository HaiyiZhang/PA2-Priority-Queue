#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "priority_queue.h"


/*
 * Validate the given PriorityQueue for structural correctness.
 *
 * In order for this function to return true, the queue passed in must
 * meet the specification in the project handout precisely.  Every node
 * in the linked list and every pointer in the tails table must be
 * correct.
 *
 * pqueue: queue to validate
 *
 * Returns true if the queue is valid, false otherwise.
 */
bool pqueue_validate(PriorityQueue *pqueue) {
    PQNode *last = pqueue->tails[(pqueue->nprios)-1];


    int a = (pqueue->nprios)-1;
    int b = (pqueue->nprios)-1;
    while (last == NULL){
        last =  pqueue->tails[b];
        b--;
    }

    /* empty pqueue*/
    if(pqueue->head == NULL){
        for(int i = 0; i<(pqueue->nprios); i++){
            if(pqueue->tails[i] != NULL){
                return false;
            }
            if(pqueue->tails[i]->priority != i){
                return false;
            }
        }
    }

    /* non-decreasing */
    if(pqueue->head != NULL){
        last = pqueue->tails[(pqueue->nprios)-1];
        while(last->prev != NULL){
            if(last->prev->priority > last->priority && last != pqueue->head){
                return false;
            }
            last = last->prev;
        }
    }
    last = pqueue->tails[(pqueue->nprios)-1];



    last = pqueue->tails[(pqueue->nprios)-1];

    /*check head prev is NULL*/
    if(pqueue->head->prev != NULL){
        return false;
    }
    /*check the last tail next is NULL*/
    if(pqueue->tails[a]->next != NULL){
        return false;

    }
    /* tails = NULL no priority = index */

    for(int i = 0; i<(pqueue->nprios); i++){
        if(pqueue->tails[i] == NULL){
            while(last != NULL){
                if(last->priority == i){
                    return false;
                }
                last = last->prev;
            }
        }
    }

    last = pqueue->tails[(pqueue->nprios)-1];
    /* the tails point the last*/
    for(int i = 0; i<(pqueue->nprios); i++){
        if(pqueue->tails[i] != NULL){
            if(pqueue->tails[i]->next != NULL){
                if(pqueue->tails[i]->next->priority == pqueue->tails[i]->priority ){
                    return false;
                }
            }
        }
    }
   last = pqueue->tails[(pqueue->nprios)-1];

    /* do not know*/
    for(;last != NULL; last = last->prev){
        if(last->prev == NULL && last != pqueue->head){
            return false;
        }

    }

    last = pqueue->tails[(pqueue->nprios)-1];

    last = pqueue->tails[(pqueue->nprios)-1];

    /* prev - next = last */
    while(last != pqueue->head){
        if(last->prev->next != last && last != pqueue->head){
            return false;
        }
        last = last->prev;
    }

    last = pqueue->tails[(pqueue->nprios)-1];

    /* node priority is in 0 and nprios-1 */
    /* PQNode *start = pqueue->head;

    while(start != NULL){
        if(!(start->priority >= 0 && start->priority<= a)){
            return false;
        }
        start = start->next;


        } */

    last = pqueue->tails[(pqueue->nprios)-1];

    while(last != NULL){
        if(last->priority < 0 || last->priority > a ){
            return false;
        }
        last = last->prev;
    }




    return true;
}
