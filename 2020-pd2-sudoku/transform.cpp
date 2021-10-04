#include <iostream>
using namespace std;

void changeNum(int sudoku[][9], int x, int y) {
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++) {
            if(sudoku[i][j] == x)
                sudoku[i][j]=y;
            else if(sudoku[i][j] == y)
                sudoku[i][j]=x;
        }
}

void changeRow(int sudoku[][9], int x, int y) {
    int temp, y_row=3*y;

    for(int i=3*x; i<3*(x+1); i++) {
        for(int j=0; j<9; j++) {
            temp=sudoku[i][j];
            sudoku[i][j]=sudoku[y_row][j];
            sudoku[y_row][j]=temp;
        }
        y_row++;
    }
}

void changeCol(int sudoku[][9], int x, int y) {
    int temp, y_col=0;

    for(int i=0; i<9; i++) {
        y_col=3*y;
        for(int j=3*x; j<3*(x+1); j++) {
            temp=sudoku[i][j];
            sudoku[i][j]=sudoku[i][y_col];
            sudoku[i][y_col]=temp;
            y_col++;
        }
    }
}

void rotate(int sudoku[][9], int x) {
    int temp_su[9][9];
    for(int num=0; num<x; num++) {
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                temp_su[i][j]=sudoku[i][j];

        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                sudoku[i][j]=temp_su[8-j][i];
    }
}

void flip(int sudoku[][9], int x) {
    int temp_su[9][9];
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++)
            temp_su[i][j]=sudoku[i][j];

    if(x == 0) {
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                sudoku[i][j]=temp_su[8-i][j];
    } else if(x == 1) {
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                sudoku[i][j]=temp_su[i][8-j];
    }
}

void PrintSudoku(int sudoku[][9]) {
    for(int row=0; row<9; row++) {
        for(int col=0; col<8; col++)
            cout << sudoku[row][col] << " ";
        cout << sudoku[row][8];
        cout << endl;
    }
}

int main() {
    int sudoku[9][9], num_in;

    //cout << "## input problem" << endl;
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++) {
            cin >> num_in;
            sudoku[i][j]=num_in;
        }

//	cout << "## command" << endl;
    while(1) {
        int command=0, x=0, y=0;
        cin >> command;
        if(command == 0)
            break;
        else if(command == 1) {
            cin >> x >> y;
            changeNum(sudoku, x, y);
        } else if(command == 2) {
            cin >> x >> y;
            changeRow(sudoku, x, y);
        } else if(command == 3) {
            cin >> x >> y;
            changeCol(sudoku, x, y);
        } else if(command == 4) {
            cin >> x;
            rotate(sudoku, x);
        } else if(command == 5) {
            cin >> x;
            flip(sudoku, x);
        }
    }

    // cout << "## output"	 << endl;
    PrintSudoku(sudoku);

    return 0;
}

