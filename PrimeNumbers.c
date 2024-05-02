#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

    int main()

    {
        int p;
        int i;
        bool isPrime;

        int primes[50] = {0}; // {0} set all elements to zero
        int primeIndex = 2;

        // hardcode prime numbers
        primes[0] = 2; // element 0
        primes[1] = 3; // element 1

        // Algorithm to determine if number is a prime
        for (p = 5; p <= 100; p = p +2) // Outer loop
        {
            isPrime = true;
            printf("%d ", p);
            for (i = 1; isPrime && p / primes[i] >= primes[i]; ++i) // if && is false skip iteration


            if (p % primes[i] == 0) // skip iteration if false // Inner loop
            {
                isPrime = false;
            }
            if (isPrime == true) // add to array if true and bounce to outer loop
            {
                primes[primeIndex] = p;
                ++primeIndex;
            }
        }
        for (i = 0; i < primeIndex; ++i)
            printf ("%i ", primes[i]);

        printf("\n");
return 0;
    }
