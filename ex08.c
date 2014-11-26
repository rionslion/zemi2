/*   ex08.c   */

#include <stdio.h>
#include <stdlib.h>

#define Hash_Size  299993
#define Store_Size 200000

#define False  0
#define True   1

typedef struct {    /* 状態のデータ構造 */
  int  x[4][8];     /*   盤面 */
  int  step;        /*   初期状態からのステップ数 */
  int  hash_link;   /*   ハッシュ用のリンク */
} stat;

stat final;         /* 目標状態 */
stat initial;       /* 初期状態 */
int  answer;        /* 目標状態に到達したらステップ数、そうでなければ -1 */

int  hash_table[Hash_Size];    /* ハッシュ表（チェイン法）*/
stat store[Store_Size];        /* 生成した状態を順に詰める、一種の待ち行列 */
int  count;                    /* store の中に記録した状態の数 */

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
  return (0);   /* ダミー */
}

void generate_moves(int p)
{
  /*  状態 store[p] から一手で行ける状態（2〜4 種類）を生成し、
  それぞれ記録する（enter を呼び出す）。生成された状態の
  ステップ数は、store[p] のステップ数に 1 を加えたものである。
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
  まず、状態 s が目標状態に等しいかどうか調べる（equal を呼び出す）。
  等しかったら、s.step の値を answer に記録する。これが答である。
  この場合は、これだけで return してよい。

  目標状態でなければ、状態 s を待ち行列に記録する。手順は次のとおり。
  まず状態をハッシュする。この値は、配列 hashtable の添字になる。
  hashtable[h] は、配列 store の添字をポインターの代わりに使った
  ような線形リストになっている（-1 が NULL の代わり）。線形リストを
  調べて、s がすでに存在すれば何もせずに return する。

  s がまだ存在しなければ、store の最後に追加する。リンクを適当に
  張り、hashtable[h] の値を書き換える。
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

/* 二つの状態が等しいか否か */

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

/* 致命的なエラー */

void fatal(char *s)
{
  fprintf(stderr, "%s\n", s);
  exit(1);
}
