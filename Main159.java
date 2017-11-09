/*
 * 159. Self-Replicating Numbers
 * TOPIC: Chinese Remainder Theorem, BigInteger
 * status: Accepted
 */
import java.math.BigInteger;
import java.io.*;
import java.util.*;

class Solution {
	private static int MAXBASE = 36;
	private static char []digit = new char[MAXBASE+1];
	private Scanner scan = new Scanner(System.in);
	static {
		for ( int k = 0; k < 10; ++k )
			digit[k] = (char)(k+'0');
		for ( char ch = 'A'; ch <= 'Z'; ++ch )
			digit[(int)(ch-'A')+10] = ch;
	}
	public static void main( String [] args ) throws Exception {
		new Solution().go();
	}
	private class Pair<T extends Number> {
		T p,deg;
		Pair( T p, T deg ) {
			this.p = p;
			this.deg = deg;
		}
	}
	private List<Pair<Integer>> factorize( int B ) {
		List<Pair<Integer>> lst = new ArrayList<>();
		for ( int deg, p = 2; p*p <= B; ++p ) {
			if ( 0 != (B%p) ) continue ;
			for ( deg = 0; 0 == (B%p); ++deg, B /= p ) ;
			lst.add(new Pair<Integer>(p,deg));
		}
		if ( B > 1 )
			lst.add(new Pair<Integer>(B,1));
		return lst;
	}
	private Pair<BigInteger> extEuclid( BigInteger x, BigInteger y ) {
		if ( y.equals(BigInteger.ZERO) )
			return new Pair<BigInteger>(BigInteger.ONE,BigInteger.ZERO);
		Pair<BigInteger> p = extEuclid(y,x.mod(y));
		BigInteger b = p.p, a = p.deg;
		b = b.subtract(a.multiply(x.divide(y)));
		return new Pair<BigInteger>(a,b);
	}
	private BigInteger inverse( BigInteger x, BigInteger MOD ) {
		Pair<BigInteger> p = extEuclid(x,MOD);
		return p.p.mod(MOD);
	}
	private String toBase( BigInteger x, int b ) {
		StringBuilder sb = new StringBuilder();
		BigInteger B = BigInteger.valueOf(b);
		do {
			sb.append(digit[x.mod(B).intValue()]);
			x = x.divide(B);
		} while ( !x.equals(BigInteger.ZERO) ) ;
		StringBuilder r = new StringBuilder();
		String t = sb.toString();
		for ( int i = t.length()-1; i >= 0; --i )
			r.append(t.charAt(i)+"");
		return r.toString();
	}
	private void go() throws Exception {
		int b,n,i,j,k,m,u;
		BigInteger B;
		List<BigInteger> P,invC,C,prod;
		for ( ;scan.hasNext(); ) {
			b = scan.nextInt();
			assert b <= MAXBASE;
			n = scan.nextInt();
			assert n <= 2000;
			B = BigInteger.valueOf(b).pow(n);
			List<Pair<Integer>> lst = factorize(b);
			m = lst.size();
			for ( i = 0; i < m; ++i )
				lst.get(i).deg *= n;
			P = new ArrayList<>();
			C = new ArrayList<>();
			invC = new ArrayList<>();
			prod = new ArrayList<>();
			for ( i = 0; i < m; ++i ) 
				P.add(BigInteger.valueOf(lst.get(i).p).pow(lst.get(i).deg));
			for ( i = 0; i < m; ++i ) {
				BigInteger e = BigInteger.ONE;
				for ( j = 0; j < m; ++j )
					if ( i != j )
						e = e.multiply(P.get(j));
				C.add(e);
				invC.add(inverse(e,P.get(i)));
				prod.add(C.get(i).multiply(invC.get(i)));
			}
			List<BigInteger> res = new ArrayList<>();
			for ( u = 0; u < (1<<m); ++u ) {
				BigInteger ans = BigInteger.ZERO;
				for ( i = 0; i < m; ++i )
					if ( 1 == ((u>>i)&1) ) 
						ans = ans.add(prod.get(i));
				res.add(ans.mod(B));
			}
			List<String> result = new ArrayList<>();
			for ( BigInteger x: res ) {
				String z = toBase(x,b);
				if ( z.length() == n )
					result.add(z);
			}
			System.out.println(result.size());
			Collections.sort(result);
			for ( String x: result )
				System.out.println(x);
		}
	}
}

