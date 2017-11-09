/*
 * 105. Div3
 * TOPIC: ad hoc, easy interview bit
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int i,j,k,n;
	for ( ;1 == scanf("%d",&n); ) {
		k = n/3, i = (n%3);
		printf("%d\n",2*k+(i<=1?0:1));
	}
	return 0;
}

