#include <stdio.h>
#define SIZE 10000
struct j {
  float comptime;
  float weight;
  float length;
  float score;
};
typedef struct j t_j;
t_j jobs[SIZE];
int main() {
  long long total;
  read();
  printf("First.weight = %f, First.length = %f, Last.weight = %f, Last.length = %f",jobs[0].weight,jobs[0].length,jobs[SIZE-1].weight, jobs[SIZE-1].length);
  populate_scores();
  sort_it(jobs, SIZE);
  break_ties();
  completion_times();
  total=answer();
  print();
}
int answer() {
  long long total=0;
  int i;
  for(i=0;i<SIZE;i++) {
    total += ((jobs[i].comptime) *(jobs[i].weight));
  }
  printf("total= %lld\n", total);
  return;
}
int break_ties() {
  int i, j,count;
  t_j temp;
  for(count=0;count<SIZE;count++) {
    for(i=0;i<SIZE;i++) {
      j=i+1;
      if((jobs[i].score == jobs[j].score) && (jobs[i].weight < jobs[j].weight)) {
	temp=jobs[i];
	jobs[i]=jobs[j];
	jobs[j]=temp;
      }
    }
  }
}
int sort_it(t_j *arr, int n) {
       
        if(n==1) return;
	t_j *left=arr;
        t_j *right=arr+n/2;
        int k=0;
        int i=0;
        int j=0;
	int count, n1, n2;
	t_j newarr[n];
	n1 = n/2;
	n2 = n - n1;
	sort_it(left,n1);
        sort_it(right,n2);

        while  ( k < n ) {
                if (left[i].score < right[j].score) {
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

int read() {
  int i;
  int make_sure;
  FILE *fptr;
  fptr=fopen("./jobs.txt", "r");
  fscanf(fptr,"%d\n",&make_sure);
  if(make_sure != SIZE) 
    printf("something is wrong\n");
  for (i = 0;i < SIZE;i++) {
    fscanf(fptr," %f",&jobs[i].weight);
    fscanf(fptr, " %f\n",&jobs[i].length);
  } 
  return;
}
int populate_scores() {
  int i;
  for(i=0;i<SIZE;i++) {
    jobs[i].score=((jobs[i].weight)/(jobs[i].length));
  }
}

int completion_times() {
  int total=0;
  int i;
  /*for(i=0;i<SIZE;i++) {
    total += jobs[i].length;
    jobs[i].comptime=total;
  }
  */
  total = jobs[0].length;
  jobs[0].comptime=total;
  for(i=1;i<SIZE;i++) {
    jobs[i].comptime = jobs[i].length + jobs[i-1].comptime;
  }
  return;
}

int print() {
  int i;
  printf("STATS: \n");
  for(i=0;i<SIZE;i++) {
    printf("weight = %f, length = %f, score = %f, comptime = %f\n ",jobs[i].weight ,jobs[i].length ,jobs[i].score,jobs[i].comptime);
  } 
  printf("\n");
  printf("\n");
  printf("\n");
}
