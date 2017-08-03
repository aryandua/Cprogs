#include <stdio.h>
#include <stdlib.h>

//Structures:
struct elist { // represents a list of all edges for a certain node
  int number;
  struct elist *next;
};
typedef struct elist t_elist;

struct node { // represents a node
  int vno;
  int orig_vno;
  int ecount;
  struct elist *edges;
};
typedef struct node t_node;

//Functions:
void create_edge(int u, int v, int sz);
void get_scc_leaders(int *arr, int elems);
void condensate(void);
int divide_sort(int *arr,int n);
void init(void);
int getopp(int index);
void pop_graph(void);
void invert(void);
void newG_by_fintime(void);
void dfs_loop (t_node *graph_new); 
void isitsat(void);
void dfs (t_node *G, int i);
void getvaln(char *filename);
void check(int val);
void condensate(void);

//Declarations:
t_node *graph;      //original graph
t_node *graph_inv;  //inverted graph
t_node *graph_new;  //graph by fintime
t_node *graph_cond; //condensated graph
int *unique_scc;    //name of leaders of all scc's
int *leader;        //leader of every node
int *fintime;       //finishing time of every node
int t = 0;          //used for fintime array
int Start = 0;      //used to represent start
int *explored;      // Marking as explored
int n;

FILE *fptr;

int main(int argc, char *argv[]) { //argv has <filename> as second argument
  check(argc);                     // check if user has used program correctly
  getvaln(argv[1]);                // fscanf value of n
  init();                          // initialize the graphs 
  pop_graph();                     // Populate graph
  invert();                        // Populate the inverse Graph
  dfs_loop(graph_inv);             // Call dfs_loop on G_inv
  newG_by_fintime();               // Change G based on Finish Time of Ginv
  dfs_loop (graph_new);            // Call dfs_loop on Gnew
  isitsat();                       // Check if it is satisfiable (exits if unsat)
  condensate();                    // Condense every SCC into 1 node
}

void check(int val) {
  if(val != 2) {
    printf("Usage: rad <filename>\n");
    exit(1);
  }
  return;
}

void getvaln(char *filename) {
  fptr = fopen(filename, "r");
  fscanf(fptr, "%d\n",&n);
  return;
}

void pop_graph(void) {
  int vcurrent = 0;
  int vread, eread;
  t_elist *temp; 
 
  while (!feof(fptr)) {
    fscanf (fptr, " %d", &vread);
    fscanf (fptr, " %d\n", &eread);
    if (vread != vcurrent) { /*read a new node */
      temp = NULL;
      vcurrent = vread;
      (graph[vread-1]).edges=(t_elist*) malloc(sizeof(t_elist));
      temp = (graph[vread-1]).edges;
      (graph[vread-1]).edges->number = eread;
      graph[vread-1].ecount++;
    }
    else {
      temp->next = (t_elist*) malloc(sizeof(t_elist));
      temp->next->number = eread;
      graph[vread-1].ecount++;
      temp = temp->next;
    }
  }
  fclose(fptr);
}

void init(void) {
  graph = malloc(sizeof(t_node) * n);
  graph_inv = malloc(sizeof(t_node) * n);
  graph_new = malloc(sizeof(t_node) * n);

  leader = malloc(sizeof(int) * n);
  fintime = malloc(sizeof(int) * n);
  explored = malloc(sizeof(int) * n);

  int i;
  for (i=0; i < n; i++) {
    graph[i].vno = i+1;
    graph[i].ecount = 0;
    graph[i].edges = NULL;
    
    graph_inv[i].vno = i+1;
    graph_inv[i].ecount = 0;
    graph_inv[i].edges = NULL;
    
    graph_new[i].vno = i+1;
    graph_new[i].ecount = 0;
    graph_new[i].edges = NULL;
  }
}


void invert(void) {
  int i;
  t_elist *temp;  /* tmp pointer to traverse over edges of each node of orignal Graph */
  t_elist *temp2; /* tmp2 pointer to traverse over the edges of each node */
  int e;
  for(i=0;i<n;i++) {
    temp=graph[i].edges;
    while(temp != NULL) {
      e = temp->number;
      temp2 = graph_inv[e-1].edges;
      if (temp2 == NULL) {
	(graph_inv[e-1]).edges = (t_elist*) malloc(sizeof(t_elist));
	(graph_inv[e-1]).edges->number = graph[i].vno;
	(graph_inv[e-1]).edges->next = NULL;
      }
      else {
	while (temp2->next != NULL)
	  temp2 = temp2->next;
	temp2->next = (t_elist*) malloc(sizeof(t_elist));
	temp2->next->number = graph[i].vno;
	temp2->next->next = NULL;
      }
      graph_inv[e-1].ecount++;
      
      temp=temp->next;
    }
  }
}


void newG_by_fintime (void) { /* Populate new G based on Finish Time of Ginv */
int i,v,k,x,y;
  t_elist *temp, *temp2 ;
  for (i = 0; i < n; i++) {
    v = fintime[i];
    
    graph_new[v-1].orig_vno =  graph_new[i].vno;
    graph_new[v-1].vno = v;
    graph_new[v-1].ecount = graph[i].ecount;
    
    temp = graph[i].edges;
    
    if (temp == NULL) {
      graph_new[v-1].edges = NULL;
    }
    else {
      temp2 = (t_elist*) malloc(sizeof(t_elist));
      graph_new[v-1].edges = temp2;
      for (k=0; k < graph[i].ecount; k++) {
	x = temp->number;
	y = fintime[x-1];
	temp2->number = y;

	if (temp->next != NULL) 
	  temp2->next = (t_elist*) malloc(sizeof(t_elist));
	else
	  temp2->next = NULL;

	temp2 = temp2->next;
	temp = temp->next;
      }
      temp2 = NULL;
    }
  }
}

