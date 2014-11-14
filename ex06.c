/*   ex06.c   */
#include <stdio.h>

#define SIZE_MAX 8
#define DEFAULT_HP 6

#define STONE 0
#define PLANE 1
#define START 2
#define NEST  3
#define FOOD  4

int map[SIZE_MAX][SIZE_MAX];
int besttime[SIZE_MAX][SIZE_MAX][DEFAULT_HP];

int w, h;
int bestgoaltime;

void search(int x, int y, int hp, int time);

int main(void){
  int i, j, k, start_x, start_y;

  scanf("%d %d",&w, &h);
  while(w!=0 && h!=0){
    for(i=0; i<h; i++){
      for(j=0; j<w; j++){
	scanf("%d",&map[j][i]);
	for(k=0; k<=DEFAULT_HP; k++){
	  besttime[j][i][k] = -1;
	}
	if(map[j][i] == START){
	  start_x = j;
	  start_y = i;
	}
      }
    }

    bestgoaltime = -1;
    search(start_x, start_y, DEFAULT_HP, 0);
    printf("%d\n",bestgoaltime); 

    scanf("%d %d",&w, &h);
    
  }

  return 0;
}


void search(int x, int y, int hp, int time){
  int tmphp, i;
  tmphp = hp;

  if(x < 0 || x >= w || y < 0 || y >= h) return; // out of field
  if(map[x][y] == STONE) return; // on the stone
  if(hp <= 0) return; // ant is dead

  // goal record
  if(map[x][y] == NEST){
    if(bestgoaltime == -1 || bestgoaltime > time) bestgoaltime = time;
  }
  
  // eat food
  if(map[x][y] == FOOD) tmphp = DEFAULT_HP;
  
  // map record
  for(i=DEFAULT_HP; i>=tmphp; i--){
    if(besttime[x][y][i] != -1 && besttime[x][y][i] <= time){
      return;
    }
  }
  besttime[x][y][tmphp] = time;

  search(x+1, y, tmphp-1, time+1);
  search(x-1, y, tmphp-1, time+1);
  search(x, y+1, tmphp-1, time+1);
  search(x, y-1, tmphp-1, time+1);

}
  
