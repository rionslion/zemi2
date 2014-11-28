/*   ex09-3.c   */
#include <stdio.h>

#define X_MAX 300
#define Y_MAX 17
int table[X_MAX+1][Y_MAX+1];

int calc(int n, int y);
int main(void){
  int n, i, j;

  for(i=0; i<=X_MAX; i++){
    for(j=0; j<=Y_MAX; j++){
      table[i][j] = -1;
    }
  }

  scanf("%d",&n);
  while(n != 0){
    printf("%d\n",calc(n, Y_MAX));
    scanf("%d",&n);
  }

  return 0;
}

int calc(int n, int y){
  if(n<0) return 0;
  if(n==0 || y==1) table[n][y] = 1;
  else if(table[n][y] == -1){
    table[n][y] = calc(n-y*y, y) + calc(n, y-1);
  }
  return(table[n][y]);
}
