
extern Node *world;
Location *newEmptyLocation(void);
Adventurer *newAdventurer(void);
Location *findLocation(char *name);
Location *logic(char *s,Location *loc,Adventurer *a,char *verb,char *noun);
Location *basicLogic(Location *loc,Adventurer *a,char *verb,char *noun);
Location *invalidDirection(Location *loc);
void getItem(Location *loc,Adventurer *a,char *noun);
void dropItem(Location *loc,Adventurer *a,char *noun);
int searchIndex(char *items[20],char *noun);
void addItemToLocation(Location *loc,char *item);
Location *indigoLogic(Location *loc,Adventurer *a,char *verb,char *noun);
Location *moonLogic(Location *loc,Adventurer *a,char *verb,char *noun);
Location *fuschiaLogic(Location *loc,Adventurer *a,char *verb,char *noun);
Location *palletLogic(Location *loc,Adventurer *a,char *verb,char *noun);
int countItems(char *items[20]);
Location *gameCore(Location *loc,Adventurer *a);
