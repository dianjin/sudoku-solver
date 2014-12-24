sudoku-solver
=============

A recursive backtracking sudoku solver written in C.

<h3>Bitwise version</h3>
The core of this algorithm relies on some bitwise functions. Although this algorithm is significantly faster and smaller than the inefficient version posted in this repo, it is missing some important optimizations used in the fastest sudoku solvers. More specifically, this algorithm does not prioritize empty cells based on the number of valid entries for that cell.

<h3>Optimizations</h3>
<ul>
<li>Finding valid entries for a cell is done with a few bitwise operations. The numbers that have been used for each row, column, and square of the sudoku are stored in short integer flags. So a simple bitwise OR is used to determine the valid entries for a given cell.
<li>A position tracker keeps track of the last filled cell of the grid, preventing redundant searches for the next empty cell. This is possible because the cells of the sudoku are always filled from left to right and top to bottom (which is not the most inefficient order to begin with).
<li> Data types were selected to prevent memory wastage. For example, using unsigned chars and shorts instead of ints where possible.

<h3>Other tips</h3>
<ul>
<li>This algo generates every possible Sudoku solution (there are 6.671*10^21) when you call the solve(Sudoku p) method on a 9x9 array of zeroes. Obviously, your computer won't be able to complete this operation since it could take decades.
<li>The easiest puzzles can be completed in less than 0.01 seconds.
<li>On my computer, 100 million recursive calls to the solve function on an empty grid takes 12 seconds. One billion recursive calls takes 109 seconds.
</ul>
