#include <iostream>
#include <string.h>
#include <graphics.h>
#include <windows.h>
using namespace std;

#define N 9

// Hard code sudoku
int arr[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
};

int userarr[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
};



//Displays grid with indices
const int cellsize = 50;
void Display_Graphics(int arr[9][9], int userarr[9][9], int size,int flag=0)
{
    int i,j;
    for(i = 1; i <=size; i++)
    {
        for(j=1; j<=size; j++)
        {
            rectangle(i*cellsize, j * cellsize,i*cellsize + cellsize,j * cellsize + cellsize);
            if(flag==0)
            {
                if(arr[i-1][j-1]!=0 && arr[i-1][j-1]==userarr[i-1][j-1])
                {
                    char s[2];
                    s[0] =  char(userarr[i-1][j-1] + 48) ;
                    s[1] = '\0';
                    outtextxy(j*cellsize+23,i*cellsize+23,s);
                    setfillstyle(SOLID_FILL,RED);
                    rectangle(j*cellsize+10, i * cellsize+10,j*cellsize + 40,i* cellsize + 40);
                    floodfill(j*cellsize+cellsize/2,i*cellsize+cellsize/2,WHITE);
                }
                else if(userarr[i-1][j-1]!=0)
                {
                    char s[2];
                    s[0] =  char(userarr[i-1][j-1] + 48) ;
                    s[1] = '\0';
                    outtextxy(j*cellsize+23,i*cellsize+23,s);
                    setfillstyle(SOLID_FILL,GREEN);
                    rectangle(j*cellsize+10, i * cellsize+10,j*cellsize + 40,i* cellsize + 40);
                    floodfill(j*cellsize+cellsize/2,i*cellsize+cellsize/2,WHITE);
                }
            }
            if(flag==1)
            {
                char s[2];
                s[0] =  char(arr[i-1][j-1] + 48) ;
                s[1] = '\0';
                outtextxy(j*cellsize+23,i*cellsize+23,s);
                setfillstyle(SOLID_FILL,GREEN);
                rectangle(j*cellsize+10, i * cellsize+10,j*cellsize + 40,i* cellsize + 40);
                floodfill(j*cellsize+cellsize/2,i*cellsize+cellsize/2,WHITE);
            }
        }
    }
}


void Display(int A[N][N])
{
    int i, j;
    cout << "Displaying Sudoku below" << endl;

    for (i = -1; i < N; i++)
    {
        if (i % 3 == 0)
            cout << "___________________________________" << endl;
        for (j = -1; j < N; j++)
        {
            if (i == -1)
            {
                if (j % 3 == 0)
                    cout << "|";
                cout << " " << j + 1 << " ";
                if (j == 8)
                    cout << "|";
                continue;
            }
            if (j == -1)
            {
                cout << " " << i + 1 << " ";
                continue;
            }
            if (j % 3 == 0)
                cout << "|";
            cout << " " << A[i][j] << " ";
            if (j == 8)
                cout << "|";
        }
        cout << endl;
        if (i == 8)
            cout << "___________________________________" << endl;
    }
    Display_Graphics(arr,userarr,9);
}

void Set_Value(int r, int c, int val)
{
    if (val > 9 || val < 1)
    {
        cout << "Value must be in between 1 to 9";
        return;
    }
    if (userarr[r][c] == 0 || arr[r][c]==0)
        userarr[r][c] = val;
    else
        cout << "Enter indices of empty(0) element\n"<< endl;
}

int Check_Score()
{
    int i,j,score=0;
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(userarr[i][j] == arr[i][j] && userarr[i][j] != 0)
                score += 10;
        }
    }
    return score;
}

//For empty location returns true and if not any then returns false
bool Is_empty(int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (arr[row][col] == 0)
                return true;
    return false;
}

