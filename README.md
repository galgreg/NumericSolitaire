# Numeric solitaire
## Task description
Let's say we have a game, in which there are integers arranged in a sequence.  
For each step, we choose one number (which must be neither first or last), and remove it from sequence.  
At the same time, we sum that number with its adjacents, and that sum add to our current total points.  
Game is over, when only two numbers remain in sequence.

Our goal is to compute maximum possible to gain sum of points.

## Input
There are some amount of input rows. Each input row begins from **_n_**, which is length of sequence.  
All following numbers at row are sequence items.  
Every sequence item **_k_** is integer number, where 0 < **_k_** < 201.  
Each number **_n_** > 2, except last one, which equals 0. That means end of input data.

## Output
For each input data set, program should output maximum possible to gain sum of points.  
Each output number should be placed in separate row.

## Samples:
  **Input data** - _input.txt_
  ```
5 1 2 3 4 5
5 2 1 5 3 4
6 30 20 40 50 70 60
0
  ```
  
  **Expected results** - _output.txt_
  ```
30
31
570
  ```

## Algorithm description
Algorithm used to solve task was based on [Dynamic Programming](https://www.geeksforgeeks.org/dynamic-programming/) method.  
Its core concept is to use previously computed values to compute current value.  
Thus, it allows to significant speed-up for solving wide range of problems.  
As example of such problems, see [this](https://blog.usejournal.com/top-50-dynamic-programming-practice-problems-4208fed71aa3).

## Implementation details
Program has been written in C++11. 
To parallelize computation, I used [OpenMP](https://www.openmp.org/) library.  
To compile program, I used g++ compiler in 7.4.0 version.  
Program use standard streams to receive input data and generate output results.

## How to run on Linux
### 1. Install g++ compiler
  ```
sudo apt-get update
sudo apt-get install g++
  ```
### 2. Clone Git repo
  ```
git clone https://github.com/galgreg/NumericSolitaire.git
  ```
### 3. Compile program
  ```
g++ -fopenmp -O3 pasjans.cc -o pasjans
  ```
### 4. Run program
  ```
./pasjans <example_input.txt >example_output.txt
  ```

## How to run on Windows
To run on Windows, your compiler have to support C++11 standard and OpenMP library.  
Please check apropriate documentation for more details.

## Acknowledgments
Special thanks for dr hab. Wojciech Wieczorek, who helped me a lot with finding right algorithm to solve a task.
