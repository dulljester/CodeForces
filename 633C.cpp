/*
 * C. Spy Syndrome 2
 * TOPIC: Aho-Corasick, dp, queue
 * status: MLE on test 59
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
#define BIT(k) (1ULL<<(k))
#define TST(u,k) ((u) & BIT(k))
#define SET(u,k) ((u) |= BIT(k))
#define L(k) ((k) & ((~(k))+1ULL))
#define tol (1e-13)
using namespace std;
#define SLEN (10100)
#define MAXLEN (0x400)
#define N (1000000+7)
#define Q (N)
#define A 26

typedef struct cell {
	unsigned int u;
	cell *son[A];
	cell *slink;
	set<int> idx;
	cell() {};
} cell;

char text[SLEN],wh[BIT(20)];
int who( unsigned int u ) { return u>=BIT(20)?20+wh[u>>20]:wh[u]; }
int m,n,which[SLEN];
short len[100100];
cell *ptr,pool[Q],*root,*q0;
queue<cell *> q;
bool can_cover[SLEN];
vector<string> vec;

cell *init() {
	cell *x = ptr++;
	x->slink = NULL, x->u = 0, x->idx.clear();
	return x;
}

void push( char *s, int idx ) {
	cell *x,*y;
	for ( x = root; *s; x = x->son[tolower(*s)-'a'], ++s )
		if ( !TST(x->u,(tolower(*s)-'a')) )
			x->son[tolower(*s)-'a'] = init(), SET(x->u,tolower(*s)-'a');
	x->idx.insert(idx);
}

void dump( int i ) {
	if ( i ) 
		dump(i-len[which[i]]), printf("%s ",vec[which[i]-1].c_str());
}

bool exists( cell *x, char *s ) {
	if ( !*s ) return x->idx.size()>0;
	if ( !x ) return false ;
	return TST(x->u,tolower(*s)-'a')?exists(x->son[tolower(*s)-'a'],s+1) : false ;
}

set<int> st[SLEN];
map<int,map<int,int> > mp;

int main() {
	int i,j,k,l,t,ch;
	char tmp[MAXLEN];
	char *s;
	cell *x,*y,*z;
	unsigned int u;
	for ( i = 0; i < 20; wh[BIT(i)] = i, ++i ) ;
	for ( ;2 == scanf("%d %s",&n,text+1); ) {
		for ( mp.clear(), i = 0; i <= n; can_cover[i++] = false ) ;
		ptr = pool, q0 = init(), root = init();
		for ( root->slink = q0, i = 0; i < A; ++i )
			q0->son[i] = root, SET(q0->u,i);
		for ( vec.clear(), scanf("%d",&m), i = 1; i <= m; len[i] = j, ++i ) {
			for ( scanf("%s",tmp), j = 0; tmp[j]; ++j ) ;
			vec.push_back(string(tmp));
			for ( k = 0, l = j-1; k < l; ++k, --l )
				swap(tmp[k],tmp[l]);
			if ( !exists(root,tmp) ) push(tmp,i);
		}
		for ( i = 0; i <= n; st[i++].clear() ) ;
		for ( u = root->u; u; i = who(L(u)), x=root->son[i], x->slink=root, q.push(x), u &= ~L(u) ) ;
		for ( ;!q.empty(); ) {
			x = q.front(), q.pop();
			for ( u = x->u; u; u &= ~L(u) ) {
				i = who(L(u));
				y = x->son[i], ch = i;
				for ( z = x->slink; z && !TST(z->u,ch); z = z->slink ) ;
				assert( z ) ;
				y->slink = z->son[ch];
				for ( set<int> :: iterator jt = y->slink->idx.begin(); jt != y->slink->idx.end(); y->idx.insert(*jt++) ) ;
				q.push(y);
			}
		}
		for ( s = text, x = root, i = 1; i <= n; ++i ) {
			if ( !TST(x->u,s[i]-'a') ) 
				for ( x = x->slink; x && !TST(x->u,s[i]-'a'); x = x->slink ) ;
			assert( x );
			x = x->son[s[i]-'a'];
			for ( set<int> :: iterator it = x->idx.begin(); it != x->idx.end();	) {
				j = *it++;
				if ( !st[i-len[j]+1].count(len[j]) )
					mp[i-len[j]+1].clear();
				st[i-len[j]+1].insert(len[j]);
			   	mp[i-len[j]+1][len[j]] = j;
			}
		}
		queue<int> e;
		for ( can_cover[0] = true, e.push(0); !e.empty() && !can_cover[n]; ) {
			i = e.front(), e.pop();
			if ( i == n ) break ;
			if ( !st[i+1].size() ) continue ;
			for ( set<int> :: iterator it = st[i+1].begin(); it != st[i+1].end(); ++it ) {
				k = *it, j = (i+1)+k-1;
				if ( !can_cover[j] )
					can_cover[j] = true, which[j] = mp[i+1][t], e.push(j);
			}
		}
		assert( can_cover[n] );
		dump(n), putchar('\n');
	}
	return 0;
}