//Puts constraints like it should not be in row,col,box and returns true for some num from 1 to 9(Bounding Function)
bool Is_valid(int row, int col, int num)
{
    //Check all constraints if any of them is invalid then return false, otherwise return true

    //Checks for empty cell
    if (arr[row][col] != 0)
        return false;

    //Check for if number is already in row
    for (int j = 0; j < N; j++)
        if (arr[row][j] == num)
            return false;

    //Check for if number is already in column
    for (int i = 0; i < N; i++)
        if (arr[i][col] == num)
            return false;

    //Check for if number is in box
    int box_x = row / 3, box_y = col / 3;
    for (int i = box_x * 3; i < box_x * 3 + 3; i++)
        for (int j = box_y * 3; j < box_y * 3 + 3; j++)
            if (arr[i][j] == num)
                return false;

    //return true for valid value
    return true;
}

long long calls=0;
//Recursive Function for backtracking algorithm in sudoku
bool Solve()
{
    int row, col;

    //Check if any position is empty and returns to main if all positions are filled and we got the solution
    if (!Is_empty(row, col))
        return true;

    //Put values from 1 to 9 and try to validate every cell recursively
    for (int num = 1; num <= 9; num++)
    {
        if (Is_valid(row, col, num))
        {
            //assign temporary value
            arr[row][col] = num;

            //Recursively calls and backtrack
            if (Solve())
            {

                return true;

            }
            //Our value is not solution then make empty and try again
            arr[row][col] = 0;
        }
    }
    if(calls%25==0)
    {
        system("cls");
        cleardevice();
        Display(arr);
        Display_Graphics(arr,arr,9,1);
        delay(500);
    }
    calls++;
    //backtrack for not getting solution
    return false;
}
//Main Function Starts

int main()
{
    //Displays given sudoku
    int gd = DETECT, gm;

    //initgraph(&gd,&gm,"");
    initwindow(570,600,"Sudoku Solver");
    Display(userarr);
    int score = Check_Score();

    int r, c, val;
    //Enter x-index,y-index and value to be changed in sudoku indexes starting from 1 to 9
    cout << "\nClick any key to continue" << endl;
    getchar();

    do
    {
        system("cls");
        cleardevice();
        cout << "Enter -1 to finish and check your score\n"<< endl;
        Display(userarr);
        cout << "\nRow Index \t\t: ";
        cin >> r;
        if (r == -1)
            break;
        cout << "\nColumn Index \t\t: ";
        cin >> c;
        cout << "\nValue from 1 to 9 \t: ";
        cin >> val;
        Set_Value(r - 1, c - 1, val);
        Display(userarr);
    }
    while (r != -1 || c != -1);

    system("cls");
    cleardevice();
    Display(userarr);

    //Computer solves sudoku and displays it if exists
    if (Solve())
    {
        score = Check_Score()-score;
        cout << "\nYour Score is " << score<<endl<<endl;
        cout << "Solution of given Sudoku is.." << endl;
        Display(arr);
        Display_Graphics(arr,arr,N,1);
        outtextxy(100,20,"The Solution of the Sudoku is below!!");
        outtextxy(100,520,"Your Score is ");
        char str[10];
        sprintf(str,"%d",score);
        outtextxy(220,520,str);
    }
    else
        cout << "No Solution Exists!!" << endl;

    getch();
    closegraph();
    return 0;
}
/*
    <--------Sudoku Solver-------->

    Common approach is Naive algorithm but as it finds all combinations and picks one solution it is
    totally time wasting so better we should use Backtracking algorithm which terminates according to
    bounding function and will not find all combinations.

    Algorithm for solving sudoku is Backtracking algorithm.
    -> It is a recursive approach uses dfs(depth first search) to solve the problem.
    -> It goes putting on values from 1 to 9 with sudoku constraints in each cell and if next none
    value is not satisfying contraints then it backtracks i.e it comes to previous call and again put
    next possible value.This process is recursive.
    -> And where we got all cells filled we come up with sudoku solution and we will stop recursion.


    1st version --> Displays grid of sudoku with indices and user can put values in grid in empty places only and check for score
    2nd version --> Computer solves the sudoku given using backtracking algorithm and bounding function

    <---Created by Vedant Valsangkar--->
*/