/*   ex11.c   */
#include <stdio.h>

#define N_MAX 1120
#define K_MAX 14

int calc(int n, int k);

int main(void){
  int n, k;
  scanf("%d %d", &n, &k);

  while(n!=0 && k!=0){
    printf("%d\n",calc(n, k));
    scanf("%d %d", &n, &k);
  }

  return 0;
}

int calc(int n, int k){
  int dp[N_MAX+1][K_MAX+1];
  int i, j, p, flag, msum;

  //init
  for(i=0; i<=N_MAX; i++){
    for(j=0; j<=K_MAX; j++){
      dp[i][j] = 0;
    }
  }
  dp[0][0] = 1;
  msum = 0;

  for(p=2; p<=n; p++){
    flag = 0;
    for(i=2; i*i<=p; i++){
      if(p%i==0){
	flag = 1;
	break;
      }
    }
    if(flag) continue;

    msum += p;

    for(i=msum; i>=p; i--){
      if(i<=n){
	for(j=1; j<=k; j++){
	  dp[i][j] += dp[i-p][j-1];
	}
      }
    }
  }

  
  return(dp[n][k]);
}
