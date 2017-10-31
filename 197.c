/*
 * 197. Nice Patterns Strike Back
 * TOPIC: DP on bitmasks, matrix expo
 * sttus: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<5)

char buff[0x400];
int m,MOD,len,c[0x400],A[N][N],ax[N][N],x[N][N],t[N][N];

int div2() {
	int carry = 0,tmp,i;
	for ( i = len-1; i >= 0; --i ) {
		tmp = ((10*carry+c[i])&1);
		c[i] = (10*carry+c[i])>>1;
		carry = tmp;
	}
	for ( ;len && c[len-1] == 0; --len ) ;
	if ( !len ) len = 1;
	return carry;
}

int compatible( unsigned int u, unsigned int v ) {
	int i;
	for ( i = 0; (i+1) < m; ++i )
		if ( ((u>>i)&3) == 3 || ((u>>i)&3) == 0 )
			if ( ((u>>i)&3) == ((v>>i)&3) )
				return 0;
	return 1;
}

int f( int x, int y ) {
	int z = (x+y);
	if ( z >= MOD )
		return z-MOD;
	if ( z < 0 ) {
		for ( ;z < 0; z += MOD );
		return z%MOD;
	}
	return z;
}

int is_zero() {
	return len == 1 && !c[0];
}

int main() {
	int i,j,k,ans;
	unsigned int u,v;
	for ( ;3 == scanf("%s %d %d",buff,&m,&MOD); ) {
		for ( len = 0; buff[len] && buff[len] != '\n'; ++len ) ;
		for ( i = 0, j = len-1; i < len; c[i++] = buff[j--]-'0' ) ;
		for ( --c[0], i = 0; i < len; ++i )
			if ( c[i] < 0 )
				for ( ;c[i] < 0; c[i] += 10, --c[i+1] ) ;
		for ( ;len && !c[len-1]; --len ) ;
		if ( !len ) len = 1;
		memset(A,0,sizeof A);
		for ( u = 0; u < (1<<m); ++u )
			for ( v = 0; v < (1<<m); ++v ) 
				x[u][v] = A[u][v] = compatible(u,v), ax[u][v] = (u==v)?1:0;
		for ( ;!is_zero(); ) {
			//puts("Here");
			if ( div2() ) {
				for ( i = 0; i < (1<<m); ++i )
					for ( j = 0; j < (1<<m); ++j )
						for ( t[i][j] = 0, k = 0; k < (1<<m); ++k )
							t[i][j] = f(t[i][j],(ax[i][k]*x[k][j])%MOD);
				for ( i = 0; i < (1<<m); ++i )
					for ( j = 0; j < (1<<m); ++j )
						ax[i][j] = t[i][j];
			}
			for ( i = 0; i < (1<<m); ++i )
				for ( j = 0; j < (1<<m); ++j )
					for ( t[i][j] = 0, k = 0; k < (1<<m); ++k )
						t[i][j] = f(t[i][j],(x[i][k]*x[k][j])%MOD);
			for ( i = 0; i < (1<<m); ++i )
				for ( j = 0; j < (1<<m); ++j )
					x[i][j] = t[i][j];
		}
		for ( ans = 0, i = 0; i < (1<<m); ++i )
			for ( j = 0; j < (1<<m); ++j )
				ans = f(ans,ax[i][j]);
		printf("%d\n",ans);
	}
	return 0;
}

