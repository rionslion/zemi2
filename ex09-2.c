/*   ex09-2.c   */
#include <stdio.h>

#define X_MAX 300
#define Y_MAX 17

int calc(int n, int y);
int main(void){
  int n;

  scanf("%d",&n);
  while(n != 0){
    printf("%d\n",calc(n, Y_MAX));
    scanf("%d",&n);
  }

  return 0;
}

int calc(int n, int y){
  if(n==0 || y==1) return 1;
  if(n<0) return 0;

  return(calc(n-y*y, y)+calc(n, y-1));
}
