/*
 * C. Spy Syndrome 2
 * TOPIC: dp, trie
 * status: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <queue>
#define tol (1e-13)
using namespace std;
#define SLEN (10100)
#define MAXLEN (0x400)
#define N (1000000+7)
#define BIT(k) (1ULL<<(k))
#define TST(u,k) ((u)&BIT(k))
#define SET(u,k) ((u)|=BIT(k))
#define A 26
typedef long long i64;
#define PR 31
#define MOD ((1LL<<31)-1L)
#define MAXQ (N)

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
	if ( !y ) *a = 1, *b = 0, *d = x;
	else 
		ext_euclid(y,x%y,b,a,d), *b -= (*a)*(x/y);
}

i64 inv( i64 x, i64 P ) {
	i64 a,b,d;
	for ( ext_euclid(x,P,&a,&b,&d); a < 0; a += P ) ;
	return a%P;
}

char text[SLEN];
int m,n,which[SLEN];
short len[100100];
bool can_cover[SLEN];
vector<string> vec;
//i64 Q = inv(PR,MOD), h[SLEN], INV[SLEN];

void dump( int i ) {
	if ( i ) 
		dump(i-len[which[i]]), printf("%s ",vec[which[i]-1].c_str());
}

/*
i64 hash( int i, int j ) {
	i64 ans = ((h[j]-h[i-1]+MOD)*INV[i]);
	for (;ans < 0; ans += MOD );
	return ans%MOD;
}
*/

typedef struct cell {
	unsigned int u;
	cell *son[A];
	int idx;
	cell() {};
} cell;

cell pool[MAXQ],*ptr,*root;

cell *init() {
	cell *x = ptr++;
	x->idx = -1, x->u = 0;
	assert( x );
	return x;
}

void push( char *s, int idx ) {
	cell *x,*y,**hold;
	int ch;
	for ( hold = &root, x = root; *s && *s != '\n'; hold = &(x->son[ch]), x = y, ++s ) {
		assert( x ) ;
		ch = tolower(*s)-'a';
		assert( 0 <= ch && ch < A );
		if ( !TST(x->u,ch) ) {
			x->son[ch] = y = init(), SET(x->u,ch);
			continue ;
		}
		else {
			//if ( !x->son[ch] )
			y = x->son[ch];
			//assert( y = x->son[ch] );
		}
		//assert( y = x->son[ch] );
	}
	x->idx = idx;
}

int main() {
	int i,j,k,l,t,ch,maxlen;
	char tmp[MAXLEN];
	char *s;
	cell *x,*y;
	/*
	for ( INV[0] = 1, i = 1; i < SLEN; INV[i++] %= MOD )
		for ( INV[i] = (INV[i-1]*Q); INV[i] < 0; INV[i] += MOD ) ;
		*/
	for ( ;2 == scanf("%d %s",&n,text+1); ) {
		/*
		for ( s = text, x = PR, h[0] = 0, i = 1; i <= n; h[i] %= MOD, ++i, x *= PR )
			for ( h[i] = h[i-1]+x*(s[i]-'a'); h[i] < 0; h[i] += MOD );
			*/
		for ( i = 0; i <= n; can_cover[i++] = false ) ;
		ptr = pool, root = init();
		for ( maxlen = -1, vec.clear(), scanf("%d",&m), i = 1; i <= m; maxlen = max(maxlen,(int)(len[i]=j)), ++i ) {
			for ( scanf("%s",tmp), j = 0; tmp[j]; ++j ) ;
			push(tmp,i);
			vec.push_back(string(tmp));
		}
		for ( s = text, can_cover[0] = true, i = 1; i <= n; ++i ) 
			for ( x = root, k = 0, j = i; j >= 1 && k < maxlen; --j, ++k ) {
				if ( !TST(x->u,s[j]-'a') ) break ;
				x = x->son[s[j]-'a'];
				if ( x->idx != -1 && can_cover[j-1] ) {
					which[i] = x->idx, can_cover[i] = true ;
					break ;
				}
			}
		dump(n), putchar('\n');
	}
	return 0;
}

