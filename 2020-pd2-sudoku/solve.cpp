#include <iostream>
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

int Solve(int sudoku[][9], int sudoku_solved[][9][9], int &solve_num) {
    int row,col;

    if(FindEmpty(sudoku, row, col) == 0) {
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++) {
                sudoku_solved[solve_num+1][i][j]=sudoku[i][j];
                sudoku[i][j]=sudoku_solved[0][i][j];
            }
        solve_num++;
        return 1;
    }

    for(int test=1; test<=9; test++) {
        if(Unused(sudoku, row, col, test)) {
            sudoku[row][col]=test;

            if(Solve(sudoku, sudoku_solved, solve_num))
                return 1;

            sudoku[row][col]=0;
        }
    }
    return 0;
}

int Solve_re(int sudoku[][9], int sudoku_solved[][9][9], int &solve_num) {
    int row,col;

    if(FindEmpty(sudoku, row, col) == 0) {
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++) {
                sudoku_solved[solve_num+1][i][j]=sudoku[i][j];
                sudoku[i][j]=sudoku_solved[0][i][j];
            }
        solve_num++;
        return 1;
    }

    for(int test=9; test>=1; test--) {
        if(Unused(sudoku, row, col, test)) {
            sudoku[row][col]=test;

            if(Solve_re(sudoku, sudoku_solved, solve_num))
                return 1;

            sudoku[row][col]=0;
        }
    }
    return 0;
}

void PrintSolution(int sudoku_solved[][9][9], int solve_num) {
    if(solve_num > 1)
        cout << "2" << endl;
    else {
        cout << solve_num << endl;
        for(int row=0; row<9; row++) {
            for(int col=0; col<8; col++)
                cout << sudoku_solved[solve_num][row][col] << " ";
            cout << sudoku_solved[solve_num][row][8];
            cout << endl;
        }
    }
}

int main() {
    int sudoku[9][9], sudoku_solved[10][9][9], check=0;
    int num_in, solve_num=0;

    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++) {
            cin >> num_in;
            sudoku[i][j]=num_in;
            sudoku_solved[0][i][j]=num_in;
        }

    if(Solve(sudoku, sudoku_solved, solve_num)) {
        Solve_re(sudoku, sudoku_solved, solve_num);

        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                if(sudoku_solved[1][i][j] != sudoku_solved[2][i][j]) {
                    check=1;
                    break;
                }
            }
            if(check == 1)
                break;
        }
        if(check == 0)
            solve_num--;

        PrintSolution(sudoku_solved, solve_num);
    } else
        cout << "0" << endl;

    return 0;
}
