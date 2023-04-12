/**************************
*Reeves Farrell
*CPSC 2310 Spring 23
*UserName: jrfarre@clemson.edu
*Instructor:  Dr. Yvon Feaster
*************************/

#include <stdio.h>

struct NODE {
    int a;
    struct NODE *b;
    struct NODE *c;
};

struct NODE nodes[5] = {
    {9, nodes + 4, NULL},
    {32, nodes + 2, nodes + 3},
    {16, NULL, nodes + 4},
    {41, nodes + 1, nodes},
    {81, nodes + 3, nodes + 1}
};

struct NODE *np = nodes + 2;
struct NODE **npp = &nodes[1].b;

int main() {

    printf("nodes\t%p\n", nodes);
    printf("nodes[3].a\t%d\n", nodes[3].a);
    printf("nodes[3].c\t%p\n", nodes[3].c);
    printf("nodes[3].c->a\t%d\n", nodes[3].c->a);
    printf("(*nodes).a\t%d\n", (*nodes).a);
    printf("nodes->a\t%d\n", nodes->a);
    printf("nodes[3].b->b\t%p\n", nodes[3].b->b);
    printf("&nodes[3].a\t%p\n", &nodes[3].a);
    printf("&nodes[3].c\t%p\n", &nodes[3].c);
    printf("&nodes[3].c->a\t%p\n", &nodes[3].c->a);
    printf("&nodes->a\t%p\n", &nodes->a);
    printf("np\t%p\n", np);
    printf("np->a\t%d\n", np->a);
    printf("np->c->c->a\t%d\n", np->c->c->a);
    printf("npp\t%p\n", npp);
    printf("*npp\t%p\n", *npp);
    printf("(*npp)->a\t%d\n", (*npp)->a);
    printf("&np\t%p\n", &np);
    printf("&np->a\t%p\n", &np->a);
    printf("&np->c->c->a\t%p\n", &np->c->c->a);
    
    return 0;
}
