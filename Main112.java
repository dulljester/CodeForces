/*
 * 112. a^b-b^a
 * TOPIC: BigInteger
 * status: Accepted
 */
import java.math.BigInteger;
import java.util.*;

public class Main112 {
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main112().go();
	}

	void go() throws Exception {
		int n = scan.nextInt(), m = scan.nextInt();
		BigInteger z = BigInteger.valueOf(n).pow(m).subtract(BigInteger.valueOf(m).pow(n));
		System.out.println(z);
	}
}
