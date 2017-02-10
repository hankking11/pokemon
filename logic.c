
//The following is the logic code for a text based game called
//              Pokemon Black-And-White
//Authored by Hank King
//for CS100
//      4/27/2015
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "game.h"
#include "scanner.h"
#include "logic.h"
#include "io.h"

//This function returns a dynamically allocated empty location
//***NOTE*** the string, "thereisnoitemhere" is used throughout
//the code to indicate an empty field. This is to avoid
//segmentation faults when passing NULL pointers to strcmp
Location *newEmptyLocation(void)
    {
    Location *loc = malloc(sizeof(Location));
    loc->name = "thereisnoitemhere";        //represents empty slot
    loc->visited = 0;
    loc->longer = "thereisnoitemhere";
    loc->shorter = "thereisnoitemhere";
    loc->north = "thereisnoitemhere";
    loc->south = "thereisnoitemhere"; 
    loc->east = "thereisnoitemhere";
    loc->west = "thereisnoitemhere";
    loc->logic = 0; 
    loc->items[20] = malloc(sizeof(char *) * 20);   //dynamically allocate
    int i;                                          //the array of strings
    for (i = 0;i < 20;i++)
        {
        loc->items[i] = malloc(sizeof(char *));     //dynamically allocate each
        loc->items[i] = "thereisnoitemhere";        //string
        }
    return loc;
    }

//This function returns a dynamically allocated
//adventurer for starting the game
Adventurer *newAdventurer(void)
    {
    Adventurer *adv = malloc(sizeof(Adventurer));
    adv->score = 0;
    adv->strength = 250;
    adv->items[20] = malloc(sizeof(char *) * 20);
    int i;
    for (i = 0;i < 20;i++)
        {
        adv->items[i] = malloc(sizeof(char *));
        adv->items[i] = "thereisnoitemhere";
        }
    return adv;
    }

//This function takes in a string representing
//the name of a location and returns the 
//corresponding location.
Location *findLocation(char *name)
    {
    Node *w = world;
    while (w != 0)
        {
        if (strcmp(name,w->value->name) == 0)
            return w->value;
        else
            w = w->next;
        if (w == 0)
            {
            printf("Location not found, name is %s \n",name);
            return NULL;
            }
        }
    return NULL;
    }

//This function takes in a logic function name
//and passes the location, adventurer, noun and verb
//to that logic function. It returns the appropriate
//location depending on user input of verb and noun
Location *logic(char *s,Location *loc,Adventurer *a,char *verb,char *noun)
    {
    if (strcmp(s,"basicLogic") == 0)
        return basicLogic(loc,a,verb,noun);
    else if (strcmp(s,"moonLogic") == 0)
        return moonLogic(loc,a,verb,noun);
    else if (strcmp(s,"fuschiaLogic") == 0)
        return fuschiaLogic(loc,a,verb,noun);
    else if (strcmp(s,"indigoLogic") == 0)
        return indigoLogic(loc,a,verb,noun);
    else if (strcmp(s,"palletLogic") == 0)
        return palletLogic(loc,a,verb,noun);
    else
        return basicLogic(loc,a,verb,noun);
        
    }

