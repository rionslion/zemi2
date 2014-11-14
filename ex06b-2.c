/*   ex06b-2.c   */
/* another answer */
#include <stdio.h>

#define SIZE_MAX 8
#define DEFAULT_HP 6

#define STONE 0
#define PLANE 1
#define START 2
#define NEST  3
#define FOOD  4

int map[SIZE_MAX][SIZE_MAX];
struct { int x, y, hp; } queue[SIZE_MAX*SIZE_MAX*(DEFAULT_HP+1)], a;

int w, h;
int bestgoaltime;
int head, tail;
int steps[SIZE_MAX*SIZE_MAX];

void search(int x, int y);
void move(int x, int y, int hp, int step);

int main(void){
  int i, j, k, start_x, start_y;

  scanf("%d %d",&w, &h);
  while(w!=0 && h!=0){
    for(i=0; i<h; i++){
      for(j=0; j<w; j++){
	scanf("%d",&map[j][i]);
	if(map[j][i] == START){
	  start_x = j;
	  start_y = i;
	}
      }
    }

    bestgoaltime = -1;
    search(start_x, start_y);
    printf("%d\n",bestgoaltime); 

    scanf("%d %d",&w, &h);
    
  }

  return 0;
}


void search(int x, int y){
  int i, step;

  //init
  queue[0].x = x;
  queue[0].y = y;
  queue[0].hp = DEFAULT_HP;

  for(i=0; i<SIZE_MAX*SIZE_MAX; i++){
    steps[i] = 0;
  }

  head = 1;
  tail = 0;

  while(tail < head){
    a = queue[tail];
    tail++;

    step = 0;
    while(steps[step] != 0 && steps[step] < tail) step++;

    // goal record
    if(map[a.x][a.y] == NEST){
      bestgoaltime = step;
      return;
    }
    
    // eat food
    if(map[a.x][a.y] == FOOD) a.hp = DEFAULT_HP;
    
    move(a.x+1, a.y, a.hp-1, step);
    move(a.x-1, a.y, a.hp-1, step);
    move(a.x, a.y+1, a.hp-1, step);
    move(a.x, a.y-1, a.hp-1, step);
  }
  
}

void move(int x, int y, int hp, int step){
  int i;

  if(x < 0 || x >= w || y < 0 || y >= h) return; // out of field
  if(map[x][y] == STONE) return; // on the stone
  if(hp <= 0) return; // ant is dead
  for(i=0; i<head; i++){
    if(queue[i].x == x && queue[i].y == y){
      if(queue[i].hp >= hp) return;
    }
  }
  queue[head].x = x;
  queue[head].y = y;
  queue[head].hp = hp;
  if(steps[step] == 0){
    steps[step] = head;
  }
  head++;
}
	  

  
