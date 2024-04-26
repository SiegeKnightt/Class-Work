// Program adapted from Question 9 at end of Chapter 3 of OSPP

#include <stdio.h>
#include <unistd.h>

int main(){
  int child = fork();
  int x = 5;

  if( child == 0 ){
    x += 5;
  }else{
    child = fork();
    x += 10;
    if( child ){
      x += 5;
    }
  }
  return 0;
}