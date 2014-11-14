/*   back01.c   */
#include <stdio.h>

#define BOARD_SIZE 5

int board[BOARD_SIZE][BOARD_SIZE];
int sum;

void backtrack(int step, int x, int y);
int main(void){
  int i, j;

  // init
  for(i=0; i<BOARD_SIZE; i++){
    for(j=0; j<BOARD_SIZE; j++){
      board[i][j] = 0;
    }
  }
  sum = 0;

  //do
  backtrack(1, 0, 0);
  return(0);
}
  
void backtrack(int step, int x, int y){
  int i, j;

  // bad position
  if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != 0){
    return;
  }

  // step
  board[x][y] = step;

  // finish
  if(step == BOARD_SIZE * BOARD_SIZE){
    sum++;
    printf("answer %d:\n",sum);
    for(i=0; i<BOARD_SIZE; i++){
      for(j=0; j<BOARD_SIZE; j++){
	printf("%3d ",board[i][j]);
      }
      printf("\n");
    }
  }

  // next step
  else{
    backtrack(step+1, x+1, y+2);
    backtrack(step+1, x+1, y-2);
    backtrack(step+1, x-1, y+2);
    backtrack(step+1, x-1, y-2);
    backtrack(step+1, x+2, y+1);
    backtrack(step+1, x+2, y-1);
    backtrack(step+1, x-2, y+1);
    backtrack(step+1, x-2, y-1);
  }

  // back
  board[x][y] = 0;
}
