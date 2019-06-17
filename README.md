# Numeric solitaire

## Rules
Let's say we have a game, in which there are integers arranged in a sequence.  
For each step, we choose one number (which must be neither first or last), and remove it from sequence.  
At the same time, we sum that number with its adjacents, and that sum add to our current total points.  
Game is over, when in sequence are only two numbers.

Our goal is to compute maximum, possible to gain sum of points.

## Input
There are some amount of input rows. Each input row begins from **_n_**, which is length of sequence.
All following numbers at row are sequence items.  
Every sequence item **_k_** is integer number, where 0 < **_k_** < 201.  
Each count number **_n_** > 2, except last one, which equals 0. That means end of input data.

## Output
For each input data set, program should output maximum possible to gain sum of points.
Each output number should be placed in separate row.

## Samples
  **Input data:**
  * 5 1 2 3 4 5
  * 5 2 1 5 3 4
  * 6 30 20 40 50 70 60
  * 0
  
  **Expected results:**
  * 30
  * 31
  * 570
