#include <stdio.h>
#include <time.h>

const short shortshift[10] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256};
int numCalls = 0;

typedef struct {
    unsigned char grid[9][9];
    unsigned short row[9];
    unsigned short col[9];
    unsigned short box[9];
    unsigned char pos;
} Sudoku;

Sudoku initSudoku(short puzzle[9][9]) {
    Sudoku mySudoku = {.row = {0}, .col = {0}, .box = {0}};
    char r, c;
    char val;
    short one;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
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

    //short myPuz[9][9] = {{0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

    short myPuz[9][9] = {{0,9,3,0,5,0,0,0,4}, {0,0,7,0,0,0,0,8,0}, {5,6,0,9,0,0,0,0,7}, {0,8,0,0,3,9,4,2,0}, {0,4,0,8,2,7,0,3,0}, {0,3,5,6,1,0,0,9,0}, {9,0,0,0,0,5,0,4,2}, {0,7,0,0,0,0,1,0,0}, {3,0,0,0,4,0,8,7,0}};

    //short myPuz[9][9] = {{0,0,8,0,0,1,7,0,0}, {0,3,0,0,6,4,0,0,9}, {2,0,0,3,0,0,0,0,0}, {0,0,5,0,0,0,6,0,0}, {0,0,2,8,4,6,5,0,0}, {0,0,1,0,0,0,9,0,0}, {0,0,0,0,0,9,0,0,2}, {7,0,0,4,5,0,0,9,0}, {0,0,9,7,0,0,4,0,0}};

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
    if (numCalls == 100000000) {
        return;
    }
    numCalls++;
    short one, valids;
    char r, c, val;
    r = puzzle.pos >> 4;
    c = puzzle.pos & 15;

    while (r < 9) {
        while (c < 9) {
            if (!puzzle.grid[r][c]) {
                valids = ~(puzzle.row[r] | puzzle.col[c] | puzzle.box[(c/3) + 3*(r/3)]);
                for (val = 1; val <= 9; val++) {
                    one = shortshift[val];
                    if (one & valids) {

                        Sudoku newPuzzle;
                        newPuzzle = puzzle;

                        newPuzzle.grid[r][c] = val;
                        newPuzzle.row[r] |= one;
                        newPuzzle.col[c] |= one;
                        newPuzzle.box[(c/3) + 3*(r/3)] |= one;
                        newPuzzle.pos = r << 4 | c;

                        solve(newPuzzle);

                    }
                }
                return;
            }
            c++;
        }
        c = 0;
        r++;
    }
    printSudoku(puzzle);

}
