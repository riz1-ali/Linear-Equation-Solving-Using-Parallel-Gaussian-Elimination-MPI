# Linear-Equation-Solving-Using-Parallel-Gaussian-Elimination-MPI

## Input Format
First line contains an integer N, denoting the number of variables in the linear equation (Let these variables are x<sub>1</sub>,x<sub>2</sub>,...,x<sub>N</sub>).
Then, there are N lines, each of which contains N integers. Each line represents one linear equation.
Let one linear equation is represented as a<sub>1</sub>x<sub>1</sub> + a<sub>2</sub>x<sub>2</sub> + ... + a<sub>N</sub>x<sub>N</sub> = y.
i<sup>th</sup> value of a line (linear equation) represents the value of a<sub>i</sub>.
Then, there is one additional line containing N integers, each of which represents value of y for each linear equation.

## Output Format
N floating point numbers rounded to 2 decimal places, representing the values of x<sub>1</sub>,x<sub>2</sub>,...,x<sub>N</sub> in order. These values should satisfy the above equations.

## Constraints
- 2 <= N <= 100
- -100 <= a<sub>i</sub>,y <= 100
