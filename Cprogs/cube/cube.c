#include <stdio.h>
char faces[6][3][3];
int r(char what);
int l(char what);
int u(char what);
char c;
char a;


int main() {
  c = 'C';
  a = 'A';
  readcube();
  solve1();
  solve2();
  solve3();
}

int readcube() {
  FILE *fptr;
  int i,j,k;
  fptr = fopen("./cube.txt", "r");
  for(i=0;i<6;i++) {
    for(j=0;j<3;j++) {
      for(k=0;k<3;k++) {
	fscanf(fptr, "%c",&faces[i][j][k]);
      }
      fscanf(fptr, "\n");
    }
    fscanf(fptr, "\n");
  }
}

int solve1() {
  r('C');
  u('C');
  u('C');
  r('A');
  u('A');
  r('C');
  u('A');
  r('A');
  u('A');
  printcube();
}

int solve2() {

}

int solve3() {

}

int r(char what) {
  int tmp1,tmp2,tmp3,i,j;
  if(what == 'C') {
    tmp1 = faces[0][0][2];
    tmp2 = faces[0][1][2];
    tmp3 = faces[0][2][2];
  
    for(i=0;i<3;i++) {
      for(j=0;j<3;j++) {
	faces[i][j][2] = faces[i+1][j][2];
      }
    }

    faces[3][0][2] = tmp1;
    faces[3][1][2] = tmp2;  
    faces[3][2][2] = tmp3; 
    
  }

  else {
    r('C');
    r('C');
    r('C');
  }
}


int l(char what) {
  int tmp1,tmp2,tmp3,i,j;
  if(what == 'A') {
    tmp1 = faces[0][0][0];
    tmp2 = faces[0][1][0];
    tmp3 = faces[0][2][0];
  
    for(i=0;i<3;i++) {
      for(j=0;j<3;j++) {
	faces[i][j][0] = faces[i+1][j][0];
      }
    }

    faces[3][0][0] = tmp1;
    faces[3][1][0] = tmp2;  
    faces[3][2][0] = tmp3; 
    
  }
  else {
    l('A');
    l('A');
    l('A');
  }
}

int u(char what) {
  int tmp1,tmp2,tmp3;
  tmp1 = faces[1][0][0];
  tmp2 = faces[1][0][1];
  tmp3 = faces[1][0][2];
  int j;
  /* 2 = 6; 
  6 = 4;
  4 = 5;
  5 = 2; */
  if(what == 'C') {
    for(j=0;j<3;j++) {
      faces[1][0][j] = faces[5][0][j];
      faces[5][0][j] = faces[3][0][j];
      faces[3][0][j] = faces[4][0][j];
    }
    faces[4][0][0] = tmp1;
    faces[4][0][1] = tmp2;
    faces[4][0][2] = tmp3;
  }
    else {
      u('C');
      u('C');
      u('C');
    }
}

int d(char what) {

}

int f(char what) {

}


int b(char what) {

}



int printcube() {
  int i,j,k;
  for(i=0;i<6;i++) {
    for(j=0;j<3;j++) {
      for(k=0;k<3;k++) {
	printf("%c",faces[i][j][k]);
      }
      printf("\t");
    }
    printf("\n");
  }
}
