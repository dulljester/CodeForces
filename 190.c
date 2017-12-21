/*
 * 190. Dominos
 * TOPIC: bipartite matching
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SH (6)
#define BIT(k) (1ULL<<(k))
#define N (45)
#define MASK(k) (BIT(k)-1ULL)
#define vc(x,y) (0<=(x) && (x)<n && 0<=(y) && (y)<n)
#define Q (1<<13)
enum { S, T, NONE };
int min( int x, int y ) { return x>y?y:x; }

char color[N][N];
int n,m,V[2],ok,seen[N*N],
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1},
	*deg,**adj,**mate,
	yes;
short id[2][N][N],occupied[N][N],q[Q],head,tail,cnt,rid[2][N*N];

void dfs( int x, int y, int t ) {
	int i,nx,ny;
	//assert( color[x][y] == NONE ) ;
	for ( color[x][y] = t, i = 0; i < 4; ++i )
		if ( vc(nx=x+dx[i],ny=y+dy[i]) )
			if ( occupied[nx][ny] != yes ) {
				if ( color[nx][ny] == t ) {
					/*ok = 0;
					return ;*/
					continue ;
				}
				if ( color[nx][ny] == NONE )
					dfs(nx,ny,t^1);
			}
}

int alt_path( int x ) {
	int i,y;
	if ( seen[x] == yes )
		return 0;
	for ( seen[x] = yes, i = 0; i < deg[x]; ++i )
		if ( mate[T][y = adj[x][i]] == -1 || alt_path(mate[T][y]) ) {
			mate[S][mate[T][y] = x] = y;
			return 1;
		}
	return 0;
}

int bpm() {
	int change,x,k;
	for ( head = tail = 0, cnt = 0, x = 0; x < V[S]; ++x )
		q[tail++] = x, tail &= (Q-1), ++cnt;
	do {
		for ( change = 0, k = cnt, ++yes; k--; ) {
			x = q[head++], head &= (Q-1), --cnt;
			if ( alt_path(x) ) change = 1;
			else q[tail++] = x, tail &= (Q-1), ++cnt;
		}
	} while ( change );
	return V[S]-cnt;
}

void decide( int u, int v, int *hor, int *ver ) {
	int xs = rid[S][u]/n, ys = rid[S][u]%n,
		xt = rid[T][v]/n, yt = rid[T][v]%n;
	if ( xs == xt )
		++(*hor);
	else ++(*ver);
}

int main() {
	int i,j,k,l,t,xs,xt,ys,yt,u,v,hor,ver;
	for (;2 == scanf("%d %d",&n,&m) && ++yes;) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; color[i][j++] = NONE ) ;
		for ( k = 0; k < m; ++k ) {
			scanf("%d %d",&j,&i), --i, --j, i = n-1-i;
			occupied[i][j] = yes;
		}
		for ( ok = 1, V[S] = V[T] = 0, i = 0; i < n && ok; ++i ) 
			for ( j = 0; j < n && ok; ++j )
				if ( occupied[i][j] != yes )
					if ( color[i][j] == NONE )
						dfs(i,j,S);
		if ( !ok ) {
			puts("No");
			continue ;
		}
		for ( V[S] = V[T] = 0, i = 0; i < n; ++i ) 
			for ( j = 0; j < n; ++j )
				if ( occupied[i][j] != yes ) 
					t = color[i][j], rid[t][id[t][i][j] = V[t]++] = (i*n+j);
		if ( V[S] != V[T] ) {
			puts("No");
			continue ;
		}
		if ( V[S] == 0 ) {
			puts("Yes");
			puts("0"), puts("0");
			continue ;
		}
		deg = (int *)calloc(V[S],sizeof *deg);
		adj = (int **)malloc(V[S]*sizeof *adj);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( occupied[i][j] != yes && color[i][j] == S )
					for ( k = 0; k < 4; ++k )
						if ( vc(i+dx[k],j+dy[k]) && occupied[i+dx[k]][j+dy[k]] != yes && color[i+dx[k]][j+dy[k]] == T ) {
							//assert( color[i+dx[k]][j+dy[k]] == T );
							++deg[id[S][i][j]];
						}
		for ( i = 0; i < V[S]; ++i )
			if ( deg[i] )
				adj[i] = (int *)malloc(deg[i]*sizeof *adj[i]);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( occupied[i][j] != yes && color[i][j] == S )
					for ( l = 0, k = 0; k < 4; ++k )
						if ( vc(i+dx[k],j+dy[k]) && occupied[i+dx[k]][j+dy[k]] != yes && color[i+dx[k]][j+dy[k]] == T ) {
							//assert( color[i+dx[k]][j+dy[k]] == T );
							adj[id[S][i][j]][l++] = id[T][i+dx[k]][j+dy[k]];
						}
		mate = (int **)malloc(2*sizeof *mate);
		for ( t = S; t <= T; ++t )
			if ( V[t] ) {
				mate[t] = (int *)malloc(V[t]*sizeof *mate[t]);
				for ( i = 0; i < V[t]; mate[t][i++] = -1 ) ;
			}
		if ( bpm() < V[S] ) {
			puts("No");
			continue ;
		}
		puts("Yes"), hor = ver = 0;
		for ( i = 0; i < V[S]; ++i ) {
			//assert( mate[S][i] != -1 );
			j = mate[S][i];
			decide(i,j,&hor,&ver);
		}
		printf("%d\n",hor);
		for ( i = 0; i < V[S]; ++i ) {
			v = mate[S][i], xs = rid[S][i]/n, ys = rid[S][i]%n;
			xt = rid[T][v]/n, yt = rid[T][v]%n;
			if ( xs == xt ) {
				xs = n-1-xs, xt = n-1-xt;
				printf("%d %d\n",min(ys,yt)+1,xs+1);
			}
		}
		printf("%d\n",ver);
		for ( i = 0; i < V[S]; ++i ) {
			v = mate[S][i], xs = rid[S][i]/n, ys = rid[S][i]%n;
			xt = rid[T][v]/n, yt = rid[T][v]%n;
			if ( ys == yt ) {
				xs = n-1-xs, xt = n-1-xt;
				printf("%d %d\n",ys+1,min(xs,xt)+1);
			}
		}
	}
	return 0;
}

