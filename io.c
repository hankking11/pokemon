
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"
#include "scanner.h"
#include "logic.h"
#include "io.h"

//prints controls for game
void printInstructions(void)
    {
    printf("------------------------------------------------\n");
    printf("You can move around and carry out actions by entering words\n");
    printf("your options are:\n");
    printf("    -north, south, east or west: flies to the nearest landmark in \n");
    printf("        the specified direction\n");
    printf("        ***note some directions will not always be available \n");
    printf("        as you can only fly so much distance at one time***\n");
    printf("    -get: picks up an item (when followed with the item to pick up) \n");
    printf("    -drop: drops an item (when followed with the item to be dropped) \n");
    printf("    -look: displays all relevant information \n");
    printf("------------------------------------------------\n");
    return;
    }

//prints intro to game
void printIntro(void)
    {
    printf("-----------------------------------------------------------\n");
    printf("    !!!!Welcome to Pokemon Black-And-White Version!!!! \n");
    printf("-----------------------------------------------------------\n");
    printf("Rated T for Teen\n");
    printf("You get to play as Ash's pidgeot. \n");
    printf("Today, Ash is out fighting the Elite Four. But he forgot his best \n");
    printf("pokemon (Thats you!). What's worse is that when Ash was out on the \n");
    printf("town last night, he left his items all over the region!!! He can't \n");
    printf("remember where he left them, and  he can't win without them. Your job \n");
    printf("is to gather his items and bring them to him before he is defeated! \n");
    printf("you have 250  moves or actions before you use up all your strength \n");
    printf("and faint.\n");
    printf("Without you ash will surely lose! (He's not feeling very well this \n");
    printf("morning) To win you need all 12 items.\n");
    return;
    }

//This function reads all information available about a location from a file
//returns the Location structure storing it
Location *readLocation(FILE *fp) 
    {
    Location *loc = newEmptyLocation();
    char *attr = readToken(fp);
    if (feof(fp)) return 0; //no more locations
    while (strcmp(attr,";") != 0) 
        {
        if (strcmp(attr,"name") == 0)
            loc->name = readToken(fp);
        else if (strcmp(attr,"longer") == 0)
            loc->longer = readString(fp);
        else if (strcmp(attr,"shorter") == 0)
            loc->shorter = readString(fp);
        else if (strcmp(attr,"north") == 0)
            loc->north = readToken(fp);
        else if (strcmp(attr,"south") == 0)
            loc->south = readToken(fp);
        else if (strcmp(attr,"east") == 0)
            loc->east = readToken(fp);
        else if (strcmp(attr,"west") == 0)
            loc->west = readToken(fp);
        else if (strcmp(attr,"logic") == 0)
            loc->logic = readToken(fp);
        else if (strcmp(attr,"item") == 0)
            {
            addItemToLocation(loc,readToken(fp));
            }
        attr = readToken(fp);
        } 
    return loc;
    }

//This function prints all relevant information to a location
void displayLocation(Location *loc)
    {
    printf("Name is %s\n",loc->name);
    printf("Visited is %d\n",loc->visited);
    printf("Longer is %s\n",loc->longer);
    printf("Shorter is %s\n",loc->shorter);
    printf("North is %s\n",loc->north);
    printf("South is %s\n",loc->south);
    printf("East is %s\n",loc->east);
    printf("West is %s\n",loc->west);
    printf("Logic is %s\n",loc->logic);
    displayItems(loc->items);
    return;
    }

//This function prints all items in an array of strings
//that aren't "thereisnoitemhere"
void displayItems(char *items[20])
    {
    int hasItems = 0;
    int i;
    for (i = 0; i < 20; i++)
        {
        if (strcmp(items[i],"thereisnoitemhere") != 0)  //makes sure there's an item
            {
            printf("    %s\n",items[i]);                //prints if there is one
            hasItems = 1;                               
            }
        }
    if (hasItems == 0)                                  //if its empty,
        printf("    (none)\n");                         //print (none)
    return;
    }

//This function prints all relevant information
//to an adventurer and location
void look(Location *loc,Adventurer *a)
    {
    printf("------------------------------------------------\n");
    printf("%s\n",loc->longer);
    printf("From above, you can see the following items scattered on the ground: \n");
    displayItems(loc->items);
    printf("You can see the following in each direction: \n");
    if (strcmp(loc->north,"nothing") != 0)      //doesn't print anything if there's
        {                                       //not an accessible location in a
        printf("    north: ");                  //direction
        printLocationName(loc->north);          //(prints only non-nothing sorroundings)
        }
    if (strcmp(loc->south,"nothing") != 0)
        {
        printf("    south: ");
        printLocationName(loc->south);
        }
    if (strcmp(loc->east,"nothing") != 0)
        {
        printf("    east: ");
        printLocationName(loc->east);
        }
    if (strcmp(loc->west,"nothing") != 0)
        {
        printf("    west: ");
        printLocationName(loc->west);
        }
    printf("\n");
    printf("strength points: %d\n",a->strength);
    printf("score: %d\n",a->score);
    printf("Your items: \n");
    displayItems(a->items);
    printf("------------------------------------------------\n");
    return;
    }

//This function prints the shorter string of
//a location with the name passed to it.
//(the shorter string contains the name seperated by a space)
void printLocationName(char *s)
    {
    Location *loc = newEmptyLocation();
    loc = findLocation(s);
    printf("%s \n",loc->shorter);
    }
