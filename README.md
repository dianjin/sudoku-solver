sudoku-solver
=============

A recursive backtracking sudoku solver written in C.

<h3>Folders</h3>
<ul>
<li><strong>Bitwise</strong> - This algorithm uses bitwise operations and is much faster and smaller than the inefficient version.
<li><strong>Inefficient</strong> - This algorithm is loop heavy, and really slow compared to the bitwise version.
</ul>

<h3>How the algorithm works</h3>
Both the bitwise and inefficient versions are recursive backtracking algorithms. This gif from wikimedia pretty much sums it up:<br>
<img src="http://upload.wikimedia.org/wikipedia/commons/8/8c/Sudoku_solved_by_bactracking.gif">

<h3>Other tips</h3>
<ul>
<li>This algo generates every possible Sudoku solution (there are 6.671*10^21) when you call the solve(Sudoku p) method on a 9x9 array of zeroes. Obviously, your computer won't be able to complete this operation since it could take decades.
<li>Calling the solve function 100 million times takes 56 seconds in the inefficient version and 12 seconds in the inefficient version.
</ul>
