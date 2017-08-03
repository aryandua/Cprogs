#include <stdio.h>
#include <strings.h>
#include <string.h>
#define SIZE 100
int main() {
  FILE *fptr, *fptr2;
  fptr = fopen("./a.txt", "r");
  fptr2 = fopen("./output.txt", "w");
  int i;
  char buffer[2000];
  int a;
  for(i=0;i<SIZE;i++) {
    fscanf(fptr, "%s",buffer);
    a = pancake(strlen(buffer), buffer);
    fprintf(fptr2, "Case #%d: %d\n",i+1,a);
  }
}

int pancake(int length, char *buffer) {
  int done = 0;
  char init,not_init;
  int found;
  int a;
  int i;
  int count = 0;
  done = 1;
 for(a=0;a<length;a++) {
      if(buffer[a] == '-')
	done = 0;
    }
  while(!done) {
    count++;
    init = buffer[0];
    found = 0;
    a=0;
    i=0;
    while(!found || i == length) {
      if(buffer[a] == init)
	i++;
      else 
	found = 1;
      a++;
    }
    if(init == '+') 
      not_init = '-';
    else 
      not_init = '+';
    for(a=0;a<i;a++) 
      buffer[a] = not_init;
    
    done = 1;

    for(a=0;a<length;a++) {
      if(buffer[a] == '-')
	done = 0;
    }
  }
  return count;
}
