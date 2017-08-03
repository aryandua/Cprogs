#include <stdio.h>
#include <stdlib.h>



int clauses[LITERALS][2];
int clauses_edges[2*LITERALS][2];

int main(int argc, char *argv[]) {
  FILE *fp;

  if(argc == 1 || argc > 2) {
    printf("Usage: rad <filename>\n");
    return;
  }

  fp=fopen(argv[1], "r");

  fill_clauses(fp);
  makesccfile();
  
}

int fill_clauses(FILE *fp) {
  int n;
  int i;
  
  fscanf(fp, "%d\n",&n);
  if(n != LITERALS) {
    printf("LITERALS is incorrect\n");
    exit(1);
  }

  for(i=0;i<LITERALS;i++) {

    fscanf(fp, "%d ",&clauses[i][0]);
    fscanf(fp, "%d\n",&clauses[i][1]);

    clauses[i][0] += LITERALS+1;
    clauses[i][1] += LITERALS+1;

    if(clauses[i][0] > LITERALS)
      clauses[i][0]--;
    if(clauses[i][1] > LITERALS)
      clauses[i][1]--;
  }
  return;
}

int makesccfile() {
  FILE *sccfile;

  int count = 0;

  sccfile = fopen("scc.txt", "w");
  int i,lit1,lit2,notlit1,notlit2;
  fprintf(sccfile,"%d\n",2*LITERALS);

  for(i=0;i<LITERALS;i++) {
    lit1 = clauses[i][0];
    lit2 = clauses[i][1];

    notlit1 = getopp(lit1);
    notlit2 = getopp(lit2);

    clauses_edges[count][0] = notlit1;
    clauses_edges[count][1] = lit2;
    count++;
    clauses_edges[count][0] = notlit2;
    clauses_edges[count][1] = lit1;
    count++;
  }


  for(i=0;i<2*LITERALS;i++) {
    fprintf(sccfile, "%d %d\n",clauses_edges[i][0], clauses_edges[i][1]);
  }
}


int getopp(int l) {
  if(l<LITERALS) 
    return (((l-(LITERALS+1))*(-1))+LITERALS);
  
  else 
    return ((l-LITERALS)*(-1)+(LITERALS+1));
}



