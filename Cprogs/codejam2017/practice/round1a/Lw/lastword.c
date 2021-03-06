#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define T 100
#define SIZE 1000
struct s {
  char val;
  struct s *next;
};
typedef struct s s_t;
int main() {
  char S[SIZE];
  int i;
  int check;
  FILE *fptr;
  FILE *fptr2;
  fptr = fopen("./a.txt", "r");
  fptr2 = fopen("./output.txt", "w");
  fscanf(fptr, "%d",&check);
  printf("%d",check);
  if(check != T) {
    printf("ERROR");
    exit(1);
  }
  for(i=0;i<T;i++) {
    fscanf(fptr, "%s",S);
    last_word(S,fptr2,i+1);
  }
}

last_word(char *S, FILE *fp2, int cnum) {
  int i,slen;
  slen = strlen(S);
  s_t *head, *tail, *tmp;
  head = malloc(sizeof(s_t));

  head->val = S[0];
  head->next = NULL;
  tail = head;
  s_t *t;
  for(i=1;i<slen;i++) {
    t = malloc(sizeof(s_t));
    t->val = S[i];
    if(S[i] >= head->val) {
      tmp = head;
      head = t;
      head->next = tmp;
      t = NULL;
    }
    else {
      tail->next = malloc(sizeof(s_t));
      tail->next = t;
      tail = t;
      tail->next = NULL;
    }
  }
  tmp = head;
  fprintf(fp2, "Case #%d: ",cnum);
  while(tmp!=NULL) {
    fprintf(fp2, "%c",tmp->val);
    tmp = tmp->next;
  }
  fprintf(fp2, "\n");
}
