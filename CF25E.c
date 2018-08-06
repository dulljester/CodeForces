/*
 * CF25E
 * TOPIC: Aho-Corasić
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<17)
#define A 26
#define M 3
#define L(k) ((k) & (~(k)+1ULL))
#define BIT(k) (1ULL<<(k))
#define Q ((N*M)<<1)
#define oo (1<<30)
#define MASK(k) (BIT(k)-1ULL)
#define SH (26)
#define enc(x,u) (((x)-pool)|((u)<<SH))

int n,m = M,len[M],yes;
char str[M][N],which[1<<21];

typedef struct cell {
	struct cell *slink, *son[A], *tr[A];
	unsigned int u,v;
	unsigned char mask;
	int d[1<<M],seen[1<<M];
} cell ;

cell *ptr,pool[Q],*root,*q[Q],**head,**tail,*q0;
unsigned int queue[Q*(1<<M)], *h,*t;

int who( unsigned int u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }

cell *init() {
	cell *x = ptr++;
	x->u = x->v = x->mask = 0, x->slink = NULL;
	return x;
}

void push( char *s, int idx ) {
	cell *x = root;
	for ( ;*s; x = x->son[*s++-'a'] )
		if ( !(x->u & BIT(*s-'a')) ) 
			x->u |= BIT(*s-'a'), x->son[*s-'a'] = init();
	x->mask |= BIT(idx);
}

cell *calc_failure_transition( cell *x, char ch ) {
	if ( x->v & BIT(ch-'a') )
		return x->tr[ch-'a'];
	if ( x->u & BIT(ch-'a') ) {
		x->v |= BIT(ch-'a'), x->tr[ch-'a'] = x->son[ch-'a'];
		return x->tr[ch-'a'];
	}
	x->v |= BIT(ch-'a'), x->tr[ch-'a'] = calc_failure_transition(x->slink,ch);
	return x->tr[ch-'a'];
}

int main() {
	int i,j,k,nk,ch,best;
	unsigned int u,v;
	cell *x,*y,*z;
	for ( i = 0; i < 21; which[1<<i] = i, ++i ) ;
	for ( ;1 == scanf("%s",str[0]); printf("%d\n",best) ) {
		ptr = pool, q0 = init(), root = init(), root->slink = q0;
		for ( i = 0; i < A; q0->son[i] = root, q0->u |= BIT(i), ++i ) ;
		for ( len[0] = strlen(str[0]), push(str[0],0), i = 1; i < M; scanf("%s",str[i]), len[i] = strlen(str[i]), push(str[i],i), ++i ) ;
		for ( head = tail = q, *tail++ = root; head < tail; ) 
			for ( u = (x = *head++)->u; u && (ch = who(L(u))) >= 0; y->mask|=(y->slink=z->son[ch])->mask, *tail++ = y, u &= ~L(u) )
				for ( y = x->son[ch], z = x->slink; z && !(z->u & BIT(ch)); z = z->slink ) ;
		for ( best = +oo, h = t = queue, root->seen[0]=++yes, root->d[0]=0, *t++ = enc(root,0); h < t; ) {
			u = *h++, x = pool+(u&MASK(SH)), k = (u>>SH);
			if ( k == MASK(M) && x->d[k] < best ) best = x->d[k];
			if ( x->d[k] >= best ) continue ;
			for ( ch = 'a'; ch <= 'z'; ++ch ) {
				if ( x->u & BIT(ch-'a') ) y = x->son[ch-'a'];
				else y = calc_failure_transition(x,ch);
				nk = y->mask|k, v = enc(y,nk);
				if ( y->seen[nk] != yes || y->d[nk] > x->d[k]+1 )
					*t++ = v, y->d[nk] = x->d[k]+1, y->seen[nk] = yes;
			}
		}
	}
	return 0;
}

