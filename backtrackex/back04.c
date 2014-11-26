/*   back04-1.c   */
#include <stdio.h>

#define NUMS 4
#define NUMM 9
#define RECNUM 16384
#define LINENUM 8

struct divnums {
  int child;
  int mother;
};
typedef struct divnums divnum;

int count;
divnum rec[RECNUM];

void init(void);
void backtrack(int step, divnum snum, divnum nnum);
void record(divnum num);
void print_record(void);

int main(void){
  divnum n;
  n.child = 0;
  n.mother = 1;

  init();

  backtrack(0, n, n);
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


void backtrack(int step, divnum snum, divnum nnum){
  int i;
  divnum n, m;
  n.mother = 1;

  if(step >= NUMS){
    n.mother = snum.mother * nnum.mother;
    n.child = snum.child*nnum.mother + nnum.child*snum.mother;
    record(n);
    return;
  }
  else if(step == 0){
    for(i=1; i<=NUMM; i++){
      n.child = i;
      backtrack(step+1, snum, n);
    }
  }

  else{

    for(i=1; i<=NUMM; i++){
      // +
      n.mother = snum.mother * nnum.mother;
      n.child = snum.child*nnum.mother + nnum.child*snum.mother;
      m.mother = 1;
      m.child = i;
      backtrack(step+1, n, m);

      // -
      n.mother = snum.mother * nnum.mother;
      n.child = snum.child*nnum.mother + nnum.child*snum.mother;
      m.mother = 1;
      m.child = -i;
      backtrack(step+1, n, m);

      // *
      n.mother = nnum.mother;
      n.child = nnum.child * i;
      backtrack(step+1, snum, n);
      
      // /
      n.mother = nnum.mother * i;
      n.child = nnum.child;
      backtrack(step+1, snum, n);

    }
  }
}
    
void record(divnum num){
  int i,j, minusflag;
  divnum n;
  
  if(count >= RECNUM-1) return;

  n.child = num.child;
  n.mother = num.mother;
  i = 2;
  minusflag = 0;

  if(n.child < 0){
    minusflag = 1;
    n.child = -n.child;
  }
  
  while(i <= n.child && i <= n.mother){
    if(n.child%i == 0 && n.mother%i == 0){
      n.child = n.child / i;
      n.mother = n.mother / i;
    }
    else i++;
  }
  if(minusflag) n.child = -n.child;

  for(i=0; i<count; i++){
    if(rec[i].child == n.child && rec[i].mother == n.mother) return;
    if(rec[i].child == 0 && n.child == 0) return;
    if(rec[i].child*n.mother > n.child*rec[i].mother) break;
  }
  
  for(j=count; j>i; j--){
    rec[j] = rec[j-1];
  }

  rec[i] = n;
  count++;

}

void print_record(void){
  int i;

  for(i=0; i<count; i++){
    if(rec[i].mother != 1) printf("%4d/%-4d ",rec[i].child ,rec[i].mother);
    else printf("%5d     ",rec[i].child);
    if(i%LINENUM==LINENUM-1) printf("\n");
  }
  printf("\n");
  printf("total: %d\n",count);

}
