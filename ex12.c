/*   ex12.c   */
#include <stdio.h>

#define N_MAX 1000000
#define K_MAX 100

void calc(int n);

int main(void){
  int n;
  scanf("%d", &n);

  while(n!=0){
    calc(n);
    scanf("%d", &n);
  }

  return 0;
}

void calc(int n){
  int dp[N_MAX+1];
  int dp2[N_MAX+1];
  int i, m, p;

  //init
  for(i=0; i<=n; i++){
    dp[i] = i;
    dp2[i] = i;
  }

  m = 2;
  while(1){
    p = m*(m+1)*(m+2)/6;
    if(p>n) break;

    for(i=p; i<=n; i++){
      if(dp[i] > dp[i-p]+1){
	dp[i] = dp[i-p]+1;
      }
    }
    if(p%2){
      for(i=p; i<=n; i++){
	if(dp2[i] > dp2[i-p]+1){
	  dp2[i] = dp2[i-p]+1;
	}
      }
    }
    m++;
  }
  
  printf("%d %d\n",dp[n],dp2[n]);
}
