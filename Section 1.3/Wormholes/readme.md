## Wormholes

Farmer John's hobby of conducting high-energy physics experiments on weekends has backfired, causing N wormholes (2 <= N <= 12, N even) to materialize on his farm, each located at a distinct point on the 2D map of his farm (the x,y coordinates are both integers).

According to his calculations, Farmer John knows that his wormholes will form N/2 connected pairs. For example, if wormholes A and B are connected as a pair, then any object entering wormhole A will exit wormhole B moving in the same direction, and any object entering wormhole B will similarly exit from wormhole A moving in the same direction. This can have rather unpleasant consequences.

For example, suppose there are two paired wormholes A at (1,1) and B at (3,1), and that Bessie the cow starts from position (2,1) moving in the +x direction. Bessie will enter wormhole B [at (3,1)], exit from A [at (1,1)], then enter B again, and so on, getting trapped in an infinite cycle!

```
   | . . . .
   | A > B .      Bessie will travel to B then
   + . . . .      A then across to B again
```

Farmer John knows the exact location of each wormhole on his farm. He knows that Bessie the cow always walks in the +x direction, although he does not remember where Bessie is currently located.

Please help Farmer John count the number of distinct pairings of the wormholes such that Bessie could possibly get trapped in an infinite cycle if she starts from an unlucky position. FJ doesn't know which wormhole pairs with any other wormhole, so find all the possibilities.

#### PROGRAM NAME: wormhole

#### INPUT FORMAT:

* Line 1:	The number of wormholes, N.
* Lines 2..1+N:	Each line contains two space-separated integers describing the (x,y) coordinates of a single wormhole. Each coordinate is in the range 0..1,000,000,000.

#### SAMPLE INPUT (file wormhole.in):
```
4
0 0
1 0
1 1
0 1
```

#### INPUT DETAILS:

There are 4 wormholes, forming the corners of a square.

#### OUTPUT FORMAT:

* Line 1:	The number of distinct pairings of wormholes such that Bessie could conceivably get stuck in a cycle walking from some starting point in the +x direction.

#### SAMPLE OUTPUT (file wormhole.out):
```
2
```

#### OUTPUT DETAILS:

If we number the wormholes 1..4 as we read them from the input, then if wormhole 1 pairs with wormhole 2 and wormhole 3 pairs with wormhole 4, Bessie can get stuck if she starts anywhere between (0,0) and (1,0) or between (0,1) and (1,1).
```
   | . . . .
   4 3 . . .      Bessie will travel to B then
   1-2-.-.-.      A then across to B again
```

Similarly, with the same starting points, Bessie can get stuck in a cycle if the pairings are 1-3 and 2-4 (if Bessie enters WH#3 and comes out at WH#1, she then walks to WH#2 which transports here to WH#4 which directs her towards WH#3 again for a cycle).

Only the pairings 1-4 and 2-3 allow Bessie to walk in the +x direction from any point in the 2D plane with no danger of cycling. 
