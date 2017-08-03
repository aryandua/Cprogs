#include <stdio.h>
#include <stdlib.h>
#define T int
#define TTYPE %d
struct ll {
  T val;
  struct ll *next;
};
typedef struct ll ll_t;

int main() {
  ll_t *head, *tail;
  head = malloc(sizeof(ll_t));
  tail = malloc(sizeof(ll_t));
  head->next = NULL;
  tail = head;

  insert_node_at_end( tail, 10);
  printlist(head);

  insert_node_at_end(tail, 12);
  printlist(head);

  insert_node_at_end(tail, 14);
  printlist(head);

  insert_node_at_end(tail, 15);
  printlist(head);

  delete_node(head, 14);
  printlist(head);

  delete_node(head, 10);
  printlist(head);  
}

insert_node_at_end(ll_t* tail, T new) {
  printf("ADDING %d\n",new);
  tail->next = malloc(sizeof(ll_t));
  tail->next->val = new;
  tail->next->next = NULL;
  tail=tail->next;
}

delete_node(ll_t *head, T del) {
  printf("deleting %d\n",del);
  ll_t *tmp, *deltmp;
  if(head->val == del) {
    deltmp = head;
    head = head->next;
    free(deltmp);
    return;
  }
  tmp = head;
  while(tmp->next->val != del) {
    tmp = tmp->next;
  }
  deltmp = tmp->next;
  tmp->next = tmp->next->next;
  free(deltmp);
  return;
}

printlist(ll_t *head) {
  ll_t *tmp;
  tmp = head;
  while(tmp!=NULL) {
    printf("%d->",tmp->val);
    tmp = tmp->next;
  }
  printf("NULL\n");
}
