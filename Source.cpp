#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include "MyMouse.h"
#include <Windows.h>
#include "MyRectangle.h"
#include "Colors.h"
//using namespace std;
using std::cout;
using std::endl;


struct position
{
    int x;
    int y;
};

class MyStack
{
public:
    position arr[1000];
    int T;
    MyStack() { T = 0; }
    void push(int x, int y);
    position pop();
    position peek();
};

void MyStack::push(int x, int y)
{
    position p;
    p.x = x;
    p.y = y;
    arr[T] = p;
    T++;
}

position MyStack::peek()
{
    return arr[T - 1];
}

MyStack S;
char board[22][50];
int value;
int xpos, ypos;
Coordinates C;
Colors G;
const int SLEEP = 3;
int cherry = 0;

// returns false of xy same as top of stack
bool CheckTopStack(int x, int y)
{
    position p;
    p = S.peek();
    if (p.x == x && p.y == y)
        return false;
    return true;
}

position MyStack::pop()
{
    T--;
    return arr[T];
}

//display box when mouse finishes maze
MyRectangle R(0, 0, 50, 22, char(219), true, 14, 10, "VICTORY!!!");
//display box for how to
MyRectangle R2(53, 2, 28, 8, char(254), true, 3, 7);
//cherry box
MyRectangle R3(53, 11, 28, 7, char(254), true, 3, 13);

void DisplayHowTo()
{
    R2.gotoxy(55, 4);
    cout << "Movement   -  Arrow Keys";
    R2.gotoxy(55, 5);
    cout << "Destroy    -  w a s d";
    R2.gotoxy(55, 6);
    cout << "Place      -  W A S D";
    R2.gotoxy(55, 7);
    cout << "  Collect 5 Cherries ";
}

void DisplayCherryBox()
{
    G.SetColor(NULL, 13);
    R3.gotoxy(58, 13);
    cout << "Cherries Collected";
}

void DisplayBoard()
{
    ifstream input("c:\\temp\\mazeinterface.txt");
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 50; j++)
            input >> board[i][j];
    system("cls");
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (board[i][j] == '1')
            {
                G.SetColor(NULL, 8);
                cout << char(219);
            }
            else if (board[i][j] == '2')
            {
                G.SetColor(NULL, 10);
                cout << char(176);
            }
            else if (board[i][j] == '3')
            {
                G.SetColor(NULL, 13);
                cout << char(219);
            }
            else if (board[i][j] == '4')
            {
                G.SetColor(NULL, 6);
                cout << char(219);
            }
            else
                cout << " ";
        }
        cout << endl;
    }
    xpos = 0; // the starting x position of the mouse
    ypos = 1; // the starting y position of the mouse
}

bool MySleep(int ms)
{
    double d = 0;
    while (d < ms)
    {
        d++;
        Sleep(1);
        if (_kbhit())
            return true;
    }
    return false;
}

//void Gate(int count) 
//{
//    if (cherry < 5)
//    {
//        C.gotoxy(50, 17);
//        cout << char(219);
//    }
//    else (cherry >= 5);
//    {
//        C.gotoxy(50, 17);
//        cout << " ";
//    }
//}

