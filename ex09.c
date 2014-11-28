/*   ex09.c   */
#include <stdio.h>

#define X_MAX 300
#define Y_MAX 17

int calc(int n);
int main(void){
  int n;

  scanf("%d",&n);
  while(n != 0){
    printf("%d\n",calc(n));
    scanf("%d",&n);
  }

  return 0;
}

int calc(int n){
  int i, j;
  int ans[X_MAX+1][Y_MAX+1];

  for(i=0; i<=n; i++){
    for(j=1; j<=Y_MAX; j++){
      if(j*j > n) break;
      if(i==0 || j==1) ans[i][j] = 1;
      else if(i-j*j<0) ans[i][j] = ans[i][j-1];
      else ans[i][j] = ans[i-j*j][j] + ans[i][j-1];
    }
  }

  return(ans[n][j-1]);
}
