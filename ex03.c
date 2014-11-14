/*   ex03.c   */
#include<stdio.h>

int xcal(int x);
int ycal(int y);

int main(void){
  int n,x,y,ans,tmp;

  for(;;){
    scanf("%d",&n);
    if(n == 0)break;

    x = 0;
    for(y=1; ycal(y) <= n; y++);
    y--;
    ans = 0;
    
    while(1){
      tmp = xcal(x) + ycal(y);
      if(tmp == n){
	ans = tmp;
	break;
      }
      if(tmp > n){
	if(y == 0) break;
	y--;
      }
      if(tmp < n){
	if(ans < tmp){
	  ans = tmp;
	}
	x++;
      }
    }

    printf("%d\n",ans);
  }

  return 0;
}

int xcal(int x){
  return(x*x*x);
}

int ycal(int y){
  return((y*(y+1)*(y+2))/6);
}
  
