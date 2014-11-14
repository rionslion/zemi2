/*   rui03-2.c   */
#include<stdio.h>

#define NMAX 100

int spritsum(int i,int j, int a[]);

int main(void){
  int n,x,i,j,tmp,ans,anssp,ansi,ansj;
  int a[NMAX];

  for(;;){
    scanf("%d %d",&n,&x);
    if(n == 0 && x == 0)break;

    for(i=0; i<n; i++){
      scanf("%d",(a+i));
    }
    i = 0;
    j = 0;
    ans = 0;
    anssp = x - a[0];
    ansi = 0;
    ansj = 0;

    if(anssp < 0) anssp = -anssp;
    
    while(1){
      tmp = spritsum(i, j, a);
      if(tmp == x){
	ans = tmp;
	ansi = i;
	ansj = j;
	break;
      }
      if(tmp < x){
	if(anssp > (x-tmp)){
	  ans = tmp;
	  ansi = i;
	  ansj = j;
	  anssp = x - tmp;
	}
	if(j == (n-1)) break;
	j++;
      }
      if(tmp > x){
	if(anssp > (tmp-x)){
	  ans = tmp;
	  ansi = i;
	  ansj = j;
	  anssp = tmp - x;
	}
	i++;
      }
    }
    printf("%d %d %d\n",ansi, ansj, ans);
  }

  return 0;
}

int spritsum(int i,int j, int a[]){
  int ans,k;
  ans = 0;
  for(k=i; k<=j; k++){
    ans += a[k];
  }
  return ans;
}
  
