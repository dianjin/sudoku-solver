sudoku-solver
=============

A recursive backtracking sudoku solver written in C.

Files included:
<ul>
<li>demo.c (Demo version) - meant for demonstration purposes, as it comes with a very basic user interface.
<li>hack.c (Hack version) - meant for tinkering and customization, as it doesn't come with a user interface or any other frills. 
</ul>

The main algorithm in this particular sudoku solver is the recursive solve(Sudoku p) method. The solving begins when the solve(Sudoku p) method is called on a 2D array of ints representing the sudoku puzzle that is to be solved. (Sudoku is typedef'd as int[9][9].) Every time solve(Sudoku p) is called, the program inputs a valid number into the next cell of the Sudoku grid and calls the solve(Sudoku p) method on that resulting Sudoku grid. The program "backtracks" when it reaches a point at which there are no valid numbers for a particular cell.

For both demo.c and hack.c:
The solve(Sudoku p) method returns an int representing the number of solutions to a given Sudoku puzzle. The solve(Sudoku p) method calls on the printPuz(Sudoku a) method to print all solutions to a given sudoku puzzle, if applicable. The printPuz(Sudoku a) method also prints the total number of calls to the recursive solve(Sudoku p) method needed to generate each solution.  