void isitsat(void) {
  int i;

  for (i = 0; i < n; i++) {
    if(leader[i] == leader[getopp(i)]) {
	printf("UNSATISFIABLE. %d in the same SCC as %d\n",i,getopp(i));
	exit(1);
    }
  }
  printf("SATISFIABLE\n");
  return;
}

int getopp(int index) {
  int target = (graph_new[index].orig_vno)-1;
  int a = ((n) - (target));
  int i;
  for(i=0;i<n;i++) {
    if(graph_new[i].orig_vno == a)
      return i;
  }
  printf("ERROR!\n");
  exit(1);
}

void dfs_loop (t_node *G) {
  int i;
  
  for (i = 0 ; i < n; i++)
    explored[i] = 0;
  
  for (i = n-1; i >= 0; i--) {
    if (explored[i] == 0) {
      Start =  i;
      dfs (G, i);
    }
  }
}

void dfs (t_node *G, int i) {
  
  t_elist *temp;
  int j;
  
  // mark node i as explored;
  explored[i] = 1;
  
  // set it's leader as Start
  leader[i] = Start;
  
  /* for j = (all edges from i) { 
     if (j is unexplored) 
     dfs(G,j); */
  
  
  temp = G[i].edges;
  while (temp != NULL) {
    j = temp->number;
    if (explored[j-1] == 0)
      dfs (G, j-1);
    temp = temp->next;
  }
  
  t++;
  fintime[i] = t;
}

void condensate(void) {
  int i;
  t_elist *tmp;
  int *all_scc_leaders;
  
  int no_of_scc = unique_elements(leader, n);
  all_scc_leaders = malloc(sizeof(int) * no_of_scc);
  get_scc_leaders(all_scc_leaders, no_of_scc);
  graph_cond = malloc(sizeof(t_node) * no_of_scc);

  for(i = 0; i < no_of_scc; i++) {
    graph_cond[i].orig_vno = 0;
    graph_cond[i].vno = all_scc_leaders[i];
    graph_cond[i].edges = NULL;
    graph_cond[i].ecount = 0; 
  }
  for(i = 0; i < n; i++) {
    tmp=graph_new[i].edges;
    while(tmp != NULL) {
      if(leader[tmp->number-1] != leader[i])
	create_edge(leader[i], leader[tmp->number-1], no_of_scc);
      tmp=tmp->next;
    }
  }
  print_graph(graph_cond, no_of_scc);
}

void create_edge(int u, int v, int sz) {
  t_elist *tmp;
  int i;

  for(i=0;i<sz;i++) {
    if(graph_cond[i].vno == leader[u]+1)
       break;
  }

  if(graph_cond[i].edges==NULL) 
    graph_cond[i].edges=malloc(sizeof(t_elist));

  tmp=graph_cond[i].edges;
  tmp->next=NULL;
  graph_cond[i].ecount++;

  while(tmp->next != NULL) 
    tmp=tmp->next;


  tmp->next=malloc(sizeof(t_elist));
  tmp=tmp->next;
  tmp->number = v;
  tmp->next=NULL;
}

void get_scc_leaders(int *arr, int elems) {
  int i,count=0;
  int prev=arr[0];

  divide_sort(arr, elems);

  for(i=1;i<elems;i++) {
    if(prev != leader[i]) {
      arr[count] = leader[i];
      count++;
    }
  }
}


int divide_sort(int *arr,int n) {
  int *left=arr;
  int *right=arr+n/2;
  int k=0;
  int i=0;
  int j=0;
  int count, n1, n2;
  int newarr[n];
  
  if(n==1) return;
  
  n1 = n/2;
  n2 = n - n1;
  
  divide_sort(left,n1);
  divide_sort(right,n2);
  
  while  ( k < n ) {
    if (left[i] > right[j]) {
      newarr[k] = right[j];
      j++;
      k++;
      if (j >= n2) {
	for (count = i; count < n1; count++) {
	  newarr[k] = left[i];
	  i++;
	  k++;
	}
      }
    }
    else {
      newarr[k]=left[i];
      i++;
      k++;
      if (i >= n1) {
	for (count = j; count < n2; count++) {
	  newarr[k] = right[j];
	  j++;
	  k++;
	}
      }
    }
  }
  for(count=0;count<n;count++) {
    arr[count] = newarr[count];
  }
}

int unique_elements(int arr[], int len) {

    int counted[len], j, n, count, flag;

    counted[0] = arr[0]; 

    count = 1;/*one element is counted*/

        for(j=0; j <= len-1; ++j) {
        flag = 1;;
        /*the counted array will always have 'count' elements*/
        for(n=0; n < count; ++n) {
            if(arr[j] == counted[n]) {
                flag = 0;
            }
        }
        if(flag == 1) {
            ++count;
            counted[count-1] = arr[j];
        }
    }
    return count;
}


print_graph(t_node *G, int length) {
  int i;
  t_elist *temp;
  
  printf ("\n***** BEGIN *****");
  for(i=0;i<length;i++) {
    printf ("\nv = %d ", G[i].vno);
    printf("orig_vno = %d ",G[i].orig_vno);
    temp = G[i].edges;
    printf ("\( ");
    while (temp) {
      printf ("%d ",temp->number);
      temp = temp->next;
    }
    printf (")");
    printf (" (ecount = %d)",G[i].ecount);
  }
  printf ("\n***** END *****\n");
}
