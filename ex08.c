/*   ex08.c   */

#include <stdio.h>
#include <stdlib.h>

#define Hash_Size  299993
#define Store_Size 200000

#define False  0
#define True   1

typedef struct {    /* $B>uBV$N%G!<%?9=B$(B */
  int  x[4][8];     /*   $BHWLL(B */
  int  step;        /*   $B=i4|>uBV$+$i$N%9%F%C%W?t(B */
  int  hash_link;   /*   $B%O%C%7%eMQ$N%j%s%/(B */
} stat;

stat final;         /* $BL\I8>uBV(B */
stat initial;       /* $B=i4|>uBV(B */
int  answer;        /* $BL\I8>uBV$KE~C#$7$?$i%9%F%C%W?t!"$=$&$G$J$1$l$P(B -1 */

int  hash_table[Hash_Size];    /* $B%O%C%7%eI=!J%A%'%$%sK!!K(B*/
stat store[Store_Size];        /* $B@8@.$7$?>uBV$r=g$K5M$a$k!"0l<o$NBT$A9TNs(B */
int  count;                    /* store $B$NCf$K5-O?$7$?>uBV$N?t(B */

void generate_moves(int p);
void enter(stat s);
int  equal(stat a, stat b);
void fatal(char *s);

int  main(void)
{
  int  k, i, j, r, h, p, n;

  scanf("%d",&n);

  for (i=0; i<4; i++){
    for(j=0; j<7; j++){
      final.x[i][j] = (i+1)*10 + j+1;
    }
    final.x[i][7] = 0;
  }

  for (k=0; k<n; k++) {
    for (h = 0; h < Hash_Size; h++)
      hash_table[h] = -1;
    count = 0;

    for (i=0; i<4; i++){
      for(j=1; j<=7; j++){
	r = scanf("%d", &initial.x[i][j]);
	if (r == EOF) return (0);
	if (initial.x[i][j]%10 < 1 || initial.x[i][j]%10 > 7 ||
	    initial.x[i][j] < 11 || initial.x[i][j] > 47){
	  fatal("input value out of range");
	}
	if(initial.x[i][j]%10 == 1) initial.x[i][j] = 0;
      }
    }

    for (i=0; i<4; i++){
      initial.x[i][0] = (i+1)*10 + 1;
    }

    initial.step = 0;
    initial.hash_link = -1;
    answer = -1;
    enter(initial);
    p = 0;
    while (p < count) {
      if (answer >= 0)
	break;
      generate_moves(p);
      p++;
    }
    printf("%d\n", answer);
  }
  return (0);   /* $B%@%_!<(B */
}

void generate_moves(int p)
{
  /*  $B>uBV(B store[p] $B$+$i0l<j$G9T$1$k>uBV!J(B2$B!A(B4 $B<oN`!K$r@8@.$7!"(B
  $B$=$l$>$l5-O?$9$k!J(Benter $B$r8F$S=P$9!K!#@8@.$5$l$?>uBV$N(B
  $B%9%F%C%W?t$O!"(Bstore[p] $B$N%9%F%C%W?t$K(B 1 $B$r2C$($?$b$N$G$"$k!#(B
  */

  stat s, w;
  int i, j, k, l;

  s = store[p];
  for(i=0; i<4; i++){
    for(j=1; j<8; j++){
      if(s.x[i][j] == 0 && s.x[i][j-1]%10 != 7){
	w = s;
	for(k=0; k<4; k++){
	  for(l=1; l<8; l++){
	    if(w.x[k][l] == w.x[i][j-1]+1){
	      w.x[k][l] = 0;
	      break;
	    }
	  }
	}
	w.x[i][j] = w.x[i][j-1]+1;
	w.step++;
	enter(w);
      }
    }
  }
}

void enter(stat s)
{
  /*
  $B$^$:!">uBV(B s $B$,L\I8>uBV$KEy$7$$$+$I$&$+D4$Y$k!J(Bequal $B$r8F$S=P$9!K!#(B
  $BEy$7$+$C$?$i!"(Bs.step $B$NCM$r(B answer $B$K5-O?$9$k!#$3$l$,Ez$G$"$k!#(B
  $B$3$N>l9g$O!"$3$l$@$1$G(B return $B$7$F$h$$!#(B

  $BL\I8>uBV$G$J$1$l$P!">uBV(B s $B$rBT$A9TNs$K5-O?$9$k!#<j=g$O<!$N$H$*$j!#(B
  $B$^$:>uBV$r%O%C%7%e$9$k!#$3$NCM$O!"G[Ns(B hashtable $B$NE:;z$K$J$k!#(B
  hashtable[h] $B$O!"G[Ns(B store $B$NE:;z$r%]%$%s%?!<$NBe$o$j$K;H$C$?(B
  $B$h$&$J@~7A%j%9%H$K$J$C$F$$$k!J(B-1 $B$,(B NULL $B$NBe$o$j!K!#@~7A%j%9%H$r(B
  $BD4$Y$F!"(Bs $B$,$9$G$KB8:_$9$l$P2?$b$;$:$K(B return $B$9$k!#(B

  s $B$,$^$@B8:_$7$J$1$l$P!"(Bstore $B$N:G8e$KDI2C$9$k!#%j%s%/$rE,Ev$K(B
  $BD%$j!"(Bhashtable[h] $B$NCM$r=q$-49$($k!#(B
  */
  int i, j, a, h;
  stat t;

  if(equal(s, final)){
    answer = s.step;
    return;
  }

  a=1;
  h = 0;
  for(i=0; i<4; i++){
    for(j=0; j<8; j++){
      h += (a*s.x[i][j]);
      if(h<0) h = -h;
      h = h%Hash_Size;
      a *= 2;
      if(a<0) a = -a;
    }
  }

  if(hash_table[h] != -1){
    t = store[hash_table[h]];
    while(t.hash_link != -1){
      if(equal(s, t)) return;
      t = store[t.hash_link];
    }
    if(equal(s, t)) return;
  }
  s.hash_link = hash_table[h];
  store[count] = s;
  hash_table[h] = count;
  count++;

}

/* $BFs$D$N>uBV$,Ey$7$$$+H]$+(B */

int  equal(stat a, stat b)
{
  int  i, j;

  for (i=0; i<4; i++){
    for (j=0; j<8; j++){
      if (a.x[i][j] != b.x[i][j]) return (False);
    }
  }
  return (True);
}

/* $BCWL?E*$J%(%i!<(B */

void fatal(char *s)
{
  fprintf(stderr, "%s\n", s);
  exit(1);
}
