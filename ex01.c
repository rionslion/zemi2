/*   ex01.c   */
#include<stdio.h>

int primeCheck(int a);

int main(void){
  int n,i,num;

  while(1){
    scanf("%d",&n);
    if(n == 0)break;
    
    num = 0;
    for(i = 0; i*2 <= n; i++){
      if((primeCheck(i) == 1) && (primeCheck(n-i) == 1)){
	num++;
      }
    }

    printf("%d\n",num);
  }

  return 0;
}

int primeCheck(int a){
  int i;

  if(a < 2)return(0);

  for(i = 2; i*i <= a; i++){
    if(a%i == 0)return(0);
  }

  return(1);
}
  
