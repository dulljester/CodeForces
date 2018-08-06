/*
 * 0196E: Opening Portals
 * TOPIC: Dijkstra, MST
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
#define tol (1e-13)
#define N (1<<20)
#define oo (1ULL<<62)
#define bubble (swap(pos[heap[i]],pos[heap[j]]),swap(heap[i],heap[j]))
typedef unsigned long long i64;
using namespace std;

int n,m,closest_portal[N],portal[N],_rank[N],p[N],heap[N],pos[N],cnt;
i64 d[N];
vector<pair<int,i64> > adj[N];
set<pair<i64,int> > s;

struct edge {
	int x,y;
	i64 w;
	edge() {};
	edge( int x, int y, i64 w ) { this->x= x, this->y= y, this->w= w; };
	bool operator < ( const edge &e ) const {
		if ( w < e.w )
			return true ;
		if ( w > e.w )
			return false ;
		return x < e.x || x == e.x && y < e.y;
	}
};

set<edge> edges;
vector<edge> vec;

void make_set( int x ) { _rank[p[x]= x]= 0; }

void link( int x, int y ) {
	if ( _rank[x] > _rank[y] )
		p[y]= x;
	else {
		p[x]= y;
		if ( _rank[x] == _rank[y] )
			++_rank[y];
	}
}

int find( int x ) { return p[x]= (p[x]==x?x:find(p[x])); }

void merge( int x, int y ) { link(find(x),find(y)); }

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt]= x]= cnt, ++cnt;
	for ( j= pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j= i ) ;
}

int pop() {
	int i,j,x= *heap;
	if ( cnt+= (pos[x]=-1) )
		pos[*heap= heap[cnt]]= 0;
	for ( j= 0; (i=j, j <<= 1, ++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[j]] >= d[heap[i]] ) break ;
	}
	return x;
}

int main() {
	int i,j,k,x,y;
	i64 weight,ans;
	for ( ;2 == scanf("%d %d",&n,&m); ) {
		for ( x= 0; x < n; adj[x++].clear() ) ;
		for ( vec.clear(), i= 0; i < m; ++i ) {
			cin >> x >> y >> weight;
			--x, --y;
			adj[x].push_back({y,weight});
			adj[y].push_back({x,weight});
			vec.push_back(edge(x,y,weight));
		}
		for ( cnt= 0, x= 0; x < n; pos[x]= -1, d[x++]= +oo ) ;
		for ( cin >> m, i= 0; i < m; ++i ) {
			cin >> portal[i]; x= --portal[i];
			closest_portal[x]= x, d[x]= 0, push(x);
		}
		while ( cnt ) {
			for ( x= pop(), i= 0; i < (int)adj[x].size(); ++i ) {
				y= adj[x][i].first, weight= adj[x][i].second;
				if ( d[y] > d[x]+weight ) {
					d[y]= d[x]+weight;
					closest_portal[y]= closest_portal[x];
					push(y);
				}
			}
		}
		for ( edges.clear(), i= 0; i < (int)vec.size(); ++i ) {
			x= vec[i].x, y= vec[i].y, weight= vec[i].w;
			edges.insert(edge(closest_portal[x],closest_portal[y],weight+d[x]+d[y]));
		}
		for ( ans= 0, i= 0; i < m; make_set(portal[i++]) ) ;
		for ( set<edge>:: iterator it= edges.begin(); it != edges.end(); ++it ) {
			x= it->x, y= it->y, weight= it->w;
			if ( find(x) != find(y) ) 
				merge(x,y), ans+= weight;
		}
		cout << (ans+d[0]) << endl;
	}
	return 0;
}

