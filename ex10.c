/*   ex10.c   */
#include <stdio.h>

#define PLAYER 10
#define STONE 8192
#define WIN 1
#define LOSE 0

int m[PLAYER*2];

int calc(int n, int s);

int main(void){
  int n, s, i;

  scanf("%d",&n);
  while(n != 0){
    scanf("%d",&s);
    for(i=0; i<n*2; i++){
      scanf("%d", &m[i]);
    }

    printf("%d\n",calc(n, s));
    scanf("%d",&n);
  }
}

int calc(int n, int s){
  int judge[PLAYER*2][STONE];
  int i, j, k;

  for(i=0; i<n; i++){
    for(j=1; j<s; j++){
      if(j==1) judge[i][j] = LOSE;
      else{
	judge[i][j] = LOSE;
	for(k=1; k<= m[i]; k++){
    }
  }

  return(judge[0][s]);
}
