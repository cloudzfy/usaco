## Cowcycles

Having made a fortune on Playbov magazine, Hugh Heifer has moved from his original field in the country to a fashionable yard in the suburbs. To visit fond pastoral memories, he wishes to cowmmute back to his old stomping grounds. Being environmentally minded, Hugh wishes to transport himself using his own power on a Cowcycle (a bicycle specially fitted for his neatly manicured hooves).

Hugh weighs over a ton; as such, getting smoothly up to speed on traditional cowcycle gear sets is a bit challenging. Changing among some of the widely spaced gear ratios causes exertion that's hard on Hugh's heart.

Help Hugh outfit his Cowcycle by choosing F (1 <= F <= 5) gears (sprockets) in the front and R (1 <= R <= 10) gears in the rear of his F*R speed cowcycle subject to these rules:

* The possible sizes (number of teeth) for the F front gears are specified.
* The possible sizes (number of teeth) for the R rear gears are specified.
* At any given gear setting, the gear ratio is the quotient of the number of teeth on the front gear and the number of teeth on the rear gear (i.e., number of front gear teeth divided by number of rear gear teeth)
* The largest gear ratio must be at least three times the smallest.
* The variance (see below) of the set of DIFFERENCES between successive (i.e., after sorting) gear ratios should be minimized.

Calculate the mean and variance of a set of differences (xi in this formula) by the following formulae:

```
        1    n
mean = ---  SUM xi
        n   i=1   
```

```
            1    n    
variance = ---  SUM (xi - mean)2
            n   i=1    
```

Deduce and print the optimal sets of F front gears and R rear gears so that the variance is minimized (and the ratios span a factor of at least 3x).

#### PROGRAM NAME: cowcycle

#### INPUT FORMAT

The first line contains F and R, the numbers of front and rear gears. The second line contains four numbers: F1, F2 (25 <= F1 < F2 <= 80), R1, and R2 (5 <= R1 < R2 <= 40). All front gears from F1 through F2 are available; all rear gears from R1 through R2 are available. There will exist at least one legal set of gears.

#### SAMPLE INPUT (file cowcycle.in)
```
2 5
39 62 12 28
```

#### OUTPUT FORMAT

Display the number of teeth on the set of F chosen front gears, from smallest to largest, on the first line of output (separated by spaces). Display the number of teeth on the set of R chosen rear gears, from smallest to largest, on the second line of output. All gears have an integer number of teeth, of course.

If multiple optimal answers exist, output the answer with the smallest front gear set (smallest first gear, or smallest second gear if first gears match, etc.). Likewise, if all first gears match, output the answer with the smallest rear gear set (similar rules to the front gear set).

#### SAMPLE OUTPUT (file cowcycle.out)
```
39 53
12 13 15 23 27
```

#### Comment

The problem wants you to find "an optimal set of gear ratios" such that the spacing between the ratios is most uniform. Consider the test case above:
```
2 5
39 62 12 28
```

This specifies two front gears from the set 39..62; five rear gears from the set 12..28. The program must examine all possible pairs of 62-39+1=24 front gears and all possible quintuples from 28-12+1=17 rear gears. Combinatorically, The total number of possibilities is (24 take 2) times (17 take 5), which is 24!/22!/2! x 17!/5!/12! which is 656,880 possibilities (I think).

For each of these possibilities, calculations like the following. This example considers in some sense the "first" case: front gears of 39 and 40, rear gears of 12, 13, 14, 15, and 16.

First, calculate all the possible ratios:
```
39/12 = 3.25000000000000000000
39/13 = 3.00000000000000000000
39/14 = 2.78571428571428571428
39/15 = 2.60000000000000000000
39/16 = 2.43750000000000000000
40/12 = 3.33333333333333333333
40/13 = 3.07692307692307692307
40/14 = 2.85714285714285714285
40/15 = 2.66666666666666666666
40/16 = 2.50000000000000000000
```

Then, sort them:
```
39/16 = 2.43750000000000000000
40/16 = 2.50000000000000000000
39/15 = 2.60000000000000000000
40/15 = 2.66666666666666666666
39/14 = 2.78571428571428571428
40/14 = 2.85714285714285714285
39/13 = 3.00000000000000000000
40/13 = 3.07692307692307692307
39/12 = 3.25000000000000000000
40/12 = 3.33333333333333333333
```

Then, calculate the absolute value of the differences:
```
2.43750000000000000000 - 2.50000000000000000000 = 0.06250000000000000000
2.50000000000000000000 - 2.60000000000000000000 = 0.10000000000000000000
2.60000000000000000000 - 2.66666666666666666666 = 0.06666666666666666666
2.66666666666666666666 - 2.78571428571428571428 = 0.11904761904761904762
2.78571428571428571428 - 2.85714285714285714285 = 0.07142857142857142857
2.85714285714285714285 - 3.00000000000000000000 = 0.14285714285714285715
3.00000000000000000000 - 3.07692307692307692307 = 0.07692307692307692307
3.07692307692307692307 - 3.25000000000000000000 = 0.17307692307692307693
3.25000000000000000000 - 3.33333333333333333333 = 0.08333333333333333333
```

Then, calculate the mean and variance of the set of numbers on the right, above. The mean is (I think): 0.0995370370370370370366666. The variance is approximately 0.00129798488416722.

Of course this set of gears is not valid, since it does not have a 3x span from highest gear to lowest.

Find the set of gears that minimizes the variance and has a 3x or greater span. 
