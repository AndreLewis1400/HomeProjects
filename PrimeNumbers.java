
public class PrimeNumbers {
	public static void main(String[] args)
	{
        int p;
        int i;
        boolean isPrime;

        int[] primes = new int[50]; 
        int primeIndex = 2;

        // hardcode prime numbers
        primes[0] = 2; // element 0
        primes[1] = 3; // element 1

        for (p = 5; p <= 100; p = p +2) // Algorithm to determine if number is a prime
        {
            isPrime = true;
            
            for (i = 1; isPrime && p / primes[i] >= primes[i]; ++i) // && expresion skips iteration if not true

            
            
			if (p % primes[i] == 0) // skip iteration if not prime
            {
                isPrime = false;
            }
            if (isPrime == true) // add prime to array
            {
                primes[primeIndex] = p;
                ++primeIndex;
            }
        }
        for (i = 0; i < primeIndex; ++i) // display output
            System.out.println(primes[i]);

}
}