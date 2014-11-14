/*   ex04ad.c   */
#include <stdio.h>
#include <string.h>

char button[301];
char word[100][51];
int w_len[100];
int b_len;
int ans[100];
int n;

// additional
char ans_words[301][511][301];
int ans_num[301];

void dp(int pos);
int match(char b, char w);
void print_ans(int len);

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
    for(i=0; i<=b_len; i++){
      dp(i);
    }
    print_ans(b_len)

    printf("--\n");
    
    scanf("%d",&n);
  }
}

void dp(int pos){
  int i, j, flag;
  char tmp[51];

  for(i=0; i<n; i++){
    if(w_len[i] <= pos){
      if(ans_num[pos-w_len[i]] != 0){
	flag = 0;
	for(j=0; j<w_len[i]; j++){
	  if(!match(button[pos-w_len[i]+j], word[i][j])){
	    flag = 1;
	  }
	}
	if(!flag){
	  record();
	}
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

void print_ans(int len){
  int i;

  for(i=0; i<ans_num[len]; i++){
    printf("%s.\n",ans_words[len][i]);
  }
}
