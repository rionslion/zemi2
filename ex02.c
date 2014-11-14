/*   ex02.c   */
#include <stdio.h>
#define MAX_N 50
#define MAX_R 50

int main(void){
  int n, r, p, c;
  int befordek[MAX_N], afterdek[MAX_N];
  int i,j;

  for(;;){
    scanf("%d%d",&n,&r);
    if(n == 0 && r == 0) break;
    
    for(i = 1; i <= n; i++){
      befordek[n-i] = i;
      afterdek[n-i] = i;
    }

    for(i = 0; i < r; i++){
      scanf("%d%d",&p,&c);
      for(j = 0; j < c; j++){
	afterdek[j] = befordek[j+p-1];
      }
      for(j = 0; j < p-1; j++){
	afterdek[j+c] = befordek[j];
      }
      for(j = p+c-1; j < n; j++){
	afterdek[j] = befordek[j];
      }
      for(j = 0; j < n; j++){
	befordek[j] = afterdek[j];
      }
    }
    printf("%d\n",befordek[0]);
  }

  return 0;
}
      
    
