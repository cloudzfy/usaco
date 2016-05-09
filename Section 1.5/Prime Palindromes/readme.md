## Prime Palindromes

The number 151 is a prime palindrome because it is both a prime number and a palindrome (it is the same number when read forward as backward). Write a program that finds all prime palindromes in the range of two supplied numbers a and b (5 <= a < b <= 100,000,000); both a and b are considered to be within the range .

#### PROGRAM NAME: pprime

#### INPUT FORMAT

* Line 1:	Two integers, a and b

#### SAMPLE INPUT (file pprime.in)
```
5 500
```

#### OUTPUT FORMAT

The list of palindromic primes in numerical order, one per line.

#### SAMPLE OUTPUT (file pprime.out)
```
5
7
11
101
131
151
181
191
313
353
373
383
```

#### HINTS

* Generate the palindromes and see if they are prime.
* Generate palindromes by combining digits properly. You might need more than one of the loops like below.
```
/* generate five digit palindrome: */
for (d1 = 1; d1 <= 9; d1+=2) {	/* only odd; evens aren't so prime */
    for (d2 = 0; d2 <= 9; d2++) {
        for (d3 = 0; d3 <= 9; d3++) {
	    palindrome = 10000*d1 + 1000*d2 +100*d3 + 10*d2 + d1;
	    ... deal with palindrome ...
	}
    }
}
```