//Returns either the current location or an adjacent location
//contains all options available at the location
//***NOTE*** if loc->(direction here) is "nothing", you can't
//go that direction
Location *basicLogic(Location *loc,Adventurer *a,char *verb,char *noun)
    {
    loc->visited = 1;
    a->strength = a->strength - 1;          //decrease strength for each call
    if (strcmp(verb,"north") == 0)          
        {           
        if (strcmp(loc->north,"nothing") == 0)//make sure theres a location to the north
            return invalidDirection(loc);      //if not call invalid direction
        return findLocation(loc->north);       //if there is one return it
        }
    else if (strcmp(verb,"south") == 0)
        {
        if (strcmp(loc->south,"nothing") == 0)//same as above 
            return invalidDirection(loc);
        return findLocation(loc->south);
        }
    else if (strcmp(verb,"east") == 0)
        {
        if (strcmp(loc->east,"nothing") == 0) 
            return invalidDirection(loc);
        return findLocation(loc->east);
        }
    else if (strcmp(verb,"west") == 0)
        {
        if (strcmp(loc->west,"nothing") == 0) 
            return invalidDirection(loc);
        return findLocation(loc->west);
        }
    else if (strcmp(verb,"get") == 0)       //if the verb involves an action
        {                                   //noun is passed to the appropriate     
        getItem(loc,a,noun);                //function.
        return loc;
        }
    else if (strcmp(verb,"drop") == 0)
        {
        dropItem(loc,a,noun);
        return loc;
        }
    else if (strcmp(verb,"look") == 0)
        {
        look(loc,a);
        return loc;
        }
    else 
        {
        printf("You can't do that. Please choose another command.\n");
        return loc;                 //if none of the expected verbs
        }                           //was inputed, stay in the same place        
    }

//This function returns the location that is passed to it
//and informs the user that the direction was invalid
Location *invalidDirection(Location *loc)
    {
    printf("You cannot fly that direction.\n");
    return loc;
    }

//This function deletes the item from the location
//and adds it to the adventurer's items.
void getItem(Location *loc,Adventurer *a,char *noun)
    {
    int locItemIndex = searchIndex(loc->items,noun);    //Makes sure the item 
    if (locItemIndex == 42)                             //exists
        {                                               //
        printf("Item not found in this location\n");    //
        return;
        }
    else
        loc->items[locItemIndex] = "thereisnoitemhere"; //deletes from location
    
    int adventurerItemIndex = searchIndex(a->items,"thereisnoitemhere"); 
                                                    //finds an empty index
    a->items[adventurerItemIndex] = noun;           //replaces empty index w/ item
    printf("Picked up %s\n",noun);
    return;
    }

//This function deletes the item from the adventurer's items
//and adds it to the location's items.
void dropItem(Location *loc,Adventurer *a,char *noun)
    {
    int advItemIndex = searchIndex(a->items,noun);  //Mades sure the item
    if (advItemIndex == 42)                         //exists
        {                                           //  
        printf("You do not have this item.\n");     //
        return;
        }
    else
        a->items[advItemIndex] = "thereisnoitemhere"; //deletes from adventurer
    
    int locItemIndex = searchIndex(loc->items,"thereisnoitemhere");
                                                    //finds an empty index
    loc->items[locItemIndex] = noun;                //replaces empty index w/ item
    printf("Dropped %s\n",noun);
    return;
    }

//This function returns the first index in the array
//passed to it that contains the string passed to it.
int searchIndex(char *items[20],char *noun)
    {
    int i;
    for (i = 0; i < 20; i++)
        {
        if (strcmp(items[i],noun) == 0)
            return i;
        }    
    return 42;//indicates the term was not found.
    }

//This function is called when reading in the world from a file
//it adds an item to the location passed to it
void addItemToLocation(Location *loc,char *item)
    {
    int emptyIndex = searchIndex(loc->items,"thereisnoitemhere");
    loc->items[emptyIndex] = item;
    return;
    }


//Returns either the current location or an adjacent location
//contains all options available at the location Mount Moon
//(just like basicLogic, but you can't go east without the flashlight.)
Location *moonLogic(Location *loc,Adventurer *a,char *verb,char *noun)
    {
    loc->visited = 1;
    int hasFlashlight = 0;
    if (searchIndex(a->items,"flashlight") != 42) //if searchIndex returns 42, the
        hasFlashlight = 1;                    // flashlight was Not found
    if (hasFlashlight == 0) 
        {
        if (strcmp(verb,"east") == 0)
            {
            printf("It is too dark to find the way out without a flashlight!\n");
            return loc;
            }
       }
    return basicLogic(loc,a,verb,noun);
    }

