/* CPSC 3220 Fall 2023 - visual log of reader/writer actions
 *
 * this program can be used to demonstrate that the pthread
 *   Read-Write Lock allows overlapped reads but enforces
 *   mutually exclusive writes
 *
 * MISSING CODE TO BE FILLED IN BY STUDENTS
 *
 *  (1) synchronization calls for record()
 *
 *  (2) post-processing the action log by adding '|' characters
 *        to show thread durations before printing
 *
 *
 * synchronization state
 *
 *   rw_lock - pthread Read-Write Lock
 *
 *   m_lock  - pthread Mutex Lock
 *
 *
 * shared state protected by the Read-Write Lock
 *
 *   the reader/writer threads do not have shared state but are
 *     merely used to exercise the pthread Read-Write Lock
 *
 *
 * shared state protected by the Mutex Lock
 *
 *   action_log - a character array with one row per action
 *                  and one column per thread
 *   log_index  - current row
 *
 *   note that because there is a limit on the number of threads
 *     (and thus actions) in this program, the log can be a two-
 *     dimensional table that easily lends itself to printing
 *
 *   in the general case of a log (a.k.a. flight recorder),
 *     it would be an array of fixed size that records
 *     (thread id, action) pairs; it would wrap around and
 *     overwrite old entries once full
 *
 *
 * input
 *
 *   a command line string of RW- characters, such as R-RW
 *
 *   character meanings are:
 *     'R' - creates a reader thread
 *     'W' - creates a writer thread
 *     '-' - causes a pause in the thread creatioin
 *
 *
 * example compilation and running
 *
 *   gcc -Wall log.c -pthread -o log
 *   ./log RRWRRW   
 *
 *
 * example output for the RRWRRW input string
 *
 *   thread 0 starts read
 *   thread 1 starts read
 *   thread 0 ends read
 *   thread 1 ends read
 *   thread 2 starts write
 *   thread 2 ends write
 *   thread 5 starts write
 *   thread 5 ends write
 *   thread 3 starts read
 *   thread 4 starts read
 *   thread 3 ends read
 *   thread 4 ends read
 *   
 *   visual log of actions by thread
 *   
 *     0  1  2  3  4  5
 *     R
 *     |  R
 *     E  |
 *        E
 *           W
 *           E
 *                    W
 *                    E
 *              R
 *              |  R
 *              E  |
 *                 E
 *
 *   note that thread scheduling and thus the outputs can
 *     change on different runs with the same input string
 *
 *
 * reader/writer priority
 *
 *   normally a pthread Read-Write Lock has reader priority, but
 *     to prevent writer starvation the pthread Read-Write Lock
 *     used below is initialized with the attribute
 *     PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP
 *
 *   you can change the initialization attribute to NULL to get
 *     reader priority, and you can add pauses before later
 *     arriving readers to allow any waiting writers to run
 */

#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>


/* parameters (optionally these could be */
/*  read in from a configuration file)   */

#define MAX_THREADS 20
#define READER_SLEEP_TIME 2
#define WRITER_SLEEP_TIME 2
#define CREATE_SLEEP_TIME 1


/* synchronization state */

pthread_rwlock_t     rw_lock;
pthread_rwlockattr_t attr;
pthread_mutex_t      m_lock;


/* shared state and global thread count */

char action_log[2*MAX_THREADS][MAX_THREADS];
int log_index = 0;
int thread_count = 0;


/* record an action in the action log */
/*   NEEDS SYNCHRONIZATION CALLS      */

void record( long tid, int action ){

  pthread_mutex_lock(&m_lock);
  action_log[log_index][(int) tid] = (char) action;
  log_index++;
  pthread_mutex_unlock(&m_lock);
}


/* print the action log in a formated way, with '|' characters */
/*   added to show the duration of a reader or writer          */

