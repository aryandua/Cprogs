#include <stdio.h>
#include <stdlib.h>
#define T 1
#define I 2
#define P 8

int main() {
  read_it();
}

int read_it() {
  int i,j,k,check,ing,pkgs,ans;
  int arr[I][P];
  int ratio[I];
  FILE *fptr,*fptr2;
  fptr = fopen("./a.txt", "r");
  fptr2 = fopen("./output.txt", "w");
  fscanf(fptr, "%d",&check);
  if(check != T) {
    printf("ERROR\n");
    exit(1);
  }
  for(i=0;i<T;i++) {
    fscanf(fptr, "%d",&ing);
    fscanf(fptr, "%d\n",&pkgs);
    for(j=0;j<ing;j++) {
      fscanf(fptr, "%d",&ratio[j]);
    }
    for(j=0;j<ing;j++) {
      for(k=0;k<pkgs;k++) {
	fscanf(fptr, "%d",&arr[j][k]);
      }
    }
    ans = calans(ratio, arr,pkgs);
    fprintf(fptr2, "Case %d: %d\n",i+1,ans);
  }
}

int calans(int *ratio, int arr[I][P], int pkgs) {
  int i,j,count,tmp2,current,wt2,tmp2b;
  float lowbound,upbound,wt2ub,wt2lb,lowboundb,upboundb,u,l;
  int arrbit[P][P];
  for(i=0;i<pkgs;i++) {
    current = arr[0][i];
    count = current/ratio[0];
    tmp2 = count*ratio[0];
    tmp2b = (count+1) * ratio[0];
    upbound = tmp2 * 1.1;
    lowbound = tmp2 * 0.9;
    upboundb = tmp2b * 1.1;
    lowboundb = tmp2b * 0.9;
    if(current >= lowbound && current <= upbound) {
      wt2 = count*ratio[1];
    }
    else if((current >= lowboundb && current <= upboundb)) {
      wt2 = (count+1)*ratio[1];
    }
    else {
      for(j=0;j<pkgs;j++)
	arrbit[i][j] = 0;
      break;
    }

    wt2lb = wt2 * 0.9;
    wt2ub = wt2 * 1.1;
    for(j=0;j<pkgs;j++) {
      u = arr[1][j]*1.1;
      l = arr[1][j]*0.9;
      if((u >= wt2lb && u <= wt2ub) ||(l >= wt2lb && l <= wt2ub)) 
	arrbit[i][j] = 1;
      else 
	arrbit[i][j] = 0;
    }
  }
  int ans = finalcal(arrbit, pkgs);
  return ans;
}

int finalcal(int arrbit[P][P], int pkgs) {
  int cnt1,cnt2;
  int i,j;
  cnt1 = pkgs;
  cnt2 = pkgs;
  for(i=0;i<pkgs;i++) {
    for(j=0;j<pkgs;j++) {
      if(arrbit[i][j] == 1) {
	cnt1--;
	break;
      }
    }
  }
  for(i=0;i<pkgs;i++) {
    for(j=0;j<pkgs;j++) {
      if(arrbit[j][i] == 1) {
	cnt2--;
	break;
      }
    }
  }
  if(cnt1 > cnt2) 
    return pkgs-cnt1;
  else 
    return pkgs-cnt2;
}
