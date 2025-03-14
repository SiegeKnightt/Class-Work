/* create.c -- Example multi-threaded program using OSPP authors' thread routines
 *
 * Compile with
 *    > gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS create.c -c -o create.o
 *    > gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS thread.c -c -o thread.o
 *    > gcc -pthread create.o thread.o -o create
 * Run with
 *    > ./create
 * or
 *    > valgrind --tool=helgrind ./create
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "thread.h"

#define NTHREADS 2

void * go (void *vp);

double x;

int main(int argc, char **argv) {
    int i;
    thread_t threads[NTHREADS];

    for (i = 0; i < NTHREADS; i++) {
        thread_create_p(&(threads[i]), &go, NULL);
    }
    for (i = 0; i < NTHREADS; i++) {
        thread_join(threads[i]);
    }

    return 0;
}

void * go (void *vp) {
    double y;

    printf( "address of x is %p, address of y is %p\n", &x, &y );

    thread_exit(0);

    // Not reached
    return NULL;
}