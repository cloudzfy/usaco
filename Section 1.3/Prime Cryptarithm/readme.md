## Prime Cryptarithm

The following cryptarithm is a multiplication problem that can be solved by substituting digits from a specified set of N digits into the positions marked with *. If the set of prime digits {2,3,5,7} is selected, the cryptarithm is called a PRIME CRYPTARITHM.

```
      * * *
   x    * *
    -------
      * * *         <-- partial product 1
    * * *           <-- partial product 2
    -------
    * * * *
```

Digits can appear only in places marked by '*'. Of course, leading zeroes are not allowed.

**The partial products must be three digits long,** even though the general case (see below) might have four digit partial products. 

********** Note About Cryptarithm's Multiplication ************

In USA, children are taught to perform multidigit multiplication as described here. Consider multiplying a three digit number whose digits are 'a', 'b', and 'c' by a two digit number whose digits are 'd' and 'e':

```
[Note that this diagram shows far more digits in its results than
the required diagram above which has three digit partial products!]

          a b c     <-- number 'abc'
        x   d e     <-- number 'de'; the 'x' means 'multiply'
     -----------
p1      * * * *     <-- product of e * abc; first star might be 0 (absent)
p2    * * * *       <-- product of d * abc; first star might be 0 (absent)
     -----------
      * * * * *     <-- sum of p1 and p2 (e*abc + 10*d*abc) == de*abc
```

Note that the 'partial products' are as taught in USA schools. The first partial product is the product of the final digit of the second number and the top number. The second partial product is the product of the first digit of the second number and the top number.

Write a program that will find all solutions to the cryptarithm above for any subset of supplied non-zero single-digits.

#### PROGRAM NAME: crypt1

#### INPUT FORMAT

* Line 1:	N, the number of digits that will be used
* Line 2:	N space separated non-zero digits with which to solve the cryptarithm

#### SAMPLE INPUT (file crypt1.in)
```
5
2 3 4 6 8
```

#### OUTPUT FORMAT

A single line with the total number of solutions. Here is the single solution for the sample input:

```
      2 2 2
    x   2 2
     ------
      4 4 4
    4 4 4
  ---------
    4 8 8 4
```

#### SAMPLE OUTPUT (file crypt1.out)
```
1
```
