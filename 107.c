/*
 * 107.
 * TOPIC: modular arithmetic, original
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int i,j,k,n;
	for ( ;1 == scanf("%d",&n); ) {
		if ( n < 9 ) puts("0");
		else if ( n == 9 ) puts("8");
		else {
			/*putchar('1'), putchar('8');*/
			putchar('7'), putchar('2');
			for ( i = 0; i < n-10; ++i )
				putchar('0');
			putchar('\n');
		}
	}
	return 0;
}

