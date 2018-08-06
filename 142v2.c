/*
 * 142. Keyword
 * TOPIC: bf, bits
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define N (1<<20)

unsigned char a[(N>>3)+8];
char s[N];
int n;

int main() {
	int i,j,k;
	unsigned int u,v;
	for ( ;2 == scanf("%d %s",&n,s); ) {
		for ( i = 0; i < n; s[i] = (s[i]=='a'?'0':'1'), ++i ) ;
		for ( k = 1; BIT(k) <= n+n; ++k ) {
			memset(a,0,sizeof a);
			for ( u = 0, i = 0; i < k; u |= (((unsigned int)(s[i]-'0'))<<i), ++i ) ;
			for ( a[u>>3]|=BIT(u&7), j=k; j<n; u>>=1, u|=(((unsigned int)(s[j]-'0'))<<(k-1)), u&=MASK(k), a[u>>3]|=BIT(u&7), ++j ) ;
			for ( v = n+n, u = 0; u < BIT(k) && v == n+n; ++u )
				if ( !(a[u>>3] & BIT(u&7)) ) v = u;
			if ( v < n+n ) {
				for ( printf("%d\n",k), i = 0; i < k; putchar(((v>>i)&1)+'a'), ++i ) ;
				putchar('\n');
				break ;
			}
		}
	}
	return 0;
}

