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
    char *items[10];
    } Location;
#endif
#ifndef NODE_STRUCT
#define NODE_STRUCT
typedef struct node
    {
    void *value;
    struct node *next;
    } Node;
#endif

#ifndef ADVENTURER_STRUCT
#define ADVENTURER_STRUCT
typedef struct adventurer
    {
    int score;
    int strength;
    char *items[20];
    } Adventurer;
#endif

#ifndef WORLD_GLOBAL
#define WORLD_GLOBAL
extern Node *world;
#endif

//Node prototypes 

Node *newNode(Location *value,Node *next);
Node *newEmptyNode(void);

/* List prototypes */

Node *newEmptyList(void);
Location *head(Node *items);
Node *tail(Node *items);
void setHead(Node *items,Location *s);
void setTail(Node *items,Node *newList);
Node *join(Location *s,Node *rest);
Node *arrayToList(Location **items,int size);
void displayList(Node *items,void (*display)(Location *));
void freeList(Node *items);
