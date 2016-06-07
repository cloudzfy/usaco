## Checker Challenge

Examine the 6x6 checkerboard below and note that the six checkers are arranged on the board so that one and only one is placed in each row and each column, and there is never more than one in any diagonal. (Diagonals run from southeast to northwest and southwest to northeast and include all diagonals, not just the major two.)
```
          Column
    1   2   3   4   5   6
  -------------------------
1 |   | O |   |   |   |   |
  -------------------------
2 |   |   |   | O |   |   |
  -------------------------
3 |   |   |   |   |   | O |
  -------------------------
4 | O |   |   |   |   |   |
  -------------------------
5 |   |   | O |   |   |   |
  -------------------------
6 |   |   |   |   | O |   |
  -------------------------
```

The solution shown above is described by the sequence 2 4 6 1 3 5, which gives the column positions of the checkers for each row from 1 to 6:
```
ROW     1	2	3	4	5	6
COLUMN	2	4	6	1	3	5
```

This is one solution to the checker challenge. Write a program that finds all unique solution sequences to the Checker Challenge (with ever growing values of N). Print the solutions using the column notation described above. Print the the first three solutions in numerical order, as if the checker positions form the digits of a large number, and then a line with the total number of solutions.

#### TIME LIMIT: 1 CPU second

#### PROGRAM NAME: checker

#### INPUT FORMAT

* A single line that contains a single integer N (6 <= N <= 13) that is the dimension of the N x N checkerboard.

#### SAMPLE INPUT (file checker.in)
```
6
```

#### OUTPUT FORMAT

* The first three lines show the first three solutions found, presented as N numbers with a single space between them. The fourth line shows the total number of solutions found.

#### SAMPLE OUTPUT (file checker.out)
```
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4
```

#### HINTS

1. Use recursion:

  ```
  function placequeen(column) {   # place columns 0..max-1
  	if (column == max) { deal with answer; return; }
    for (row = 0; row < max; row++)  {
      if (canplacequeen (row)) {
  		  mark queen placed at column,row;
  		  placequeen(column+1);
  		  un-mark queen placed at column,row;
  	  }
    }
  }
  ```
2. Do everything you can to eliminate loops (searching) in the part of your program executed most frequently. Usually, the best way to do this is to 'trade memory for speed'. When checking to see if a queen can be placed in a given row, for example, store a row status list that says if a queen is already stored there or not:

  ```
  function placequeen(column) {   # place columns 0..max-1
  	if (column == max) { deal with answer; return; }
    for (row = 0; row < max; row++)  {
      if (rowok[row] && canplacequeen(row,column)) {
  		  rowok[row] = 1;
  		  mark queen placed at column,row;
  		  placequeen(column+1);
  		  un-mark queen placed at column,row;
  		  rowok[row] = 0;
  		}
  	}
  }
  ```

3. Do *absolutely everything* you can to eliminate loops (searching) in the part of your program executed most frequently. Keep track not only of the rows that are legal for queen placement but also which of the two sorts of diagonals (the ones that are like a '/' and the others that are like '\' by using an array of size 2 * max - 1 that records whether a diagonal is legal or not.

4. SYMMETRY. Can you eliminate half or 3/4 of the cases you test by studying rotations, reflections, or something like that? [hint: yes]

5. Still over time? If you have programmed modularly and have little subroutines to check diagonals, etc., move that code into the main execution stream. The subroutine call overhead is nontrivial.

6. Most successful Java solutions store their 'this column used' marks as bits in a word.
