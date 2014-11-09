#include <stdlib.h>
#include <stdio.h>
#include <time.h>



typedef struct {
    long long grid[9];
    short row[9];
    short col[9];
    short box[9];
} Sudoku;

int numCalls = 0;
int const puzSize = sizeof(Sudoku);

long long setValue(long long storage, short index, long long value) {
    long long fifteen = 15;
    index = index << 2;
    fifteen = fifteen << index;
    value = value << index;
    return (storage & (~fifteen)) | value;
}

short getValue(long long storage, long long index) {
    long long fifteen = 15;
    index = index << 2;
    fifteen = fifteen << index;
    return (storage & fifteen) >> index;
}

Sudoku* initSudoku(short puzzle[9][9]) {
    Sudoku *mySudoku = (Sudoku*) malloc(puzSize);
    short r, c;
    for (r = 0; r < 9; r++) {
        mySudoku->row[r] = 0;
        mySudoku->col[r] = 0;
        mySudoku->box[r] = 0;
    }
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            updateSudoku(mySudoku, r, c, puzzle[r][c]);
        }
    }
    return mySudoku;
}

void updateSudoku(Sudoku *puzzle, short r, short c, short val) {
    // Update actual sudoku
    puzzle->grid[r] = setValue(puzzle->grid[r], c, val);

    // Update valid rows, cols, and boxes
    short one = 1 << (val-1);
    puzzle->row[r] = puzzle->row[r] | one;
    puzzle->col[c] = puzzle->col[c] | one;
    puzzle->box[(c/3) + 3*(r/3)] = puzzle->box[(c/3) + 3*(r/3)] | one;

}

void printSudoku(Sudoku *myPuzzle) {
    short r,c;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            printf("%d  ", getValue(myPuzzle->grid[r], c));
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
    Sudoku *myPointer = initSudoku(myPuz);
    solve(myPointer);

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n\nElapsed: %g seconds\n", time_spent);

    return 0;

}

void solve(Sudoku *puzzle) {
    if (numCalls == 1000000) {
        return;
    }
    // to traverse a col, just bitshift
    numCalls++;

    short valids;
    int r, c, i;
    short one = 1;
    short ninebits = 511;
    int dummy;
//    if (numCalls == 194) {
//        printSudoku(puzzle);
//        scanf("%d", &dummy);
//    }
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            //printf("value: %d\n", !getValue(puzzle->grid[r], c));
            //printf("row: %d, col: %d\n", r,c );
            if (!getValue(puzzle->grid[r], c)) { // if gric[r][c] is empty
                //printf("found an empty cell");
                //printf("row: %d, col: %d, box number: %d\n", r,c,(c/3) + 3*(r/3) );
                valids = ((~(puzzle->row[r] | puzzle->col[c] | puzzle->box[(c/3) + 3*(r/3)])) & ninebits);
                //printf("valids: %d\n", valids);
                //if (valids) { // if there are possible valid entries for this cell
                    one = 1;
                    for (i = 1; i <= 9; i++) {
                        //printf("is %d valid?: %d\n", i, one & valids);
                        if (one & valids) {
                            Sudoku *newPuzzle = (Sudoku*) malloc(puzSize);
                            memcpy(newPuzzle, puzzle, puzSize);
                            //printf("row: %d col: %d value: %d\n", r,c,i);
                            updateSudoku(newPuzzle, r, c, i);
                            //printSudoku(newPuzzle);
                            //scanf("%d", &dummy);
                            //printSudoku(newPuzzle);
                            solve(newPuzzle);

                        }
                        one = one << 1;
                    }
                    //printf("exit cuz THERES NO POSSIBLE VALSSSS\n");
                    free(puzzle);
                    return;
                //}
            }
        }
    }
    //printSudoku(puzzle);
}
