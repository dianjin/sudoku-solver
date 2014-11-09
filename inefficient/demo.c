// Sudoku Solver - Demo Version
// Date: July 25, 2014
// Developer: Dian Jin
// Github: http://github.com/dianjin
//
// This is Sudoku Solver - Demo Version
// The Demo version has a very bare-bones user interface.
// The Demo version has extra features and is intended for demonstrations, rather than actual customization or tinkering.
// It is much easier to modify or customize Sudoku Solver - Hack Version.
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
Sudoku *puzToSolve; // This points to the puzzle that is ultimately passed into the solve(Sudoku p) method.

// Sample Sudokus
Sudoku sampleEasy = {{0,9,3,0,5,0,0,0,4}, {0,0,7,0,0,0,0,8,0}, {5,6,0,9,0,0,0,0,7}, {0,8,0,0,3,9,4,2,0}, {0,4,0,8,2,7,0,3,0}, {0,3,5,6,1,0,0,9,0}, {9,0,0,0,0,5,0,4,2}, {0,7,0,0,0,0,1,0,0}, {3,0,0,0,4,0,8,7,0}};
Sudoku sampleHard = {{0,0,0,0,0,0,3,0,0}, {8,0,0,1,0,3,0,0,9}, {7,0,0,0,6,0,0,0,0}, {2,0,5,9,0,0,0,3,0}, {0,6,0,8,0,1,0,5,0}, {0,1,0,0,7,5,9,0,6}, {0,0,0,0,8,0,0,0,3}, {1,0,0,3,0,9,0,0,2}, {0,0,7,0,0,0,0,0,0}};
Sudoku sampleVeryHard = {{8,0,0,0,0,0,0,0,0}, {0,0,3,6,0,0,0,0,0}, {0,7,0,0,9,0,2,0,0}, {0,5,0,0,0,7,0,0,0}, {0,0,0,0,4,5,7,0,0}, {0,0,0,1,0,0,0,3,0}, {0,0,1,0,0,0,0,6,8}, {0,0,8,5,0,0,0,1,0}, {0,9,0,0,0,0,4,0,0}};
Sudoku sampleMultipleSolutions = {{0,0,8,0,0,1,7,0,0}, {0,3,0,0,6,4,0,0,9}, {2,0,0,3,0,0,0,0,0}, {0,0,5,0,0,0,6,0,0}, {0,0,2,8,4,6,5,0,0}, {0,0,1,0,0,0,9,0,0}, {0,0,0,0,0,9,0,0,2}, {7,0,0,4,5,0,0,9,0}, {0,0,9,7,0,0,4,0,0}};
Sudoku sampleNoSolutions = {{8,0,0,0,0,0,0,0,0}, {0,0,3,6,0,0,0,0,0}, {0,7,0,0,9,0,2,0,0}, {0,5,0,0,0,0,7,0,0}, {0,0,0,0,4,5,7,0,0}, {0,0,0,1,0,0,0,3,0}, {0,0,1,0,0,0,0,6,8}, {0,0,8,5,0,0,0,1,0}, {0,9,0,0,0,0,4,0,0}};
Sudoku sampleAllSolutions = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}};

void main() {
    numSolvable = &numSols;
    printf("\n Sudoku Solver (Demo)\n\n");
    int done = 0;
    while (done != 1) {
        prompt();
    }
}

void prompt() {
        int input;
        numCalls = 0;
        numSols = 0;
        printf(" --------------------------------------------------\n\n");
        printf("\t<1> Solve a sample puzzle\n");
        printf("\t<2> Solve puzzle from txt file\n");
        printf("\t<3> Generate all possible sudoku solutions\n");
        printf("\n >> Pick a numeric option: ");
        scanf("%d", &input);
        switch(input) {
            case 1:
                choosePuz();
                break;
            case 2:
                readFile();
                break;
            case 3:
                solve(sampleAllSolutions);
                break;
            default:
                printf("\n  Invalid input, try again. \n\n");
                break;
        }
}

void choosePuz() {
    printf("\n");
    int numPuz;
    printf("\t\t<1> Easy\n");
    printf("\t\t<2> Hard\n");
    printf("\t\t<3> Very hard\n");
    printf("\t\t<4> Multiple solutions\n");
    printf("\t\t<5> No solutions\n");
    printf("\n >> Pick a sudoku to solve: ");
    scanf("%d", &numPuz);
    switch (numPuz) {
        case 1:
            puzToSolve = &sampleEasy;
            break;
        case 2:
            puzToSolve = &sampleHard;
            break;
        case 3:
            puzToSolve = &sampleVeryHard;
            break;
        case 4:
            puzToSolve = &sampleMultipleSolutions;
            break;
        case 5:
            puzToSolve = &sampleNoSolutions;
            break;
        default:
            printf("\n Invalid input, try again. \n\n");
            return;
            break;
    }

    int n = solve(puzToSolve);
    if (n == 0) {
        printf("\n NO SOLUTION \n\n");
    }
}

void readFile() {
    printf("\n Importing puzzle from puzzles.txt...\n");
    Sudoku readPuz;
    int index = 0;
    int numRow, numCol;
    char c;
    FILE *file;
    file = fopen("puzzles.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF && index<=81) {
            numCol = (index % 9);
            numRow = index / 9;
                if (c == '.') {
                c = '0';
                }
            readPuz[numRow][numCol] = c - '0';
            index++;
        }
        fclose(file);
    }
    int n = solve(readPuz);
    if (n == 0) {
        printf(" \n NO SOLUTIONS \n\n");
    }
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
    printPuz(p); // Print the solution.
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
