// Sudoku Solver - Hack Version
// Date: July 25, 2014
// Developer: Dian Jin
// Github: http://github.com/dianjin
//
// This is Sudoku Solver - Hack Version.
// The Hack version does not have a user interface.
// The Hack version is meant for customization and tinkering, and does not have any of the extra features included in the Demo version.
// The Hack version is only able to solve one sudoku per excecution, making the excecution time representative of the time needed to solve a given sudoku.
// It is much easier to demonstrate the algorithm using Sudoku Solver - Demo Version.
//
//        ***********************************************************
//        * VIEW THE main() METHOD TO INPUT YOUR OWN SUDOKU PUZZLE. *
//        ***********************************************************
//
// This is a backtracking recursive sudoku solver written in C.
// The final outcome of the solve(Sudoku p) method is as follows:
//      1) If the given sudoku is solvable:
//          - Returns an int representing the number of solutions for the given puzzle
//          - Prints out all possible solutions
//      2) If the given sudoku is NOT solvable:
//          - Returns the int 0, as there are zero possible solutions for the given puzzle
//          - Does NOT print anything, unless it is instructed to after the solve(Sudoku p) method is call
//

#include <stdio.h>
#include <stdlib.h>

// Ints
int const puzSize = sizeof(int) * 81; // This is the size of each sudoku puzzle.
int numCalls = 0; // This keeps track of the number of recursive calls made to solve(Sudoku p). It is reset in the prompt() method.
int numSols = 0; // This keeps track of the number of solutions to a given puzzle. It is reset in the prompt() method.
int *numSolvable; // This points to numSols.

// Sudokus
typedef int Sudoku[9][9]; // Define Sudoku as a 2D int array of size 9,9. Empty cells are represented by the int 0.

