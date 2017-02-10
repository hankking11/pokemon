
//The following is code for a text based game called
//              Pokemon Black-And-White
//Authored by Hank King
//for CS100
//      4/27/2015
//
//compile with io.c, game.c, logic.c, and olist.c
//NOTE: the olist module has been modified to fit the 
//nodes and objects used in this project w/o void *
//
//The user is prompted for input until the game is
//either won, lost or quit.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"
#include "io.h"
#include "logic.h"
#include "olist.h"

int main()
    {
    FILE *fp = fopen("loc.txt","r");
    Location *loc = readLocation(fp);
    world = newEmptyList();
    while (!feof(fp))               //This loop reads all locations
        {                           //into a linked list of nodes
        world = join(loc,world);    //called world
        loc = readLocation(fp);
        }
    
    //void (*functionPointer)(Location *) = displayLocation;
    //displayList(world,functionPointer);
    
    Adventurer *adv = newAdventurer();
    loc = findLocation("palletTown");   //palletTown is the first location
    
    printIntro();           //prints intro to game and
    printInstructions();    //instructions
    while (loc != 0)                //this loop will prompt the user
        {                           //for input until the game is 
        loc = gameCore(loc,adv);    //either won, lost or, quit
        }
    return 0;
    }