//Returns either the current location or an adjacent location
//contains all options available at the location Fuschia City.
//(just like basicLogic, but you cant go west without Gyarados.)
Location *fuschiaLogic(Location *loc,Adventurer *a,char *verb,char *noun)
    {
    loc->visited = 1;
    int hasGyarados = 0;
    if (searchIndex(a->items,"Gyarados") != 42) //if searchIndex returns 42, the
        hasGyarados = 1;                   // Gyarados was Not found
    if (hasGyarados == 0) 
        {
        if (strcmp(verb,"west") == 0)
            {
            printf("You cannot make it accross the ocean! You must surf across on a water pokemon.\n");
            return loc;
            }
        }
    return basicLogic(loc,a,verb,noun);
    }

//Returns either the current location or an adjacent location
//contains all options available at the location Indigo Plateau
//(just like basicLogic but it ends the game if you have all items
//and tells you you won.)
Location *indigoLogic(Location *loc,Adventurer *a,char *verb,char *noun)
    {
    loc->visited = 1;
    if (countItems(a->items) == 12)
        {
        printf("You brought Ash all of his missing items! Just in time. You finish\n");
        printf("off the elite for to win the championship for Ash. Good job! \n");
        printf("        -------- You Have Won The Game --------\n");
        return 0;
        }
    else
        printf("You don't have all the items Ash needs to win! \n");
    return basicLogic(loc,a,verb,noun);
    }

//Returns either the current location or an adjacent location
//contains all options available at the location Pallet Town
//(Just like basicLogic but you can't go south without Gyarados.)
Location *palletLogic(Location *loc,Adventurer *a,char *verb,char *noun)
    {
    loc->visited = 1;
    int hasGyarados = 0;
    if (searchIndex(a->items,"Gyarados") != 42) //if searchIndex returns 42, the
        hasGyarados = 1;                   // Gyarados was Not found
    if (hasGyarados == 0) 
        {
        if (strcmp(verb,"south") == 0)
            {
            printf("You cannot make it accross the ocean! You must surf across on a water pokemon.\n");
            return loc;
            }
       }
    return basicLogic(loc,a,verb,noun);
    }
//returns the number of items in the array of strings
//(number of strings that aren't "thereisnoitemhere")
int countItems(char *items[20])
    {
    int count = 0;
    int i;
    for (i = 0; i < 20; i++)
        {
        if (strcmp(items[i],"thereisnoitemhere") != 0) //if there's an actual item
            count++;                                   //increment count
        }
    return count;
    }

//This function prompts the user for input and returns
//the resulting location from that input.
//It returns 0 if the game is won, lost, or quit.
Location *gameCore(Location *loc,Adventurer *adv)
    {
    char *noun;
    char *verb;
    if (loc->visited == 0)
        printf("%s \n",loc->longer);    //display long description if its a new place
    else
        {
        printf("You are in ");
        printf("%s. \n",loc->shorter);  //otherwise show the short description
        }
    if (adv->strength == 0)             //end game if adventurer is out of strength
        {
        printf("You lost all your strength points and fainted. Ash lost the battle.\n");
        printf("        --------GAME OVER--------\n");
        return 0;
        }
    printf("What would you like to do?\n"); //
    verb = readToken(stdin);
    if (strcmp(verb,"north") == 0 || strcmp(verb,"south") == 0 || strcmp(verb,"east") == 0 || strcmp(verb,"west") == 0 || strcmp(verb,"look") == 0) 
        {
        noun = "none";
        loc = logic(loc->logic,loc,adv,verb,noun);  //tries to carry out a command
        }                                           //that doesn't need a noun
    else if (strcmp(verb,"q") == 0 || strcmp(verb,"quit") == 0)
        {
        printf("Are you sure you want to quit?\n");
        verb = readToken(stdin);
        if (strcmp(verb,"yes") == 0)
            return 0;
        }
    else
        {                                           //if a noun is required,
        printf("%s what?\n",verb);                  //ask for the noun
        noun = readToken(stdin);                    
        loc = logic(loc->logic,loc,adv,verb,noun);  //and call the function 
        }                                           //appropriately
    if (loc == 0)               //if loc == 0, the game has been won, so stop the
        return 0;               //gameplay.
    return loc;
    }
