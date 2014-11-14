/*   rui03-1.c   */
#include<stdio.h>

int twice(int x);

int main(void){
  int n,x,y,tmp;

  for(;;){
    scanf("%d",&n);
    if(n == 0)break;

    x = 0;
    for(y=1; twice(y) <= n; y++);
    y--;
    
    while(1){
      tmp = twice(x) + twice(y);
      if(tmp == n){
	printf("%3d, %3d\n",x,y);
	if(y == 0) break;
	x++;
	y--;
      }
      if(tmp > n){
	if(y == 0) break;
	y--;
      }
      if(tmp < n){
	x++;
      }
    }
  }

  return 0;
}

int twice(int x){
  return(x*x);
}
  
