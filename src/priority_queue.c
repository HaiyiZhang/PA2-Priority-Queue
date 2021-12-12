#include <stdlib.h>
#include <stdbool.h>
#include "priority_queue.h"

/*
 * Create a new PriorityQueue structure and return it.
 *
 * The newly-created structure should have a NULL head, and every tail
 * pointer in its tails table should be NULL.
 *
 * nprios: The maximum number of priorities to support
 */
PriorityQueue *pqueue_init(int nprios) {
     PriorityQueue *pq;
    if(nprios <= 0){
        return NULL;
    }
    else{
        pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
        pq->tails =(PQNode **)malloc(nprios * sizeof(PQNode *));
        pq->nprios = nprios;
        for(int i = 0; i<nprios; i++){
            pq->tails[i] = NULL;
        }
    }
    return pq;
}

/*
 * Free all structures associated with this priority queue, including their
 * queue structure itself.  Any access to pqueue after this function returns
 * should be considered invalid.
 *
 * pqueue: the queue to free
 */
void pqueue_free(PriorityQueue *pqueue) {
    PQNode *head = pqueue->head;
    if(head != NULL){
        while(head->next != NULL){
            head = head->next;
            free(head->prev);
        }
        free(head);
    }
    else{
        free(head);
    }
    for(int i = 0; i < pqueue->nprios; i++){
        free(pqueue->tails[i]);
    }
    free(pqueue);
}

/*
 * Insert a new node into a queue by priority and value.
 *
 * pqueue: the queue into which the new node should be inserted
 * value: the opaque value being inserted into the queue
 * priority: the priority at which this value is to be inserted
 */
void pqueue_insert(PriorityQueue *pqueue, int value, int priority) {
    if(priority >= pqueue->nprios || priority < 0){
        ;
    }
    else{
        PQNode *thelast = pqueue->tails[priority];
        PQNode *myhead = pqueue->head;
        
        PQNode *node = (PQNode *)malloc(sizeof(PQNode));

        int checknull = 0;
        int checkmax = 0;
        for(int i = 0; i < pqueue->nprios; i++){
            if(pqueue->tails[i] != NULL){
                checknull = checknull + 1;
                if(priority >= pqueue->tails[i]->priority){
                    checkmax = checkmax + 1;
                }
            }
        }
        node->value = value;
        node->priority = priority;
        pqueue->tails[priority] = node;
        
        if(checknull == 0 || checkmax == 0){
            pqueue->head = node;
            pqueue->head->next = NULL;
            pqueue->head->prev = NULL;
        }

                
        if(thelast == NULL){
            if(pqueue->tails[priority] == pqueue->head){
                pqueue->tails[priority]->prev = NULL;
                pqueue->tails[priority]->next = myhead;
                if(myhead != NULL){
                    myhead->prev = pqueue->tails[priority];}}
            else{
                int before = 0;
                int after = (pqueue->nprios)-1;
                for(int i = 0; i < priority; i++){    //check later
                    if(pqueue->tails[i] != NULL){
                        before = i;}}
                for(int i = (pqueue->nprios)-1; i > priority; i--){    //check later
                    if(pqueue->tails[i] != NULL){
                        after = i;}}
                if(pqueue->tails[before]!=NULL){
                    pqueue->tails[priority]->prev = pqueue->tails[before];
                    pqueue->tails[before]->next = pqueue->tails[priority];}
                if(pqueue->tails[after]!=NULL){
                    pqueue->tails[priority]->next = pqueue->tails[after];
                    pqueue->tails[after]->prev = pqueue->tails[priority];}}}
        else{
            pqueue->tails[priority]->next = thelast->next;
            pqueue->tails[priority]->prev = thelast;
            thelast->next = pqueue->tails[priority];
        }
    }
}

/*
 * Return the head queue node without removing it.
 */
PQNode *pqueue_peek(PriorityQueue *pqueue) {
    if(pqueue->head == NULL){
        return NULL;
    }
    else{
        PQNode *node = pqueue->head;
        return node;
    }

}

/*
 * Remove and return the head queue node.
 */
PQNode *pqueue_get(PriorityQueue *pqueue) {
    if(pqueue->head == NULL){
        return NULL;
    }
    else{
        PQNode *node = pqueue->head;
        for(int i = 0; i < pqueue->nprios; i++){
            if(pqueue->tails[i] == node){
                pqueue->tails[i] = NULL;
            }
        }
        PQNode *nodenext = pqueue->head->next;
        pqueue->head = nodenext;
        pqueue->head->prev = NULL;
        return node;
    }
}
