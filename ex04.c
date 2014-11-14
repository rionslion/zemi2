/*   ex04.c   */
#include <stdio.h>
#include <string.h>

char button[301];
char word[100][51];
int w_len[100];
int b_len;
int ans[100];
int n;

void backtrack(int pos, int num);
int match(char b, char w);
void print_ans(int num);

int main(void){

  int i;
  char emptyword[2];

  scanf("%d",&n);

  while(n != 0){
    gets(emptyword);
    for(i=0; i<n; i++){
      gets(word[i]);
      w_len[i] = strlen(word[i]);
    }
    gets(button);
    b_len = strlen(button);

    // do
    backtrack(0, 0);

    printf("--\n");
    
    scanf("%d",&n);
  }
}

void backtrack(int pos, int num){
  int i, j, flag;
  char tmp[51];

  if(pos >= b_len){
    print_ans(num);
  }
  
  else{
    for(i=0; i<n; i++){
      flag = 0;
      for(j=0; j<w_len[i]; j++){
	if(!match(button[pos+j], word[i][j])){
	  flag = 1;
	}
      }
      if(!flag){
	ans[num] = i;
	backtrack(pos+w_len[i], num+1);
      }
    }
  }
}

int match(char b, char w){
  switch (b){
  case '2': if(w == 'a' || w == 'b' || w == 'c') return 1;
    break;
  case '3': if(w == 'd' || w == 'e' || w == 'f') return 1;
    break;
  case '4': if(w == 'g' || w == 'h' || w == 'i') return 1;
    break;
  case '5': if(w == 'j' || w == 'k' || w == 'l') return 1;
    break;
  case '6': if(w == 'm' || w == 'n' || w == 'o') return 1;
    break;
  case '7': if(w == 'p' || w == 'q' || w == 'r' || w == 's') return 1;
    break;
  case '8': if(w == 't' || w == 'u' || w == 'v') return 1;
    break;
  case '9': if(w == 'w' || w == 'x' || w == 'y' || w == 'z') return 1;
    break;
  }

  return 0;
}

void print_ans(int num){
  int i;

  for(i=0; i<num-1; i++){
    printf("%s ",word[ans[i]]);
  }
  printf("%s.\n",word[ans[num-1]]);
}
