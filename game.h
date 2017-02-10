//This structure will hold all information 
//relevant to a single location.
#ifndef LOCATION_STRUCT
#define LOCATION_STRUCT
typedef struct location
    {
    char *name;
    int visited;
    char *longer;
    char *shorter;
    char *north;
    char *south;
    char *east;
    char *west;
    char *logic;
    char *items[20];
    } Location;
#endif

//This structure will hold a location and
//a next node
#ifndef NODE_STRUCT
#define NODE_STRUCT
typedef struct node
    {
    Location *value;
    struct node *next;
    } Node;
#endif

//This structure will hold all information
//relevant to an adventurer.
#ifndef ADVENTURER_STRUCT
#define ADVENTURER_STRUCT
typedef struct adventurer
    {
    int score;
    int strength;
    char *items[20];
    } Adventurer;
#endif
//declare the external variable
Node *world;
