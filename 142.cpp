/*
 * 142. Keyword
 * TOPIC: suffix automata
 * status: MLE
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#define N (500100)
using namespace std;


typedef struct cell {
	struct cell *son[2], *slink;
	int len, pos;
} cell;

cell *sink, *root;
vector<cell *> vec;

cell *init( int len, int pos ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->len = len, x->pos = pos, x->slink = x->son[0] = x->son[1] = NULL;
	vec.push_back(x);
	return x;
}

cell *split( cell *x, char ch, int pos ) {
	cell *y=x->son[ch-'0'], *z=init(x->len+1,pos);
	for(z->slink=y->slink,y->slink=z,z->son[0]=y->son[0],z->son[1]=y->son[1],x->son[ch-'0']=z;(x=x->slink)&&x->son[ch-'0']&&x->son[ch-'0']==y;x->son[ch-'0']=z);
	return z;
}

cell *update( char ch, int pos ) {
	cell *new_sink = init(sink->len+1,pos), *x;
	for ( (x = sink)->son[ch-'0'] = new_sink; (x = x->slink) && !x->son[ch-'0']; x->son[ch-'0'] = new_sink ) ;
	if ( !x ) new_sink->slink = root;
	else new_sink->slink = (x->son[ch-'0']->len == x->len+1)?x->son[ch-'0']:split(x,ch,pos);
	return new_sink;
}

char s[N];
int n;

int main() {
	int i,j,k,l,t,idx;
	cell *x;
	for ( ;2 == scanf("%d %s",&n,s); ) {
		for ( sink = root = init(0,-1), i = 0; i < n; s[i]=s[i]=='a'?'0':'1',sink = update(s[i],i), ++i ) ;
		for ( k = N, idx = 0; idx < (int)vec.size(); ++idx ) 
			for ( x = vec[idx], t = 0; t <= 1; ++t )
				if ( !x->son[t] && k > x->slink->len+2 )
					k = x->slink->len+2, i = x->pos-x->slink->len, j = t;
		for ( printf("%d\n",k), l = 0; l < k-1; putchar(s[i+l]-'0'+'a'), ++l ) ;
		putchar(j+'a'), putchar('\n');
	}
	return 0;
}

