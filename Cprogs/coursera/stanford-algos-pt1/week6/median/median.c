#include <stdio.h>
#define SIZE 10000
int hlow[SIZE/2+1];
int h_high[SIZE/2+1];
int elems_in_high=0;
int elems_in_low=0;
int mod;
void insert_elem(int which, int number);
int main() {
  //("entered main\n");
  initialize();
  read_compute();
  return 1;
}
int read_compute() {
  int i,j,r,a,total=0;
  FILE *fptr;
  int max_of_low;
  fptr=fopen("./a.txt", "r");
  for(i=0;i<SIZE;i++){
    fscanf(fptr, " %d\n",&j);
    max_of_low=hlow[0];
    if(max_of_low>=j) {
      insert_elem(0,j);
      elems_in_low++;
    }
    else {
      insert_elem(1,j);
      elems_in_high++;
    }
    if((elems_in_high - elems_in_low) >= 2) {
      r=extract_min(j);
      insert_elem(0 ,r);
      elems_in_low++;
      elems_in_high--;
    }
    else if(elems_in_low-elems_in_high>=2) {
      r=extract_max();
      insert_elem(1,r);
      elems_in_high++;
      elems_in_low--;
    }
    if(elems_in_low==elems_in_high) { //elems are even 
      mod=hlow[0];
    }
    else {
      if(elems_in_low>elems_in_high) {
	mod=hlow[0];
      }
      else {
	mod=h_high[0];
      }
      
    }
    total+=mod;
    //   printf ("mod = %d\n",mod);
   if(i==9999)
     print_heap();
   }
  
  printf("total = %d\n",total);
  printf("answer = %d\n",total%10000);
}
print_heap() {
  int a;
  printf("Hlow: ");
    for(a=0;a<elems_in_low;a++) { 
      printf("%d, ",hlow[a]);
    }
    printf("\t");
    printf("Hhigh : ");
    for(a=0;a<elems_in_high;a++)  {
      printf("%d, ",h_high[a]);
    }
    printf("\n");
}
int initialize() {
  int i;
  for(i=0;i<SIZE/2;i++) {
    h_high[i]=10001;
    hlow[i]=0;
  }
}

int extract_min(int number) {   
  int min;
  int i;
  int lchild,rchild,temp;
  min=h_high[0];
  i=1;
  lchild = 2;
  rchild = 3;
  h_high[0]=h_high[elems_in_high-1];
  h_high[elems_in_high-1]=10001;
  
  //while( (2*i < elems_in_high) && ((h_high[lchild]<h_high[i-1]) || (h_high[rchild]<h_high[i-1])) ) {
  while(2*i < elems_in_high) {
  
    if(h_high[lchild-1]<h_high[rchild-1]) {
      
      temp=h_high[lchild-1];
      h_high[lchild-1]=h_high[i-1];
      h_high[i-1]=temp;
      i=(i*2);
    }
    else  { /* if (h_high[rchild]<h_high[lchild]) */
      
     temp=h_high[rchild-1];
      h_high[rchild-1]=h_high[i-1];
      h_high[i-1]=temp;
      i=(i*2)+1;
   }
   lchild=i*2;
   rchild=(i*2)+1; 
  }
  
  return min;
 }
 

int extract_max() {
  int max;
  int i;
  int lchild,rchild,temp;
//printf ("BEGIN extract_max\n");
  max=hlow[0];
  i=1;
  hlow[0]=hlow[elems_in_low-1];
  hlow[elems_in_low-1]=0;
  lchild=i*2;
  rchild=(i*2)+1;
  // while( (2*i < elems_in_low) && ((hlow[lchild] > hlow[i-1]) || (hlow[rchild] > hlow[i-1])) ) { 
  while(2*i < elems_in_low) {
    if(hlow[lchild-1]>hlow[rchild-1]) {
      temp=hlow[lchild-1];
      hlow[lchild-1]=hlow[i-1];
      hlow[i-1]=temp;
      i=(i*2);
    }

    else {
      temp=hlow[rchild-1];
      hlow[rchild-1]=hlow[i-1];
      hlow[i-1]=temp;
      i=(i*2)+1;    
    }

    lchild=(i*2);
    rchild=(i*2)+1;
  }
//printf ("END extract_max\n");
  return max;
}

void insert_elem(int which, int number) {
  int i,temp,a;
//printf ("BEGIN insert_elem\n");
   if(which==0) {
     i=elems_in_low+1;
     hlow[i-1]=number;
     while(i>1 && hlow[(i/2)-1] < hlow[(i-1)]) {
       if(h_high[(i/2)-1] != 0 && h_high[i-1]!=0) {
	 temp=hlow[i-1];
	 hlow[i-1]=hlow[(i/2)-1];
	 hlow[(i/2)-1]=temp;
	 }
       i/=2;
     }
   }
   else {
     i=elems_in_high+1;
     h_high[i-1]=number;
     while(i>1 && (h_high[(i/2)-1] > h_high[i-1]) ) {
       if(h_high[(i/2)-1] != 0 && (h_high[i-1]!=0)) {
	 temp=h_high[(i/2)-1];
	 h_high[(i/2)-1]=h_high[(i-1)];
	 h_high[(i-1)]=temp;
       }
       i/=2;
     }
   }
//printf ("END insert_elem\n");
}
