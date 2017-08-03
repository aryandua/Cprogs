#include <stdio.h>
#define SIZE 7
int hlow[SIZE/2+1];
int h_high[SIZE/2+1];
int elems_in_high=0;
int elems_in_low=0;
int mod[SIZE];
int main() {
  //("entered main\n");
  initialize();
  read_compute();
  return 1;
}
int read_compute() {
  // ("entered read_compute\n");
  int i,j,r,a,total=0;
  FILE *fptr;
  int max_of_low,min_of_high;
  fptr=fopen("./a.txt", "r");
  //("opened file\n");
  for(i=0;i<SIZE;i++){
    //("loop stage: %d\n",i);
    fscanf(fptr, " %d\n",&j);
    max_of_low=hlow[0];
    min_of_high=h_high[0];
    if(max_of_low>=j) {
      insert(0,j);
      elems_in_low++;
    }
    else if(min_of_high<j) {
      insert(1,j);
      elems_in_high++;
    }
    if(elems_in_high-elems_in_low>=2) {
      r=extract_min();
      insert(0 ,r);
      elems_in_low++;
      elems_in_high--;
    }
    else if(elems_in_low-elems_in_high>=2) {
      r=extract_max();
      insert(1,r);
      elems_in_high++;
      elems_in_low--;
    }
    if((elems_in_low+elems_in_high)%2==0) { //elems are even 
      mod[i]=hlow[0];
    }
    else {
      if(elems_in_low>elems_in_high) {
	mod[i]=hlow[0];
      }
      else {
	mod[i]=h_high[0];
      }
      
    }
    total+=mod[i];
    //    printf("mod[i] = %d\n",mod[i]);
    printf("Hlow: ");
    for(a=0;a<SIZE/2;a++) 
      printf("%d, ",hlow[a]);
    printf("\t");
    printf("Hhigh : ");
    for(a=0;a<SIZE/2;a++) 
      printf("%d, ",h_high[a]);
    printf("\n");
   }
  
  printf("total = %d\n",total);
}

int initialize() {
  int i;
  for(i=0;i<SIZE/2;i++) {
    h_high[i]=0;
    hlow[i]=0;
  }
}

int extract_min() {   
  int min;
  int i;
  int lchild,rchild,temp;
  min=h_high[0];
  i=1;
  h_high[0]=h_high[elems_in_high-1];
  h_high[elems_in_high-1]=0;
  lchild=i*2-1;
  rchild=i*2;
  while(h_high[lchild]>h_high[i-1] && h_high[rchild]>h_high[i-1]) {   
    if(h_high[lchild]<h_high[rchild]) {
      temp=h_high[lchild];
      h_high[lchild]=h_high[i-1];
      h_high[i-1]=temp;
      lchild=(i*2)-1;
      rchild=i*2;
      i=(i*2)-1;
    }
    else {
      temp=h_high[rchild];
      h_high[rchild]=h_high[i-1];
      h_high[i-1]=temp;
      lchild=(i*2)-1;
      rchild=i*2;
      i=(i*2);
    }
  }
  return min;
 }
 

int extract_max() {
  int max;
  int i;
  int lchild,rchild,temp;
  max=hlow[0];
  i=1;
  hlow[0]=hlow[elems_in_high-1];
  hlow[elems_in_high-1]=0;
  lchild=i*2-1;
  rchild=i*2;
  while(hlow[lchild]>hlow[i-1] && hlow[rchild]>hlow[i-1]) {   
    if(hlow[lchild]>hlow[rchild]) {
      temp=hlow[lchild];
      hlow[lchild]=hlow[i-1];
      hlow[i-1]=temp;
      lchild=(i*2)-1;
      rchild=i*2;
      i=(i*2)-1;
    }
    else {
      temp=hlow[rchild];
      hlow[rchild]=hlow[i-1];
      hlow[i-1]=temp;
      lchild=(i*2)-1;
      rchild=i*2;
      i=(i*2);
    }
  }
  return max;
}

insert(int which, int number) {
  int i,temp;
   if(which==0) {
     i=elems_in_low;
     hlow[i]=number;
     while(i>1 && hlow[(i*2)-1] < hlow[(i*2)]) {
       if(hlow[(i*2)-1]!=0 && hlow[(i*2)] != 0) {
	 temp=hlow[i];
	 hlow[(i/2)-1]=hlow[(i-1)];
	 hlow[(i-1)]=temp;
	 i=i/2;
       }
     }
   }
   else {
     i=elems_in_high;
     h_high[i]=number;
     while(i>1 && h_high[i] > h_high[(i*2)]) {
	 temp=h_high[i];
	 h_high[i-1]=h_high[(i*2)];
	 h_high[(i*2)]=temp;
	 i/=2;
     }
   }
 }
