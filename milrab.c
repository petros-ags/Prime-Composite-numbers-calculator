#include <stdio.h>
#include <time.h>
#define MINNUM 3990000000
#define MAXNUM 4010000000

unsigned long long int modular_power(unsigned long long int base, unsigned long long int exponent, unsigned long long int mod)
{
    unsigned long long x = 1;
    unsigned long long y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        	y = (y * y) % mod;
        	exponent = exponent / 2;
    }
    return x % mod;
}

int main(void)
{					//DETERMINISTIC

	printf("Checking range [%lu,%lu] for primes: \n", MINNUM, MAXNUM);				//i,j help to count primes and composites
	double sttime0, endtime0;									//time variables declaration
	sttime0 = ((double) clock())/CLOCKS_PER_SEC;							//start cpu time
    	unsigned int i, j;
	int  count = 0, flag;										//count for prime total,flag to determine result(prime or composite)
    	for (i = MINNUM; i <= MAXNUM; i++)								//main calculation process
    	{
        		flag = 0;
        		for (j = 2; j*j<= i; j++)
       		 	{
            		if ((i % j) == 0)
            		{
                		flag = 1;
               		 	break;
            		}
        	 	}
        		if (flag == 0)
        		{								
            		count++;									//count increase,"printf("%u\n", i);" if i want to print primes
        		}
    	}
    	endtime0 = ((double) clock())/CLOCKS_PER_SEC;				
    	printf("Deterministic algorithm: Found %d primes in %.2f secs\n", count, endtime0-sttime0);	//stop cpu time

					//MILLER-RABIN
///////////////////////////////////////////////////////////////////////////////////////////////////
    	double sttime, endtime;										//time variables declaration
	sttime = ((double) clock())/CLOCKS_PER_SEC;
	unsigned long long int x, d, n, r;
	int i1, a, j1, flag1, c = 0;
	for(n= MINNUM; n <= MAXNUM; n++)								//flag = 0 prime flag = 1 composite
	{
		if(n % 2 == 0)
		{
			continue;
		}
		d = n-1;										//calculate d,r,express n-1 = (2^r) * d
		r = 0;
		while( d % 2 == 0)
		{
			r++;
			d /= 2;
		}
			flag1 = 0;
			for(i1 = 1; i1<=3; i1++)							//choose "a"
			{
				switch(i1)
				{
					case 1: a = 2;
					break;
					case 2: a = 7;
					break;
					case 3: a = 61;
					break;
					default: break;
				}
				x = modular_power(a, d-1, n);
				x = (a * x) % n;
				if( x == 1 || x == n-1)
				{
					continue;
				}
				for(j1 = 1; j1<= r-1; j1++)
				{
					x = modular_power(x, 2, n);
					x = x % n;
					if(x == n-1)
					{
						break;
					}
				}
				if (j1 >= r)								//reverse expression of j1<= r-1 to find composites
				{
					flag1 = 1;
				}
			}
		if (flag1 == 0)
		{
			c++;										//"printf("%u\n", n);" to print primes
		}
	}
	endtime = ((double) clock())/CLOCKS_PER_SEC;							//stop cpu time
   	printf("Miller-Rabin algorithm: Found %u primes in %.2f secs\n", c, endtime-sttime);
	return 0;
}