void main() {
    numSolvable = &numSols;

    // Below are a number of Sudoku puzzles taken from Sudoku #2 by Playmore Publishing Group.
    // To give the program a Sudoku to solve, simply declare myPuz using the format given in the following sample puzzles.

    // EASY
    //Sudoku myPuz = {{0,9,3,0,5,0,0,0,4}, {0,0,7,0,0,0,0,8,0}, {5,6,0,9,0,0,0,0,7}, {0,8,0,0,3,9,4,2,0}, {0,4,0,8,2,7,0,3,0}, {0,3,5,6,1,0,0,9,0}, {9,0,0,0,0,5,0,4,2}, {0,7,0,0,0,0,1,0,0}, {3,0,0,0,4,0,8,7,0}};
    //Sudoku myPuz = {{0,9,0,0,7,0,6,0,1}, {6,0,7,1,0,2,0,0,0}, {0,8,3,0,0,0,0,7,0}, {9,0,8,4,0,6,0,0,3}, {7,4,0,3,0,9,0,1,6}, {3,0,0,7,0,5,4,0,9}, {0,7,0,0,0,0,1,4,0}, {0,0,0,2,0,1,5,0,7}, {2,0,4,0,5,0,0,6,0}};
    //Sudoku myPuz = {{0,0,0,6,4,9,1,5,0}, {0,3,9,0,5,0,0,0,0}, {6,5,0,3,2,0,0,7,0}, {3,0,7,4,0,6,0,2,0}, {2,0,0,0,0,0,0,0,9}, {0,9,0,5,0,2,4,0,7}, {0,7,0,0,6,4,0,8,1}, {0,0,0,0,7,0,3,4,0}, {0,8,4,2,3,5,0,0,0}};

    // INTERMEDIATE
    //Sudoku myPuz = {{5,7,0,0,0,0,0,0,0}, {0,0,1,0,0,8,0,7,3}, {0,3,2,7,0,6,1,8,0}, {0,0,0,1,0,0,0,4,0}, {0,0,0,6,2,9,0,0,0}, {0,6,0,0,0,0,0,0,0}, {0,8,7,9,0,5,4,2,0}, {4,5,0,8,0,0,7,0,0}, {0,0,0,0,0,0,0,1,8}};
    //Sudoku myPuz = {{4,9,0,0,0,0,0,0,0}, {0,2,7,0,0,8,0,0,0}, {0,6,0,0,2,5,0,0,0}, {2,0,0,7,6,0,0,9,1}, {0,0,0,0,0,0,0,0,0}, {1,8,0,0,5,4,0,0,7}, {0,0,0,9,7,0,0,1,0}, {0,0,0,8,0,0,5,4,0}, {0,0,0,0,0,0,0,6,3}};
    //Sudoku myPuz = {{8,0,0,0,5,7,4,9,0}, {6,0,0,4,0,0,2,0,5}, {5,0,0,0,0,0,0,0,0}, {0,0,8,0,3,0,0,0,0}, {7,0,2,0,0,0,3,0,9}, {0,0,0,0,4,0,6,0,0}, {0,0,0,0,0,0,0,0,6}, {9,0,6,0,0,5,0,0,1}, {0,7,3,9,1,0,0,0,2}};

    // CHALLENGING
    //Sudoku myPuz = {{0,0,0,0,6,0,8,7,5}, {0,2,0,0,3,0,0,0,0}, {0,8,0,9,0,0,3,6,0}, {2,0,0,0,0,0,0,5,0}, {5,0,0,7,0,1,0,0,6}, {0,7,0,0,0,0,0,0,9}, {0,9,2,0,0,3,0,8,0}, {0,0,0,0,2,0,0,4,0}, {7,5,1,0,8,0,0,0,0}};
    //Sudoku myPuz = {{0,4,0,0,9,0,6,0,0}, {0,9,0,0,0,0,0,3,0}, {0,0,0,3,0,8,0,0,1}, {0,6,0,0,5,4,0,0,8}, {0,0,0,0,0,0,0,0,0}, {8,0,0,6,3,0,0,5,0}, {2,0,0,9,0,7,0,0,0}, {0,7,0,0,0,0,0,9,0}, {0,0,5,0,1,0,0,4,0}};
    //Sudoku myPuz = {{0,7,0,0,0,8,0,3,6}, {0,0,0,0,4,3,0,0,0}, {6,0,0,0,0,7,0,2,0}, {0,0,3,8,0,0,0,5,4}, {0,0,8,0,0,0,7,0,0}, {1,2,0,0,0,6,9,0,0}, {0,1,0,9,0,0,0,0,7}, {0,0,0,7,2,0,0,0,0}, {2,8,0,3,0,0,0,0,0}};

    // TOUGH
    //Sudoku myPuz = {{0,0,0,0,0,0,3,0,0}, {8,0,0,1,0,3,0,0,9}, {7,0,0,0,6,0,0,0,0}, {2,0,5,9,0,0,0,3,0}, {0,6,0,8,0,1,0,5,0}, {0,1,0,0,7,5,9,0,6}, {0,0,0,0,8,0,0,0,3}, {1,0,0,3,0,9,0,0,2}, {0,0,7,0,0,0,0,0,0}};
    //Sudoku myPuz = {{9,0,0,0,0,6,0,0,8}, {5,0,0,4,1,0,7,0,9}, {8,7,0,0,3,0,0,0,0}, {0,0,0,0,0,4,0,0,0}, {0,5,0,0,8,0,0,4,0}, {0,0,9,3,0,0,0,0,0}, {0,0,0,0,4,0,0,5,7}, {6,0,4,0,7,9,0,0,1}, {7,0,0,2,0,0,0,0,4}};
    //Sudoku myPuz = {{5,0,7,0,1,4,0,0,0}, {0,6,0,0,0,0,0,3,0}, {0,1,0,0,2,0,8,0,0}, {0,0,0,0,0,9,4,6,0}, {9,0,0,0,0,0,0,0,7}, {0,4,5,6,0,0,0,0,0}, {0,0,2,0,9,0,0,4,0}, {0,5,0,0,0,0,0,1,0}, {0,0,0,5,8,0,7,0,6}};

    // SUPER TOUGH
    //Sudoku myPuz = {{4,8,7,0,0,0,0,0,6}, {0,0,0,0,3,0,0,8,1}, {0,0,0,0,0,5,7,0,0}, {3,0,0,6,4,0,0,0,5}, {0,6,0,0,0,0,0,7,0}, {9,0,0,0,2,7,0,0,4}, {0,0,3,9,0,0,0,0,0}, {7,2,0,0,1,0,0,0,0}, {1,0,0,0,0,0,3,9,0}};
    //Sudoku myPuz = {{0,0,0,0,0,0,0,1,5}, {5,0,0,9,0,1,4,0,0}, {0,0,0,0,5,2,0,6,0}, {8,9,0,0,2,0,3,5,0}, {0,0,5,0,1,0,8,0,0}, {0,3,1,0,8,0,0,2,9}, {0,7,0,8,4,0,0,0,0}, {0,0,0,2,0,3,0,0,4}, {2,8,0,0,0,0,0,0,0}};
    //Sudoku myPuz = {{5,0,8,0,0,1,7,0,0}, {0,3,0,0,6,4,0,0,9}, {2,0,0,3,0,0,0,0,0}, {0,0,5,0,0,0,6,0,0}, {0,0,2,8,4,6,5,0,0}, {0,0,1,0,0,0,9,0,0}, {0,0,0,0,0,9,0,0,2}, {7,0,0,4,5,0,0,9,0}, {0,0,9,7,0,0,4,0,0}};

    // ALLEGEDLY ONE OF THE HARDEST SO FAR
    // From http://www.telegraph.co.uk/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html
    // Published by Arto Inkala
    //Sudoku myPuz = {{8,0,0,0,0,0,0,0,0}, {0,0,3,6,0,0,0,0,0}, {0,7,0,0,9,0,2,0,0}, {0,5,0,0,0,7,0,0,0}, {0,0,0,0,4,5,7,0,0}, {0,0,0,1,0,0,0,3,0}, {0,0,1,0,0,0,0,6,8}, {0,0,8,5,0,0,0,1,0}, {0,9,0,0,0,0,4,0,0}};

    // THIS ONE HAS TWO SOLUTIONS
    // From http://sandwalk.blogspot.ca/2007/06/i-knew-it-there-can-be-more-than-one.html
    //Sudoku myPuz = {{9,0,6,0,7,0,4,0,3}, {0,0,0,4,0,0,2,0,0}, {0,7,0,0,2,3,0,1,0}, {5,0,0,0,0,0,1,0,0}, {0,4,0,2,0,8,0,6,0}, {0,0,3,0,0,0,0,0,5}, {0,3,0,7,0,0,0,5,0}, {0,0,7,0,0,5,0,0,0}, {4,0,5,0,1,0,7,0,8}};

    // THIS ONE HAS SIX SOLUTIONS
    // Modified version of Super Tough #3.
    //Sudoku myPuz = {{0,0,8,0,0,1,7,0,0}, {0,3,0,0,6,4,0,0,9}, {2,0,0,3,0,0,0,0,0}, {0,0,5,0,0,0,6,0,0}, {0,0,2,8,4,6,5,0,0}, {0,0,1,0,0,0,9,0,0}, {0,0,0,0,0,9,0,0,2}, {7,0,0,4,5,0,0,9,0}, {0,0,9,7,0,0,4,0,0}};

    // THIS ONE IS UNSOLVABLE
    // It's basically a small modiciation of the "allegedly one of the hardest so far" puzzle.
    //Sudoku myPuz = {{8,0,0,0,0,0,0,0,0}, {0,0,3,6,0,0,0,0,0}, {0,7,0,0,9,0,2,0,0}, {0,5,0,0,0,0,7,0,0}, {0,0,0,0,4,5,7,0,0}, {0,0,0,1,0,0,0,3,0}, {0,0,1,0,0,0,0,6,8}, {0,0,8,5,0,0,0,1,0}, {0,9,0,0,0,0,4,0,0}}

    Sudoku myPuz = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

    int n = solve(myPuz); // int n represents the number of possible solutions to myPuz.
    if (n == 0) {
        printf("No possible solutions.");
    }

    // If you want to solve two sudoku puzzles in one excecution, reset numSols and numCols to 0 every time before you call solve().
}