void print_log( void ){
  int i, j, active;


  /* traverse the action log column by column, adding '|' */
  /*   characters in the rows between an R or W and an E  */
  /*   to visually illustrate the duration of a thread    */

  for( i = 0; i < thread_count; i++ ){

    /* NEEDS CODE TO ADD '|' CHARACTERS */
    active = 0;

    for (j = 0; j < log_index; j++) {

      if (action_log[j][i] == 'W' || action_log[j][i] == 'R') {

        active = 1;
      }
      else if (action_log[j][i] == 'E') {

        active = 0;
      }
      else if (active) {

        action_log[j][i] = '|';
      }
    }
  }


  /* print the action log as a table with thread id headers */

  for( j = 0; j < thread_count; j++ ){
    printf( "%3d", j );
  }
  printf( "\n" );
  for( i = 0; i < log_index; i++ ){
    for( j = 0; j < thread_count; j++ ){
      printf( "  %c", action_log[i][j] );
    }
    printf( "\n" );
  }
}


/* function to be executed by reader threads */

void *reader( void *thread_id ){
  pthread_rwlock_rdlock( &rw_lock );
  record( (long) thread_id, (int) 'R' );
  printf( "thread %ld starts read\n", (long)thread_id );
  sleep( READER_SLEEP_TIME );
  printf( "thread %ld ends read\n", (long)thread_id );
  record( (long) thread_id, (int) 'E' );
  pthread_rwlock_unlock( &rw_lock );
  return NULL;
}


/* function to be executed by writer threads */

void *writer( void *thread_id ){
  pthread_rwlock_wrlock( &rw_lock );
  record( (long) thread_id, (int) 'W' );
  printf( "thread %ld starts write\n", (long)thread_id );
  sleep( WRITER_SLEEP_TIME );
  printf( "thread %ld ends write\n", (long)thread_id );
  record( (long) thread_id, (int) 'E' );
  pthread_rwlock_unlock( &rw_lock );
  return NULL;
}


/* test driver */

int main( int argc, char **argv ){
  pthread_t threads[MAX_THREADS];
  int i, rc;

  if( argc != 2 ){
    printf( "reader-writer string should be provided\n" );
    printf( "as a command argument, e.g., R-RWR\n" );
    exit( 0 );
  }


  /* initialization of pthread synchronization objects */

  pthread_rwlockattr_setkind_np( &attr,
    PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP );
  // pthread_rwlock_init( &rw_lock, NULL );   // reader preference
  pthread_rwlock_init( &rw_lock, &attr );   // writer preference
  pthread_mutex_init( &m_lock, NULL );


  /* fill the action log with spaces */

  memset( (void *) action_log, ' ', 2*MAX_THREADS*MAX_THREADS );


  /* traverse the input string and create threads or pause, as   */
  /*   indicated                                                 */
  /* ignore RW inputs beyond the maximum number of threads       */
  /* exit the program if a thread cannot be successfully created */

  for( i = 0; i < strlen( argv[1] ); i++ ){

    if( thread_count == MAX_THREADS ) break;

    switch( argv[1][i] ){

      case( 'R' ):
        rc = pthread_create( &threads[thread_count], NULL, &reader,
                             (void *)((long)thread_count) );
        if( rc ){
          printf( "** could not create thread %d\n", i );
          exit( -1 );
        }
        thread_count++;
        break;

      case( 'W' ):
        rc = pthread_create( &threads[thread_count], NULL, &writer,
                             (void *)((long)thread_count) );
        if( rc ){
          printf( "** could not create thread %d\n", i );
          exit( -1 );
        }
        thread_count++;
        break;

      case( '-' ):
        /* merely causes a sleep */
        break;

      default:
        printf( "stray character in command line input, \'%c\'",
          argv[1][i] );
        printf( " (= %d decimal)\n", (int) argv[1][i] );
        exit( -1 );
    }

    sleep( CREATE_SLEEP_TIME );
  }


  /* wait for all created threads to end by joining */

  for( i = 0; i < thread_count; i++ ){
    rc = pthread_join(threads[i], NULL);
    if( rc ){
      printf( "** could not join thread %d\n", i );
      exit( -1 );
    }
  }


  /* garbage collect pthread synchronization state */

  pthread_mutex_destroy( &m_lock );
  pthread_rwlock_destroy( &rw_lock );


  /* print the action log */

  printf( "\nvisual log of actions by thread\n\n" );
  print_log();

  return 0;
}
