
extern Node *world;
void printInstructions();
void printIntro();
Location *readLocation(FILE *fp);
void displayLocation(Location *loc);
void displayItems(char *items[20]);
void look(Location *loc,Adventurer *a);
void printLocationName(char *s);
