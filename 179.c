/*
 * 179. Brackets Light
 * TOPIC: lex order, correct bracket sequence, cbs
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (10100)

int n,pref[N];
char s[N];

int main() {
	int i,j,k,l,t;
	for ( ;1 == scanf("%s",s+1); ) {
		for ( n = strlen(s+1), i = 1; i <= n; pref[i] = pref[i-1] + (s[i]=='('?1:-1), ++i ) ;
		for ( j = n; j >= 1 && !(s[j] == '(' && pref[j] >= 2); --j ) ;
		if ( !j ) {
			puts("No solution");
			continue ;
		}
		for ( i = 1; i <= j-1; putchar(s[i++]) ) ;
		putchar(')'), k = pref[j]-2;
		l = (n-j-k);
		assert( !(l&1) );
		for ( t = 0; t < l/2; ++t, putchar('(') );
		for ( t = 0; t < l/2; ++t, putchar(')') );
		for ( t = 0; t < k; putchar(')'), ++t ) ;
		putchar('\n');
	}
	return 0;
}