void main()
{
    DisplayBoard();
    DisplayHowTo();
    DisplayCherryBox();
    R2.Draw();
    R3.Draw();

    // DIGGER GUY

    int ux, uy;
    ux = 3;
    uy = 19;
    G.SetColor(NULL, 12);
    C.gotoxy(ux, uy);
    cout << "R";
    int cherry = 0;

    char c;
    while (1)
    {
        C.ShowConsoleCursor(false);
        if (MySleep(SLEEP))
        {
            c = _getch();
            // destroying
            if ((c == 'd') && (ux + 1 < 49)) //DESTROY TO THE RIGHT
            {
                if (ux + 1 == 49)
                    continue;
                board[uy][ux + 1] = '0';
                C.gotoxy(ux + 1, uy);
                cout << " ";
            }
            else if ((c == 'a') && (ux - 1 > 0)) //DESTROY TO THE LEFT
            {
                if (ux - 1 == 0)
                    continue;
                board[uy][ux - 1] = '0';
                C.gotoxy(ux - 1, uy);
                cout << " ";
            }
            else if ((c == 'w') && (uy + 1 > 0)) //DESTROY TO THE UP
            {
                if (uy - 1 == 0)
                    continue;
                board[uy - 1][ux] = '0';
                C.gotoxy(ux, uy - 1);
                cout << " ";
            }
            else if ((c == 's') && (uy - 1 <= 21)) //DESTROY TO THE DOWN
            {
                if (uy + 1 == 21)
                    continue;
                board[uy + 1][ux] = '0';
                C.gotoxy(ux, uy + 1);
                cout << " ";
            }

            //placing
            else if ((c == 'D') && (ux + 1 < 49)) //PLACE TO THE RIGHT
            {
                if (ux + 1 == 49)
                    continue;
                board[uy][ux + 1] = '1';
                C.gotoxy(ux + 1, uy);
                cout << char(219);
            }
            else if ((c == 'A') && (ux - 1 > 0)) //PLACE TO THE LEFT
            {
                if (ux - 1 == 0)
                    continue;
                board[uy][ux - 1] = '1';
                C.gotoxy(ux - 1, uy);
                cout << char(219);
            }
            else if ((c == 'W') && (uy + 1 > 0)) //PLACE TO THE UP
            {
                if (uy - 1 == 0)
                    continue;
                board[uy - 1][ux] = '1';
                C.gotoxy(ux, uy - 1);
                cout << char(219);
            }
            else if ((c == 'S') && (uy - 1 <= 21)) //PLACE TO THE DOWN
            {
                if (uy + 1 == 21)
                    continue;
                board[uy + 1][ux] = '1';
                C.gotoxy(ux, uy + 1);
                cout << char(219);
            }

            else if (c == -32)
            {
                c = _getch(); // moving
                if ((c == 77) && (board[uy][ux + 1] == '0')) //MOVE CHARACHTER RIGHT
                {
                    C.gotoxy(ux, uy);
                    cout << " ";
                    ux++;
                    C.gotoxy(ux, uy);
                    G.SetColor(NULL, 12);
                    cout << "R";
                }
                else if ((c == 75) && (board[uy][ux - 1] == '0')) //MOVE CHARACHTER LEFT
                {
                    C.gotoxy(ux, uy);
                    cout << " ";
                    ux--;
                    C.gotoxy(ux, uy);
                    G.SetColor(NULL, 12);
                    cout << "R";
                }
                else if ((c == 72) && (board[uy - 1][ux] == '0')) //MOVE CHARACHTER UP
                {
                    C.gotoxy(ux, uy);
                    cout << " ";
                    uy--;
                    C.gotoxy(ux, uy);
                    G.SetColor(NULL, 12);
                    cout << "R";
                }
                else if ((c == 80) && (board[uy + 1][ux] == '0')) //MOVE CHARACHTER DOWN
                {
                    C.gotoxy(ux, uy);
                    cout << " ";
                    uy++;
                    C.gotoxy(ux, uy);
                    G.SetColor(NULL, 12);
                    cout << "R";
                }
            }
        }

        //MOUSE MOVEMENT

        C.ShowConsoleCursor(false);
        G.SetColor(NULL, 14);
        C.gotoxy(xpos, ypos);
        cout << "*";
        if (MySleep(SLEEP) == false)
        {
            C.gotoxy(xpos, ypos);
            cout << " ";
            if ((board[ypos][xpos + 1] == '0') && //MOVE MOUSE RIGHT
                (CheckTopStack(xpos + 1, ypos)))
            {
                S.push(xpos, ypos);
                xpos++;
            }
            else if ((board[ypos + 1][xpos] == '0') && //MOVE MOUSE DOWN
                (CheckTopStack(xpos, ypos + 1)))
            {
                S.push(xpos, ypos);
                ypos++;
            }
            else if ((board[ypos][xpos - 1] == '0') && //MOVE MOUSE LEFT
                (CheckTopStack(xpos - 1, ypos)))
            {
                S.push(xpos, ypos);
                xpos--;
            }
            else if ((board[ypos - 1][xpos] == '0') && //MOVE MOUSE UP
                (CheckTopStack(xpos, ypos - 1)))
            {
                S.push(xpos, ypos);
                ypos--;
            }
            else if ((board[ypos][xpos + 1] == '3') && // CHERRY RIGHT
                (CheckTopStack(xpos + 1, ypos)))
            {
                cherry++;
                G.SetColor(NULL, 13);
                R3.gotoxy(66, 15);
                cout << cherry;
                S.push(xpos, ypos);
                xpos++;
            }
            else if ((board[ypos + 1][xpos] == '3') && // CHERRY DOWN
                (CheckTopStack(xpos, ypos + 1)))
            {
                cherry++;
                G.SetColor(NULL, 13);
                R3.gotoxy(66, 15);
                cout << cherry;
                S.push(xpos, ypos);
                ypos++;
            }
            else if ((board[ypos][xpos - 1] == '3') && // CHERRY LEFT
                (CheckTopStack(xpos - 1, ypos)))
            {
                cherry++;
                G.SetColor(NULL, 13);
                R3.gotoxy(66, 15);
                cout << cherry;
                S.push(xpos, ypos);
                xpos--;
            }
            else if ((board[ypos - 1][xpos] == '3') && // CHERRY UP
                (CheckTopStack(xpos, ypos - 1)))
            {
                cherry++;
                G.SetColor(NULL, 13);
                R3.gotoxy(66, 15);
                cout << cherry;
                S.push(xpos, ypos);
                ypos--;
            }
            else if ((board[ypos][xpos + 1] == '4') && //THE GATE
                (CheckTopStack(xpos + 1, ypos)))
            {
                if (cherry >= 5)
                {
                    S.push(xpos, ypos);
                    xpos++;
                }
                else if (cherry < 5)
                {
                    C.gotoxy(xpos, ypos);
                    cout << ".";
                    board[ypos][xpos] = '4';
                    position p;
                    p = S.pop();
                    xpos = p.x;
                    ypos = p.y;
                }

            }
            else if ((board[ypos][xpos + 1] == '2') && //WE HAVE REACHED THE END
                (CheckTopStack(xpos + 1, ypos)))
            {
                G.SetColor(NULL, 10);
                cout << "VICTORY!!!" << endl;
                system("cls");
                R.Draw();
                while (1);
            }
            else // dead end
            {
                C.gotoxy(xpos, ypos);
                cout << ".";
                board[ypos][xpos] = '1';
                position p;
                p = S.pop();
                xpos = p.x;
                ypos = p.y;

            }
        }
    }
}

