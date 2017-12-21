/*
 * 149. computer Network
 * TOPIC: graphs, trees, DP on trees
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
#include <set>
#include <map>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define tol (1e-13)
using namespace std;
typedef unsigned long long u64;
typedef long long i64;
#define N (10100)
#define pb push_back
#define mp make_pair
enum { UP, DOWN };
#define oo (1LL<<60)

int n,p[N],seen[N],yes;
vector<pair<int,int> > adj[N];
map<i64,int> h[N];
i64 z[2][N],d[N],len[N];

void dfs( int x ) {
	assert( seen[x] != yes );
	seen[x] = yes;
	for ( int y,i = 0; i < (int)adj[x].size(); ++i )
		if ( seen[y = adj[x][i].first] != yes ) 
			p[y] = x, d[y] = d[x]+(len[y] = adj[x][i].second), dfs(y);
}

i64 calc_z( int t, int x ) {
	if ( z[t][x] < +oo )
		return z[t][x];

	int i,y;
	map<i64,int> :: iterator it;

	if ( t == DOWN && !h[x].size() ) {
		for ( i = 0; i < (int)adj[x].size(); ++i )
			if ( p[y = adj[x][i].first] == x ) {
				if ( h[x].count(-len[y]-calc_z(DOWN,y)) )
					++h[x][-len[y]-calc_z(DOWN,y)];
				else 
					h[x][-len[y]-calc_z(DOWN,y)] = 1;
			}
	}

	if ( t == DOWN ) {
		if ( !h[x].size() ) return z[t][x] = 0;
		it = h[x].begin();
		return z[t][x] = -it->first;
	}

	if ( p[x] == -1 ) return z[t][x] = 0;
	z[t][x] = len[x]+calc_z(t,p[x]);
	if ( h[p[x]][-len[x]-calc_z(DOWN,x)] == 1 ) {
		h[p[x]].erase(-len[x]-calc_z(DOWN,x));
		if ( h[p[x]].size() ) {
			it = h[p[x]].begin();
			z[t][x] = max(z[t][x],len[x]-it->first);
		}
		h[p[x]][-len[x]-calc_z(DOWN,x)] = 1;
	}
	else {
		it = h[p[x]].begin();
		z[t][x] = max(z[t][x],len[x]-it->first);
	}

	return z[t][x];
}

int main() {
	int i,j,k,ts,cs = 0,t;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; p[i] = -1, h[i].clear(), adj[i++].clear() ) ;
		for ( t = UP; t <= DOWN; ++t )
			for ( i = 0; i < n; ++i )
				z[t][i] = +oo;
		for ( i = 1; i <= n-1; ++i ) {
			scanf("%d %d",&j,&k), --j;
			adj[i].pb(mp(j,k)), adj[j].pb(mp(i,k));
		}
		++yes, d[0] = 0, dfs(0);
		for ( i = 0; i < n; ++i )
			calc_z(DOWN,i);
		for ( i = 0; i < n; ++i )
			printf("%lld\n",max(calc_z(UP,i),calc_z(DOWN,i)));
	}
	return 0;
}

