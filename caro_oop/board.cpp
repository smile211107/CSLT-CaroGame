#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "board.h"

unsigned char mainGameBoard[13][13] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int checkRow(int y, int x)
{
    int res = 1, start = 1, end = 12;
    if (x > 4) start = x - 4;
    if (x < 9) end = x + 4;
    for (int i = start; i <= end; i++)
    {
        if (mainGameBoard[y][i] == mainGameBoard[y][i - 1] && mainGameBoard[y][i] == mainGameBoard[y][x] && mainGameBoard[y][i] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[y][x];
    }
    return 0;
}

int checkCol(int y, int x)
{
    int res = 1, start = 1, end = 12;
    if (y > 4) start = y - 4;
    if (y < 9) end = y + 4;
    for (int i = start; i <= end; i++)
    {
        if (mainGameBoard[i][x] == mainGameBoard[i - 1][x] && mainGameBoard[i][x] == mainGameBoard[y][x] && mainGameBoard[i][x] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[y][x];
    }
    return 0;
}

int checkDia2(int y, int x)
{
    int i = y, j = x, res = 1;
    if (y + x < 12)
    {
        i = 2;
        j = y + x - 2;
    }
    else
    {
        i = x + y - 11;
        j = 11;
    }
    while (i <= 12 && j >= 1)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j + 1] && mainGameBoard[i][j] == mainGameBoard[y][x] && mainGameBoard[i][j] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[i][j];
        i++; j--;
    }
    return 0;
}

int checkDia1(int y, int x)
{
    int i = y, j = x, res = 1;
    if (y > x)
    {
        i = y - x + 2;
        j = 2;
    }
    else
    {
        i = 2;
        j = x - y + 2;
    }
    while (i <= 12 && j <= 12)
    {
        if (mainGameBoard[i][j] == mainGameBoard[i - 1][j - 1] && mainGameBoard[i][j] == mainGameBoard[y][x] && mainGameBoard[i][j] > 0) res++;
        else res = 1;
        if (res > 4) return mainGameBoard[i][j];
        i++; j++;
    }
    return 0;
}

int checkWin(int y, int x, int checkNum)
{
    if (checkNum == checkRow(y, x) || checkNum == checkCol(y, x) || checkNum == checkDia1(y, x) || checkNum == checkDia2(y, x))
    {
        //printf_s("%d %d %d\n",mainGameBoard[y][x],y,x);
        return checkNum;
    }
    return 0;
}