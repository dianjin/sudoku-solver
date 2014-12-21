#include <stdlib.h>
#include <stdio.h>
#include <time.h>



typedef struct {
    unsigned long long grid[9];
    unsigned short row[9];
    unsigned short col[9];
    unsigned short box[9];
    unsigned char pos;
} Sudoku;

int numCalls = 0;
int const puzSize = sizeof(Sudoku);
long long const fifteen = 15;

long long setValue(long long storage, short index, long long value) {
    index = index << 2;
    value = value << index;
    return (storage & (~(fifteen << index))) | value;
}

short getValue(long long storage, long long index) {
    index = index << 2;
    return (storage & (fifteen << index)) >> index;
}

Sudoku updateSudoku(Sudoku puzzle, char r, char c, short val) {
    // Update actual sudoku
    puzzle.grid[r] = setValue(puzzle.grid[r], c, val);

    // Update valid rows, cols, and boxes
    short one = 1 << (val-1);
    puzzle.row[r] = puzzle.row[r] | one;
    puzzle.col[c] = puzzle.col[c] | one;
    puzzle.box[(c/3) + 3*(r/3)] = puzzle.box[(c/3) + 3*(r/3)] | one;
    puzzle.pos = r << 4 | c;
    //printf("row: %d %d col: %d %d pos: %d\n", r, puzzle.pos >> 4, c, puzzle.pos & 15, puzzle.pos);
    return puzzle;
}


Sudoku initSudoku(short puzzle[9][9]) {
    Sudoku mySudoku;
    char r, c;
    for (r = 0; r < 9; r++) {
        mySudoku.row[r] = 0;
        mySudoku.col[r] = 0;
        mySudoku.box[r] = 0;
    }
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            mySudoku = updateSudoku(mySudoku, r, c, puzzle[r][c]);
        }
    }
    mySudoku.pos = 0;
    return mySudoku;
}


void printSudoku(Sudoku myPuzzle) {
    char r,c;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            printf("%d  ", getValue(myPuzzle.grid[r], c));
        }
        printf("\n\n");
    }
    printf("\n");
}

int main(void) {

    clock_t begin, end;
    double time_spent;

    begin = clock();

    short myPuz[9][9] = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

    //short myPuz[9][9] = {{0,9,3,0,5,0,0,0,4}, {0,0,7,0,0,0,0,8,0}, {5,6,0,9,0,0,0,0,7}, {0,8,0,0,3,9,4,2,0}, {0,4,0,8,2,7,0,3,0}, {0,3,5,6,1,0,0,9,0}, {9,0,0,0,0,5,0,4,2}, {0,7,0,0,0,0,1,0,0}, {3,0,0,0,4,0,8,7,0}};

    //short myPuz[9][9] = {{0,0,8,0,0,1,7,0,0}, {0,3,0,0,6,4,0,0,9}, {2,0,0,3,0,0,0,0,0}, {0,0,5,0,0,0,6,0,0}, {0,0,2,8,4,6,5,0,0}, {0,0,1,0,0,0,9,0,0}, {0,0,0,0,0,9,0,0,2}, {7,0,0,4,5,0,0,9,0}, {0,0,9,7,0,0,4,0,0}};

    Sudoku myPuzzle = initSudoku(myPuz);
    solve(myPuzzle);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n\nElapsed: %g seconds\n", time_spent);

    return 0;

}

void solve(Sudoku puzzle) {
    if (numCalls == 100000000) {
        return;
    }
    numCalls++;
    int poop;
    short valids;
    char r, c, i;
    short one = 1;
    r = puzzle.pos >> 4;
    c = puzzle.pos & 15;
    while (r < 9) {
        while (c < 9) {
            if (!getValue(puzzle.grid[r], c)) {
                valids = ((~(puzzle.row[r] | puzzle.col[c] | puzzle.box[(c/3) + 3*(r/3)])));
                    one = 1;
                    for (i = 1; i <= 9; i++) {
                        if (one & valids) {
                            Sudoku newPuzzle;
                            newPuzzle = puzzle;
                            newPuzzle = updateSudoku(newPuzzle, r, c, i);
                            solve(newPuzzle);

                        }
                        one = one << 1;
                    }
                    return;
            }
            c++;
        }
        c = 0;
        r++;
    }
    //printSudoku(puzzle);
}
