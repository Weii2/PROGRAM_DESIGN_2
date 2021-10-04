#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int FindEmpty(int sudoku[][9], int &row, int &col) {
    for(row=0; row<9; row++)
        for(col=0; col<9; col++)
            if(sudoku[row][col] == 0)
                return 1;
    return 0;
}

int Unused(int sudoku[][9], int row, int col, int test) {
    for(int col_num=0; col_num<9; col_num++)    //for row
        if(sudoku[row][col_num] == test)
            return 0;
    for(int row_num=0; row_num<9; row_num++)    //for col
        if(sudoku[row_num][col] == test)
            return 0;
    for(int col_num=0; col_num<3; col_num++)    //for 3*3 box
        for(int row_num=0; row_num<3; row_num++)
            if(sudoku[3*(int)(row/3)+row_num][3*(int)(col/3)+col_num] == test)
                return 0;
    return 1;
}

int Generate(int sudoku[][9]) {
    srand((unsigned) time(NULL));
    rand();
    int row, col, test, repeat[10];

    if(FindEmpty(sudoku, row, col) == 0) {
        return 1;
    }

    for(int i=0; i<10; i++)
        repeat[i]=0;
    for(int i=1; i<=9; i++) {
        while(1) {
            test = (int) ((double)(rand()) / (RAND_MAX) * (9.0 - 0.0) ) +1;
            if(repeat[test] == 0) {
                repeat[test]=1;
                break;
            }
        }
        if(Unused(sudoku, row, col, test)) {
            sudoku[row][col]=test;

            if(Generate(sudoku))
                return 1;

            sudoku[row][col]=0;
        }
    }
    return 0;
}

void Block(int sudoku[][9]) {
    srand((unsigned) time(NULL));
    rand();

    int block_num, block_row, block_col;
    block_num = (int) ((double)(rand()) / (RAND_MAX) * (35.0 - 15.0) ) +15;

    for(int i=0; i<=block_num; i++) {
        while(1) {
            block_row = (int) ((double)(rand()) / (RAND_MAX) * (8.0 - 0.0) );
            block_col = (int) ((double)(rand()) / (RAND_MAX) * (8.0 - 0.0) );
            if(sudoku[block_row][block_col] != 0)
                break;
        }
        sudoku[block_row][block_col] = 0;
    }
}

void PrintSudoku(int sudoku[][9]) {
    for(int row=0; row<9; row++) {
        for(int col=0; col<9; col++)
            cout << sudoku[row][col] << " ";
        cout << endl;
    }
}

int main() {
    int sudoku[9][9];

    for(int row=0; row<9; row++)
        for(int col=0; col<9; col++)
            sudoku[row][col] = 0;

    Generate(sudoku);
    Block(sudoku);
    PrintSudoku(sudoku);

    return 0;
}

