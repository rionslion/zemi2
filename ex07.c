/*   ex07.c   */

#include <stdio.h>
#include <stdlib.h>

#define Hash_Size  299993
#define Store_Size 200000

#define False  0
#define True   1

typedef struct {    /* 状態のデータ構造 */
  int  x[9];        /*   盤面 */
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
  int  i, r, h, p;

  for (;;) {
    for (h = 0; h < Hash_Size; h++)
      hash_table[h] = -1;
    count = 0;
    for (i = 0; i < 8; i++)
      final.x[i] = i+1;
    final.x[8] = 0;
    for (i = 0; i < 9; i++) {
      r = scanf("%d", &initial.x[i]);
      if (r == EOF)
	return (0);
      if (initial.x[i] < 0 || initial.x[i] > 8)
	fatal("input value out of range");
    }
    initial.step = 0;
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
  int i;

  s = store[p];
  for(i=0; i<9; i++){
    if(s.x[i] == 0) break;
  }
  if(i%3 == 0){
    w = s;
    w.x[i] = w.x[i+1];
    w.x[i+1] = 0;
    w.step++;
    enter(w);
  }
  else if(i%3 == 1){
    w = s;
    w.x[i] = w.x[i-1];
    w.x[i-1] = 0;
    w.step++;
    enter(w);

    w = s;
    w.x[i] = w.x[i+1];
    w.x[i+1] = 0;
    w.step++;
    enter(w);
  }
  else if(i%3 == 2){
    w = s;
    w.x[i] = w.x[i-1];
    w.x[i-1] = 0;
    w.step++;
    enter(w);
  }

  if(i/3 == 0){
    w = s;
    w.x[i] = w.x[i+3];
    w.x[i+3] = 0;
    w.step++;
    enter(w);
  }
  else if(i/3 == 1){
    w = s;
    w.x[i] = w.x[i+3];
    w.x[i+3] = 0;
    w.step++;
    enter(w);

    w = s;
    w.x[i] = w.x[i-3];
    w.x[i-3] = 0;
    w.step++;
    enter(w);
  }
  else if(i/3 == 2){
    w = s;
    w.x[i] = w.x[i-3];
    w.x[i-3] = 0;
    w.step++;
    enter(w);
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
  int i, a, h;
  stat t;

  if(equal(s, final)){
    answer = s.step;
    return;
  }

  a=1;
  h = 0;
  for(i=0; i<9; i++){
    h += (a*s.x[i]);
    h = h%Hash_Size;
    a *= 9;
    if(a<0) a = -a;
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
  int  i;

  for (i = 0; i < 9; i++)
    if (a.x[i] != b.x[i])
      return (False);
  return (True);
}

/* 致命的なエラー */

void fatal(char *s)
{
  fprintf(stderr, "%s\n", s);
  exit(1);
}