// Determines if n is a valid entry for the given puzzle(p[][9]), row(r), and column(c).
// If n is valid, return 1.
// If n is invalid, return 0.
int isValid(Sudoku p, int n, int r, int c) {

    int lbr, lbc, k; // lbr and lbc are used to see if n already exists in the cell's corresponding box.
    lbr = r - r%3; // The box's row starts at lbr.
    lbc = c - c%3; // The box's column starts at lbc.

    // This loop determines is n already exists in the cell's corresponding row and column.
    // If so, return 0.
    for (k = 0; k < 9; k++) {
        if (p[r][k] == n || p[k][c] == n) {
            return 0;
        }
    }

    // This loop determines if n already exists in the cell's corresponding box.
    // If so, return 0.
    for (r = lbr; r < lbr+3; r++) { // Notice the use of lbr here.
        for (c = lbc; c < lbc+3; c++) { // Notice the use of lbc here.
            if (p[r][c] == n) {
                return 0;
            }
        }
    }

    // If none of the previous loops have returned 0, n must be a valid entry for the given puzzle, row, and column.
    // Therefore return 1.
    return 1;

}

// This is the recursive method used to solve the sudoku.
// For easier puzzles, it is called a few hundred times.
// For harder puzzles, it is called a few ten thousand times.
int solve(Sudoku p) {
    if (numCalls == 100000000) {
        return;
    }
    int r, c, i; // Used in the loop.
    numCalls++; // Keeps track of how many times the solve method is called.

    // Loops through the entire puzzle, looking for empty spaces (represented by 0) to fill.
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            if (p[r][c] == 0) {
                // The next loop fills an empty cell with valid entries in ascending order.
                // The algorithm first inserts the smallest valid value into the empty cell.
                // If that value eventually leads to a cell with NO valid values down the road, the algorithm "backtracks".
                // "Backtracking" means the algorithm returns to a previous state of the puzzle and continues to _
                // input and "test" different valid values for a given cell to find solutions to the Sudoku puzzle.
                for (i = 1; i <= 9; i++) {
                    if (isValid(p, i, r, c) == 1) {
                        // Computer creates a new Sudoku, newPuz, on which to call the solve method.
                        Sudoku newPuz;
                        memcpy(newPuz, p, puzSize);
                        newPuz[r][c] = i; // The valid value being tested is inserted in its proper location in newPuz.
                        solve(newPuz); // The computer tries to solve newPuz.
                    }
                }
                return *numSolvable; // This returns the number of the solutions to a given puzzle.
            }
        }
    }
    //printPuz(p); // Print the solution.
    numSols++; // Increment numSols to indicate another solution has been found.

}

// Prints any Sudoku
void printPuz(Sudoku a) {
    printf("\n");
    printf(" SOLUTION %d:\n", numSols+1);
    // Super simple loop to print a solved puzzle and the number of recursive calls needed to solve the puzzle.
    printf("\n");
    int r, c;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            printf(" %d ", a[r][c]);
        }
        printf("\n\n");
    }
    printf(" Total recursive calls: %d\n\n", numCalls);
}
