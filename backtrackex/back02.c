/*   back02.c   */
#include <stdio.h>

#define BOARD_SIZE 8

int board[BOARD_SIZE];
int left[BOARD_SIZE*2-1];
int right[BOARD_SIZE*2-1];
int sum;

void backtrack(int p);
int check(int p, int i);
void set(int p, int i);
void reset(int p, int i);


int main(void){
  int i;

  // init
  for(i=0; i<BOARD_SIZE; i++){
    board[i] = 0;
  }
  for(i=0; i<BOARD_SIZE*2-1; i++){
    right[i] = 0;
    left[i] = 0;
  }
  sum = 0;

  //do
  backtrack(0);
  return(0);
}
  
void backtrack(int p){
  int i;

  // finish
  if(p == BOARD_SIZE){
    sum++;
    printf("answer %d:\n",sum);
    for(i=0; i<BOARD_SIZE; i++){
      printf("%3d ",board[i]);
    }
    printf("\n");
  }

  // set
  else{
    for(i=0; i<BOARD_SIZE; i++){
      if(check(p,i) == 1){
	set(p,i);
	backtrack(p+1);
	reset(p,i);
      }
    }
  }
}

int check(int p, int i){
  if(board[i] != 0) return(0);
  if(right[p+i] != 0) return(0);
  if(left[p+BOARD_SIZE-1-i] != 0) return(0);
  return 1;
}

void set(int p, int i){
  board[i] = p+1;
  right[p+i] = p+1;
  left[p+BOARD_SIZE-1-i] = p+1;
}

void reset(int p, int i){
  board[i] = 0;
  right[p+i] = 0;
  left[p+BOARD_SIZE-1-i] = 0;
}
