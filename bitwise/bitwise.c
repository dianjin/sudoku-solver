#include <stdio.h>
#include <time.h>

const short shortshift[10] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256};
int numCalls = 0;

typedef struct {
    unsigned char grid[9][9]; // This represents the 9x9 Sudoku grid. Char values range from 0 to 9. An empty cell is represented by 0.
    unsigned short row[9]; // This short represents the values that have been used in a given row. Only bitwise operations are applied to this variable.
    unsigned short col[9]; // This short represents the values that have been used in a given column. Only bitwise operations are applied to this variable.
    unsigned short box[9]; // This short represents the values that have been used in a given box (or square). Only bitwise operations are applied to this variable.
    unsigned char pos; // This char represents the position of the last filled cell. The first 4 and last 4 bits represent the row and column of the last filled cell respectively.
} Sudoku;

Sudoku initSudoku(char puzzle[9][9]) {
    // Initializes the Sudoku struct given a puzzle as represented by a 2D array of chars.
    Sudoku mySudoku = {.row = {0}, .col = {0}, .box = {0}};
    char r, c;
    char val;
    short one;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            // This block is also used in the solve function. The explanation is there too.
            val = puzzle[r][c];
            one = shortshift[val];
            mySudoku.grid[r][c] = val;
            mySudoku.row[r] |= one;
            mySudoku.col[c] |= one;
            mySudoku.box[(c/3) + 3*(r/3)] |= one;
        }
    }
    mySudoku.pos = 0;
    return mySudoku;
}

void printSudoku(Sudoku myPuzzle) {
    // Prints the sudoku.
    char r,c;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            printf("%d  ", myPuzzle.grid[r][c]);
        }
        printf("\n\n");
    }
    printf("\n");
}

int main(void) {

    // SAMPLE PUZZLES
    // Just uncomment the puzzle you want to test, or write in your own.

    // This relatively difficult puzzle was written by Arto Inkala.
    char myPuz[9][9] = {{8,5,0,0,0,2,4,0,0}, {7,2,0,0,0,0,0,0,9},{0,0,4,0,0,0,0,0,0},{0,0,0,1,0,7,0,0,2},{3,0,5,0,0,0,9,0,0},{0,4,0,0,0,0,0,0,0},{0,0,0,0,8,0,0,7,0},{0,1,7,0,0,0,0,0,0},{0,0,0,0,3,6,0,4,0}};

    // This is a completely empty grid, so the program can theoretically generate all possible sudoku solutions ever. Used to compare runtimes between different solving algos.
    // char myPuz[9][9] = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

    // Super easy sudoku
    // char myPuz[9][9] = {{0,9,3,0,5,0,0,0,4}, {0,0,7,0,0,0,0,8,0}, {5,6,0,9,0,0,0,0,7}, {0,8,0,0,3,9,4,2,0}, {0,4,0,8,2,7,0,3,0}, {0,3,5,6,1,0,0,9,0}, {9,0,0,0,0,5,0,4,2}, {0,7,0,0,0,0,1,0,0}, {3,0,0,0,4,0,8,7,0}};

    // This sudoku has multiple solutions. The program will print all of them.
    // char myPuz[9][9] = {{0,0,8,0,0,1,7,0,0}, {0,3,0,0,6,4,0,0,9}, {2,0,0,3,0,0,0,0,0}, {0,0,5,0,0,0,6,0,0}, {0,0,2,8,4,6,5,0,0}, {0,0,1,0,0,0,9,0,0}, {0,0,0,0,0,9,0,0,2}, {7,0,0,4,5,0,0,9,0}, {0,0,9,7,0,0,4,0,0}};

    clock_t begin, end;
    double time_spent;
    begin = clock();

    // Timer starts here

    Sudoku myPuzzle = initSudoku(myPuz);
    solve(myPuzzle);

    // Timer ends here

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\nElapsed: %g seconds\n", time_spent);

    return 0;

}

void solve(Sudoku puzzle) {
    short one, valids;
    char r, c, val;

    // To prevent an infinite loop if you try to solve an empty grid.
    if (numCalls == 100000000) {
        return;
    }
    numCalls++;

    // puzzle.pos indicates the location of the last filled cell. The program will search for empty cells from that location onward.
    r = puzzle.pos >> 4;
    c = puzzle.pos & 15;

    // The loop that iterates traverses the grid
    while (r < 9) {
        while (c < 9) {
            if (!puzzle.grid[r][c]) { // If the cell is empty:
                valids = ~(puzzle.row[r] | puzzle.col[c] | puzzle.box[(c/3) + 3*(r/3)]); // Compute valid entries for that empty cell.
                for (val = 1; val <= 9; val++) { // Iterates through the valid entries for that cell in ascending order.
                    one = shortshift[val];
                    if (one & valids) {
                        // Creates a new Sudoku struct, newPuzzle, by copying the current Sudoku struct into newPuzzle.
                        Sudoku newPuzzle;
                        newPuzzle = puzzle;
                        // Updates newPuzzle to reflect the insertion of a new value into the empty cell.
                        newPuzzle.grid[r][c] = val; // Insert the new value into the empty cell.
                        newPuzzle.row[r] |= one; // That value is no longer available for that given row.
                        newPuzzle.col[c] |= one; // That value is no longer available for that given column.
                        newPuzzle.box[(c/3) + 3*(r/3)] |= one; // That value is no longer available for that given box.
                        newPuzzle.pos = r << 4 | c; // Update the position char to reflect the location of the last filled cell.
                        // Recursive call to the solve function.
                        solve(newPuzzle);

                    }
                }
                return; // This happens when there are no valid entries for a given cell, causing the program to "backtrack".
            }
            c++;
        }
        c = 0;
        r++;
    }
    printSudoku(puzzle); // Prints the solution(s) to the puzzle as soon it's found.

}
