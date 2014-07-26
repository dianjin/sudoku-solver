sudoku-solver
=============

A recursive backtracking sudoku solver written in C.

<h3>Files included</h3>
<ul>
<li>demo.c - This is the Demo version. Meant for demonstration purposes, as it comes with a very basic user interface.
<li>hack.c - This is the Hack version. Meant for tinkering and customization, as it doesn't come with a user interface or any other frills. 
</ul>

<h3>Algorithm input and output</h3>
(This applies to both the Demo and Hack versions, since they use the same algorithm.)<br>
Input: a 9x9 array of ints representing the sudoku puzzle to be solved. Empty cells are denoted by zeroes.<br>
Output: Returns an int representing the number of solutions to the given Sudoku puzzle. Prints all solutions to given puzzle, if there are any. Prints the number of calls to the recursive solve(Sudoku p) method needed to generate each solution.

<h3>How the algorithm works</h3>
The main algorithm in this particular sudoku solver is the recursive solve(Sudoku p) method. The solving begins when the solve(Sudoku p) method is called on a 9x9 array of ints representing the sudoku puzzle that is to be solved. (Sudoku is typedef'd as int[9][9].) Every time solve(Sudoku p) is called, the algo inputs a valid number into the next cell of the Sudoku grid and calls the solve(Sudoku p) method on that resulting Sudoku grid. The algo "backtracks" when it reaches a point at which there are no valid numbers for a particular cell. At that point, the algo swaps its previous cell entry for a different valid value and continues filling in the grid as described. At the end of the day, the algo will have found every possible solution to a given puzzle, since the program ultimately inputs and thereby tests ALL valid values for a particular cell. Read the comments in the code for line-by-line explanations.

<h3>Useful tips</h3>
<ul>
<li>This algo generates every possible Sudoku solution (there are 6.671*10^21) when you call the solve(Sudoku p) method on a 9x9 array of zeroes. Obviously, your computer won't be able to complete this operation since it could take decades.
<li>The Hack version is only meant to solve one Sudoku puzzle per excecution. It is possible to call the solve(Sudoku p) method on multiple different Sudoku puzzles in one excecution, but you'd have to reset numSols and numCalls to 0 to prevent any wonky outputs in the console.
<li>To solve your own Sudoku puzzle, I'd recommend running the Hack version. You just need to swap Sudoku myPuz in the main() method for your own Sudoku puzzle.
<li>This algo definitely isn't the most efficient recursive backtracking Sudoku Solver, but it does its job and is a good starting point for further tinkering.
</ul>
