/*   back04-1.c   */
/* print calculation version */
#include <stdio.h>

#define NUMS 4
#define NUMM 9
#define RECNUM 32768
#define LINENUM 8

struct divnums {
  int child;
  int mother;
};
typedef struct divnums divnum;

int count;
divnum rec[RECNUM];

void init(void);
void backtrack(int step, divnum num);
void record(divnum num);
void print_record(void);

int main(void){
  divnum n;
  n.child = 0;
  n.mother = 0;

  init();

  backtrack(0, n);
  print_record();
  return 0;
}

void init(void){
  int i;
  divnum n;
  n.child = 0;
  n.mother = 0;

  for(i=0; i<RECNUM; i++) rec[i] = n;
  count = 0;
}


void backtrack(int step, divnum num){
  int i, j;
  divnum n;
  n.mother = 1;

  if(step >= NUMS){
    record(num);
    return;
  }
  else if(step == 0){
    for(i=1; i<=NUMM; i++){
      n.child = i;
      printf("%d ",i);
      backtrack(step+1, n);
    }
  }

  else{
    for(i=1; i<=NUMM; i++){
      // +
      n.mother = num.mother;
      n.child = num.child + i * num.mother;
      if(i>1){
	printf("  ");
	for(j=0; j<step-1; j++) printf("    ");
      }
      printf("+ %d ",i);
      backtrack(step+1, n);

      // -
      n.mother = num.mother;
      n.child = num.child - i * num.mother;
      printf(" ");
      for(j=0; j<step-1; j++) printf("    ");
      printf(" - %d ",i);
      backtrack(step+1, n);

      // *
      n.mother = num.mother;
      n.child = num.child * i;
      printf(" ");
      for(j=0; j<step-1; j++) printf("    ");
      printf(" * %d ",i);
      backtrack(step+1, n);
      
      // /
      n.mother = num.mother * i;
      printf(" ");
      for(j=0; j<step-1; j++) printf("    ");
      printf(" / %d ",i);
      n.child = num.child;
      backtrack(step+1, n);

    }
  }
}
    
void record(divnum num){
  int i,j;
  divnum n;
  
  if(count >= RECNUM-1) return;

  n.child = num.child;
  n.mother = num.mother;
  i = 2;
  
  while(i < n.child && i < n.mother){
    if(n.child%i == 0 && n.mother%i == 0){
      n.child = n.child / i;
      n.mother = n.mother / i;
    }
    else i++;
  }
  /*

  for(i=0; i<count; i++){
    if(rec[i].child == n.child && rec[i].mother == n.mother) return;
    if(rec[i].child*n.mother > n.child*rec[i].mother) break;
  }
  
  for(j=count; j>i; j--){
    rec[j] = rec[j-1];
  }

  rec[i] = n;
  */

  if(n.mother != 1) printf("= %d/%d\n",n.child ,n.mother);
  else printf("= %d\n",n.child);


  count++;

}

void print_record(void){
  int i;
  /*
  for(i=0; i<count; i++){
    if(rec[i].mother != 1) printf("%4d/%-4d ",rec[i].child ,rec[i].mother);
    else printf("%-9d ",rec[i].child);
    if(i%LINENUM==LINENUM-1) printf("\n");
  }
  printf("\n");
  */
  printf("total: %d\n",count);

}
