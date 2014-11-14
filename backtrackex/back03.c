/*   back03.c   */
#include <stdio.h>

#define BOARD_SIZE 4

int board[BOARD_SIZE][BOARD_SIZE];
int used[BOARD_SIZE][BOARD_SIZE];

int ans, ans_num;

void init(void);
void backtrack(int mode, int x, int y);
void nextstep(int mode, int x, int y);

int checknum(int sel);
void uncheck(int sel);

int check_x(int y);
int check_y(int x);
int check_up(void);
int check_down(void);

void print_ans(void);

int main(void){
  init();
  backtrack(0, 0, 0);
  return 0;
}

void init(void){
  int i, j;

  for(i=0; i<BOARD_SIZE; i++){
    for(j=0; j<BOARD_SIZE; j++){
      board[i][j] = 0;
      used[i][j] = 0;
    }
  }

  ans = (BOARD_SIZE * BOARD_SIZE * BOARD_SIZE + BOARD_SIZE) / 2;
  ans_num = 1;
}

void backtrack(int mode, int x, int y){
  int sel, i, j;

  for(sel = 0; sel<BOARD_SIZE*BOARD_SIZE; sel++){
    if(checknum(sel)){
      board[x][y] = sel+1;
      nextstep(mode, x, y);
      board[x][y] = 0;
      uncheck(sel);
    }
  }

}


void nextstep(int mode, int x, int y){

  if(mode == 0){
    if(x == BOARD_SIZE-1){
      if(check_x(y)) backtrack(mode+1, 0, y+1);
    }
    else backtrack(mode, x+1, y);
  }

  else if(mode == 1){
    if(y == BOARD_SIZE-1){
      if(check_y(x)) backtrack(mode+1, x+1, y-1);
    }
    else backtrack(mode, x, y+1);
  }

  else if(mode == 2){
    if(x == BOARD_SIZE-2){
      if(check_up()){
	backtrack(mode+1, 1, y);
      }
    }
    else backtrack(mode, x+1, y-1);
  }

  else if(mode == 3){
    if(x == BOARD_SIZE-1){
      if(check_x(y)){
	if(y == BOARD_SIZE-2) backtrack(mode+1, x, y+1);
	else if(y == BOARD_SIZE-3) backtrack(mode, 2, y+1);
	else backtrack(mode, 1, y+1);
      }
    }
    else{
      if(x+y == BOARD_SIZE-2) backtrack(mode, x+2, y);
      else backtrack(mode, x+1, y);
    }
  }

  else if(mode == 4){
    if(check_y(x) && check_down()) backtrack(mode+1, x-1, y);
  }
  
  else if(mode == 5){
    if(check_y(x)){
      if(x == 1) print_ans();
      else backtrack(mode, x-1, y);
    }
  }
}


int checknum(int sel){
  int i, j;
  i = sel / BOARD_SIZE;
  j = sel % BOARD_SIZE;
  if(used[i][j] != 0) return 0;
  else{
    used[i][j] = sel + 1;
    return 1;
  }
}

void uncheck(int sel){
  int i, j;
  i = sel / BOARD_SIZE;
  j = sel % BOARD_SIZE;
  used[i][j] = 0;
}


int check_x(int y){
  int sum, i;
  sum = 0;

  for(i=0; i<BOARD_SIZE; i++){
    sum += board[i][y];
  }

  return(sum == ans);
}

int check_y(int x){
  int sum, i;
  sum = 0;

  for(i=0; i<BOARD_SIZE; i++){
    sum += board[x][i];
  }

  return(sum == ans);
}

int check_up(void){
  int sum, i;
  sum = 0;

  for(i=0; i<BOARD_SIZE; i++){
    sum += board[BOARD_SIZE-i-1][i];
  }

  return(sum == ans);
}

int check_down(void){

  int sum, i;
  sum = 0;

  for(i=0; i<BOARD_SIZE; i++){
    sum += board[i][i];
  }

  return(sum == ans);
}

void print_ans(void){
  int i, j;

  printf("ans: %d\n", ans_num);
  for(i=0; i<BOARD_SIZE; i++){
    for(j=0; j<BOARD_SIZE; j++){
      printf("%2d ",board[j][i]);
    }
    printf("\n");
  }
  printf("\n");
  ans_num++;
}
