#include <stdio.h>
#include <string.h>

/* A program to test typedefing logic function pointers 
 *    written by John C. Lusth
 *
 * Functions a, b, and z simulate logic functions, but note that they
 *    have different formal parameters and return types than actual
 *    logic functions
 *
 * The decider function takes a string name and returns the matching function
 */

/* create a simple name, Logic, for a logic pointer */

typedef char *(*Logic)(int, char *);

/* logic functions - note the return type and formals match the typedef */

char *
a(int x,char *y)
    {
    printf("a: %d and %s\n",x,y);
    return "done";
    }

char *
b(int x,char *y)
    {
    printf("b: %s and %d\n",y,x);
    return "finished";
    }

char *
z(int x,char *y)
    {
    printf("z: %s/%d\n",y,x);
    return "completed";
    }

/* logic finding function */

Logic decider(char *s)
    {
    Logic g;
    if (strcmp(s,"a") == 0)
        g = a;
    else if (strcmp(s,"b") == 0)
        g = b;
    else
        g = z;
    return g;
    }

int
main(int argc,char **argv)
    {
    Logic c;
    char *s;
    /* looking for function a */
    c = decider("a");
    s = c(5,"howdy");
    printf("%s\n",s);
    /* looking for function b */
    c = decider("b");
    s = c(5,"howdy");
    printf("%s\n",s);
    /* looking for function syzygy (should get default function z) */
    c = decider("syzygy");
    s = c(5,"howdy");
    printf("%s\n",s);
    return 0;
    }
