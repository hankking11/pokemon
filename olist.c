//
//****NOTE****
//THIS IS NOT THE ORIGINAL OLIST FROM THE TROLL WEBSITE
//This module has been modified to work with nodes that have values
//of Location *'s. ALL void *'s have been replaced with Location *'s
//
/* olist - a module for manipulating linked-lists of objects (structures)
 *    - written by John C. Lusth, 2015
 
      - MODIFIED BY HANK KING
      - 4/27/2015
      - for CS100
      -for use with the game for project4
 *


 *    - nodes have values generic void pointers
 *    - join takes a pointer as its first argument
 *    - head returns the pointer (as void *)
 *    - tail returns the list beyond the first node
 *    - setHead replaces the head value
 *    - setTail replaces the tail
 *    - displayList takes in value display procedure and calls it on each value
 *    - arrayToList converts an array of pointers into a list of void pointers
 *    - freeList frees all the values and nodes in the given list
 */

#include <stdio.h>
#include <stdlib.h>
#include "olist.h"
#include "game.h"

#define MAX_SIZE 1024 //size of buffer for readList


/********************* node functions ******************************/

/* newNode
 *     - create a node that holds an Location * value
 */

Node *
newNode(Location *value,Node *next)
    {
    Node *n = malloc(sizeof(Node));
    if (n == 0)
        {
        fprintf(stderr,"newNode: out of memory!\n");
        exit(1);
        }
    n->value = value;
    n->next = next;
    return n;
    }

Node *
newEmptyNode(void)
    {
    Node *n = malloc(sizeof(Node));
    if (n == 0)
        {
        fprintf(stderr,"newEmptyNode: out of memory!\n");
        exit(1);
        }
    n->value = 0;                       //set to the null pointer
    n->next = 0;                        //set to the null pointer
    return n;
    }


/********************* list functions ******************************/

/* newEmptyList
 *    - uses the null pointer to signify an empty list
 */

Node *
newEmptyList(void)
    {
    return 0;
    }

/* head
 *     - return the first value in the list
 */

Location *
head(Node *items)
    {
    return items->value;
    }

/* setHead
 *     - replace the first value in the list
 */

void
setHead(Node *items,Location *s)
    {
    items->value = s;
    }

/* tail
 *    - return the list minus the first node 
 */

Node *
tail(Node *items)
    {
    return items->next;
    }

/* setTail
 *    - replace the tail of a list 
 */

void
setTail(Node *items,Node *newtail)
    {
    items->next = newtail;
    }

/* join
 *     - join an value to a list
 */

Node *
join(Location *s,Node *rest)
    {
    return newNode(s,rest);
    }

/* arrayToList
 *     - convert an array of pointers into a list of Locatoin pointer-valued nodes
 */

Node *
arrayToList(Location **items,int size)
    {
    if (size == 0)
        return 0;
    else
        return join(items[0],arrayToList(items+1,size-1));
    }

//takes in a function to display a location, and a list of locations
//and displays every location in the list
void
displayList(Node *items,void (*display)(Location *))
    {
    while (items != 0)
        {
        printf("{");
        display(head(items));
        printf("}");
        items = tail(items);
        }
    }

void
freeList(Node *items)
    {
    while (items != 0)
        {
        Node *spot = items;
        items = tail(items);
        free(head(spot));    //free the pointer value
        free(spot);          //free the node
        }
    }

